/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2011 Razor team
 *            2014 LXQt team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *   Maciej Płaza <plaza.maciej@gmail.com>
 *   Kuzma Shapran <kuzma.shapran@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "ukuitaskgroup.h"
#include "ukuitaskbar.h"

#include <QDebug>
#include <QMimeData>
#include <QFocusEvent>
#include <QDragLeaveEvent>
#include <QStringBuilder>
#include <QMenu>
#include <XdgIcon>
#include <KF5/KWindowSystem/KWindowSystem>
#include <functional>

#include <QtX11Extras/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <QLabel>

#include <qmainwindow.h>
#include <QWidget>

#define PREVIEW_WIDTH		168
#define PREVIEW_HEIGHT		128
#define SPACE_WIDTH			8
#define SPACE_HEIGHT		8
#define THUMBNAIL_WIDTH		(PREVIEW_WIDTH - SPACE_WIDTH)
#define THUMBNAIL_HEIGHT	(PREVIEW_HEIGHT - SPACE_HEIGHT)
#define ICON_WIDTH			48
#define ICON_HEIGHT			48

QPixmap qimageFromXImage(XImage* ximage)
{
    QImage::Format format = QImage::Format_ARGB32_Premultiplied;
    if (ximage->depth == 24)
        format = QImage::Format_RGB32;
    else if (ximage->depth == 16)
        format = QImage::Format_RGB16;

    QImage image = QImage(reinterpret_cast<uchar*>(ximage->data),
                          ximage->width, ximage->height,
                          ximage->bytes_per_line, format).copy();

    // 大端还是小端?
    if ((QSysInfo::ByteOrder == QSysInfo::LittleEndian && ximage->byte_order == MSBFirst)
            || (QSysInfo::ByteOrder == QSysInfo::BigEndian && ximage->byte_order == LSBFirst)) {

        for (int i = 0; i < image.height(); i++) {
            if (ximage->depth == 16) {
                ushort* p = reinterpret_cast<ushort*>(image.scanLine(i));
                ushort* end = p + image.width();
                while (p < end) {
                    *p = ((*p << 8) & 0xff00) | ((*p >> 8) & 0x00ff);
                    p++;
                }
            } else {
                uint* p = reinterpret_cast<uint*>(image.scanLine(i));
                uint* end = p + image.width();
                while (p < end) {
                    *p = ((*p << 24) & 0xff000000) | ((*p << 8) & 0x00ff0000)
                         | ((*p >> 8) & 0x0000ff00) | ((*p >> 24) & 0x000000ff);
                    p++;
                }
            }
        }
    }

    // 修复alpha通道
    if (format == QImage::Format_RGB32) {
        QRgb* p = reinterpret_cast<QRgb*>(image.bits());
        for (int y = 0; y < ximage->height; ++y) {
            for (int x = 0; x < ximage->width; ++x)
                p[x] |= 0xff000000;
            p += ximage->bytes_per_line / 4;
        }
    }

    return QPixmap::fromImage(image);
}




/************************************************

 ************************************************/
UKUITaskGroup::UKUITaskGroup(const QString &groupName, WId window, UKUITaskBar *parent)
    : UKUITaskButton(window, parent, parent),
    mGroupName(groupName),
    mPopup(new UKUIGroupPopup(this)),
    mPreventPopup(false),
    mSingleButton(true)
{
    Q_ASSERT(parent);

    setObjectName(groupName);
    setText(groupName);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked(bool)));
    connect(KWindowSystem::self(), SIGNAL(currentDesktopChanged(int)), this, SLOT(onDesktopChanged(int)));
    connect(KWindowSystem::self(), SIGNAL(activeWindowChanged(WId)), this, SLOT(onActiveWindowChanged(WId)));
    connect(parent, &UKUITaskBar::buttonRotationRefreshed, this, &UKUITaskGroup::setAutoRotation);
    connect(parent, &UKUITaskBar::refreshIconGeometry, this, &UKUITaskGroup::refreshIconsGeometry);
    connect(parent, &UKUITaskBar::buttonStyleRefreshed, this, &UKUITaskGroup::setToolButtonsStyle);
    connect(parent, &UKUITaskBar::showOnlySettingChanged, this, &UKUITaskGroup::refreshVisibility);
    connect(parent, &UKUITaskBar::popupShown, this, &UKUITaskGroup::groupPopupShown);
}

/************************************************

 ************************************************/
void UKUITaskGroup::contextMenuEvent(QContextMenuEvent *event)
{
    setPopupVisible(false, true);
    mPreventPopup = true;
    if (mSingleButton)
    {
        UKUITaskButton::contextMenuEvent(event);
        return;
    }

    QMenu * menu = new QMenu(tr("Group"));
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QAction *a = menu->addAction(XdgIcon::fromTheme("process-stop"), tr("Close group"));
    connect(a, SIGNAL(triggered()), this, SLOT(closeGroup()));
    connect(menu, &QMenu::aboutToHide, [this] {
        mPreventPopup = false;
    });
    menu->setGeometry(plugin()->panel()->calculatePopupWindowPos(mapToGlobal(event->pos()), menu->sizeHint()));
    plugin()->willShowWindow(menu);
    menu->show();
}

/************************************************

 ************************************************/
void UKUITaskGroup::closeGroup()
{
    for (UKUITaskButton *button : qAsConst(mButtonHash) )
        if (button->isOnDesktop(KWindowSystem::currentDesktop()))
            button->closeApplication();
}

/************************************************

 ************************************************/
UKUITaskButton * UKUITaskGroup::addWindow(WId id)
{
    if (mButtonHash.contains(id))
        return mButtonHash.value(id);

    UKUITaskButton *btn = new UKUITaskButton(id, parentTaskBar(), mPopup);
    btn->setToolButtonStyle(popupButtonStyle());

    btn->setStyleSheet(
                //正常状态样式
                "QToolButton{"
                "background-color:rgba(74,112,139,90%);"//背景色（也可以设置图片）
                "qproperty-iconSize:24px 24px;"
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:0px;"                     //边框宽度像素
                "border-radius:0px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "font:bold 14px;"                       //字体，字体大小
                "color:rgba(255,255,255,100%);"                //字体颜色
                "padding:0px;"                          //填衬
                "spacing:0px;"
                "border-bottom-style:solid"
                "}"
                //鼠标悬停样式
                "QToolButton:hover{"
                "background-color:rgba(74,112,139,80%);"
                "}"
                //鼠标按下样式
                "QToolButton:pressed{"
                "background-color:rgba(74,112,139,100%);"
                "}"
                );

    if (btn->isApplicationActive())
    {
        btn->setChecked(true);
        setChecked(true);
    }

    mButtonHash.insert(id, btn);
    //mPopup->addButton(btn);

    connect(btn, SIGNAL(clicked()), this, SLOT(onChildButtonClicked()));
    refreshVisibility();

    return btn;
}

/************************************************

 ************************************************/
UKUITaskButton * UKUITaskGroup::checkedButton() const
{
    for (UKUITaskButton* button : qAsConst(mButtonHash))
        if (button->isChecked())
            return button;

    return NULL;
}

/************************************************

 ************************************************/
UKUITaskButton * UKUITaskGroup::getNextPrevChildButton(bool next, bool circular)
{
    UKUITaskButton *button = checkedButton();
    int idx = mPopup->indexOf(button);
    int inc = next ? 1 : -1;
    idx += inc;

    // if there is no cheked button, get the first one if next equals true
    // or the last one if not
    if (!button)
    {
        idx = -1;
        if (next)
        {
            for (int i = 0; i < mPopup->count() && idx == -1; i++)
                if (mPopup->itemAt(i)->widget()->isVisibleTo(mPopup))
                    idx = i;
        }
        else
        {
            for (int i = mPopup->count() - 1; i >= 0 && idx == -1; i--)
                if (mPopup->itemAt(i)->widget()->isVisibleTo(mPopup))
                    idx = i;
        }
    }

    if (circular)
        idx = (idx + mButtonHash.count()) % mButtonHash.count();
    else if (mPopup->count() <= idx || idx < 0)
        return NULL;

    // return the next or the previous child
    QLayoutItem *item = mPopup->itemAt(idx);
    if (item)
    {
        button = qobject_cast<UKUITaskButton*>(item->widget());
        if (button->isVisibleTo(mPopup))
            return button;
    }

    return NULL;
}

/************************************************

 ************************************************/
void UKUITaskGroup::onActiveWindowChanged(WId window)
{
    UKUITaskButton *button = mButtonHash.value(window, nullptr);
    for (UKUITaskButton *btn : qAsConst(mButtonHash))
        btn->setChecked(false);

    if (button)
    {
        button->setChecked(true);
        if (button->hasUrgencyHint())
            button->setUrgencyHint(false);
    }
    setChecked(nullptr != button);
}

/************************************************

 ************************************************/
void UKUITaskGroup::onDesktopChanged(int number)
{
    refreshVisibility();
}

/************************************************

 ************************************************/
void UKUITaskGroup::onWindowRemoved(WId window)
{
    if (mButtonHash.contains(window))
    {
        UKUITaskButton *button = mButtonHash.value(window);
        mButtonHash.remove(window);
        mPopup->removeWidget(button);
        button->deleteLater();

        if (mButtonHash.count())
            regroup();
        else
        {
            if (isVisible())
                emit visibilityChanged(false);
            hide();
            emit groupBecomeEmpty(groupName());

        }
    }
}

/************************************************

 ************************************************/
void UKUITaskGroup::onChildButtonClicked()
{
    setPopupVisible(false, true);
}

/************************************************

 ************************************************/
Qt::ToolButtonStyle UKUITaskGroup::popupButtonStyle() const
{
    // do not set icons-only style in the buttons in the group,
    // as they'll be indistinguishable
    const Qt::ToolButtonStyle style = toolButtonStyle();
    return style == Qt::ToolButtonIconOnly ? Qt::ToolButtonTextBesideIcon : style;
}

/************************************************

 ************************************************/
void UKUITaskGroup::setToolButtonsStyle(Qt::ToolButtonStyle style)
{
    setToolButtonStyle(style);

    const Qt::ToolButtonStyle styleInPopup = popupButtonStyle();
    for (auto & button : mButtonHash)
    {
        button->setToolButtonStyle(styleInPopup);
    }
}

/************************************************

 ************************************************/
int UKUITaskGroup::buttonsCount() const
{
    return mButtonHash.count();
}

/************************************************

 ************************************************/
int UKUITaskGroup::visibleButtonsCount() const
{
    int i = 0;
    for (UKUITaskButton *btn : qAsConst(mButtonHash))
        if (btn->isVisibleTo(mPopup))
            i++;
    return i;
}

/************************************************

 ************************************************/
void UKUITaskGroup::draggingTimerTimeout()
{
    if (mSingleButton)
        setPopupVisible(false);
}

/************************************************

 ************************************************/
void UKUITaskGroup::onClicked(bool)
{
    if (visibleButtonsCount() > 1)
    {
        setChecked(mButtonHash.contains(KWindowSystem::activeWindow()));
        setPopupVisible(true);
    }
}

/************************************************

 ************************************************/
void UKUITaskGroup::regroup()
{
    int cont = visibleButtonsCount();
    recalculateFrameIfVisible();

//    if (cont == 1)
//    {
//        mSingleButton = false;
//        // Get first visible button
//        UKUITaskButton * button = NULL;
//        for (UKUITaskButton *btn : qAsConst(mButtonHash))
//        {
//            if (btn->isVisibleTo(mPopup))
//            {
//                button = btn;
//                break;
//            }
//        }

//        if (button)
//        {
//            setText(button->text());
//            setToolTip(button->toolTip());
//            setWindowId(button->windowId());

//        }
//    }
    /*else*/ if (cont == 0)
        hide();
    else
    {
        mSingleButton = false;
        QString t = QString("%1 - %2 windows").arg(mGroupName).arg(cont);
        setText(t);
        setToolTip(parentTaskBar()->isShowGroupOnHover() ? QString() : t);
    }

}

/************************************************

 ************************************************/
void UKUITaskGroup::recalculateFrameIfVisible()
{
    if (mPopup->isVisible())
    {
        recalculateFrameSize();
        if (plugin()->panel()->position() == IUKUIPanel::PositionBottom)
            recalculateFramePosition();
    }
}

/************************************************

 ************************************************/
void UKUITaskGroup::setAutoRotation(bool value, IUKUIPanel::Position position)
{
    for (UKUITaskButton *button : qAsConst(mButtonHash))
        button->setAutoRotation(false, position);

    UKUITaskButton::setAutoRotation(value, position);
}

/************************************************

 ************************************************/
void UKUITaskGroup::refreshVisibility()
{
    bool will = false;
    UKUITaskBar const * taskbar = parentTaskBar();
    const int showDesktop = taskbar->showDesktopNum();
    for(UKUITaskButton * btn : qAsConst(mButtonHash))
    {
        bool visible = taskbar->isShowOnlyOneDesktopTasks() ? btn->isOnDesktop(0 == showDesktop ? KWindowSystem::currentDesktop() : showDesktop) : true;
        visible &= taskbar->isShowOnlyCurrentScreenTasks() ? btn->isOnCurrentScreen() : true;
        visible &= taskbar->isShowOnlyMinimizedTasks() ? btn->isMinimized() : true;
        btn->setVisible(visible);
        will |= visible;
    }

    bool is = isVisible();
    setVisible(will);
    regroup();

    if (is != will)
        emit visibilityChanged(will);
}

/************************************************

 ************************************************/
QMimeData * UKUITaskGroup::mimeData()
{
    QMimeData *mimedata = new QMimeData;
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << groupName();
    mimedata->setData(mimeDataFormat(), byteArray);
    return mimedata;
}

/************************************************

 ************************************************/
void UKUITaskGroup::setPopupVisible(bool visible, bool fast)
{
    if (visible && !mPreventPopup && !mSingleButton)
    {

        if (!mPopup->isVisible())
        {
            // setup geometry

            recalculateFrameSize();
            recalculateFramePosition();
        }
        showPreview();
        /* for origin preview
        plugin()->willShowWindow(mPopup);
        mPopup->show();
        qDebug()<<"setPopupVisible ********";
        emit popupShown(this);*/
    }
    else
        mPopup->hide(fast);
}
/************************************************

 ************************************************/
void UKUITaskGroup::refreshIconsGeometry()
{
    QRect rect = geometry();
    rect.moveTo(mapToGlobal(QPoint(0, 0)));

    if (mSingleButton)
    {
        refreshIconGeometry(rect);
        return;
    }

    for(UKUITaskButton *but : qAsConst(mButtonHash))
    {
        but->refreshIconGeometry(rect);
        but->setIconSize(QSize(plugin()->panel()->iconSize(), plugin()->panel()->iconSize()));
    }
}

/************************************************

 ************************************************/
QSize UKUITaskGroup::recalculateFrameSize()
{
    int height = recalculateFrameHeight();
    mPopup->setMaximumHeight(1000);
    mPopup->setMinimumHeight(0);

    int hh = recalculateFrameWidth();
    mPopup->setMaximumWidth(hh);
    mPopup->setMinimumWidth(0);

    QSize newSize(hh, height);
    mPopup->resize(newSize);

    return newSize;
}

/************************************************

 ************************************************/
int UKUITaskGroup::recalculateFrameHeight() const
{
    int cont = visibleButtonsCount();
    int h = !plugin()->panel()->isHorizontal() && parentTaskBar()->isAutoRotate() ? width() : height();
    return cont * h + (cont + 1) * mPopup->spacing();
}

/************************************************

 ************************************************/
int UKUITaskGroup::recalculateFrameWidth() const
{
    const QFontMetrics fm = fontMetrics();
    int max = 100 * fm.width (' '); // elide after the max width
    int txtWidth = 0;
    for (UKUITaskButton *btn : qAsConst(mButtonHash))
        txtWidth = qMax(fm.width(btn->text()), txtWidth);
    return iconSize().width() + qMin(txtWidth, max) + 30/* give enough room to margins and borders*/;
}

/************************************************

 ************************************************/
QPoint UKUITaskGroup::recalculateFramePosition()
{
    // Set position
    int x_offset = 0, y_offset = 0;
    switch (plugin()->panel()->position())
    {
    case IUKUIPanel::PositionTop:
        y_offset += height();
        break;
    case IUKUIPanel::PositionBottom:
        y_offset = -recalculateFrameHeight();
        break;
    case IUKUIPanel::PositionLeft:
        x_offset += width();
        break;
    case IUKUIPanel::PositionRight:
        x_offset = -recalculateFrameWidth();
        break;
    }

    QPoint pos = mapToGlobal(QPoint(x_offset, y_offset));
    mPopup->move(pos);

    return pos;
}

/************************************************

 ************************************************/
void UKUITaskGroup::leaveEvent(QEvent *event)
{
    setPopupVisible(false);
    QToolButton::leaveEvent(event);
}

/************************************************

 ************************************************/
void UKUITaskGroup::enterEvent(QEvent *event)
{
    QToolButton::enterEvent(event);

    if (sDraggging)
        return;
    if (parentTaskBar()->isShowGroupOnHover())
    {
        setPopupVisible(true);
    }
}

/************************************************

 ************************************************/
void UKUITaskGroup::dragEnterEvent(QDragEnterEvent *event)
{
    // only show the popup if we aren't dragging a taskgroup
    if (!event->mimeData()->hasFormat(mimeDataFormat()))
    {
        setPopupVisible(true);
    }
    UKUITaskButton::dragEnterEvent(event);
}

/************************************************

 ************************************************/
void UKUITaskGroup::dragLeaveEvent(QDragLeaveEvent *event)
{
    // if draggind something into the taskgroup or the taskgroups' popup,
    // do not close the popup
    if (!sDraggging)
        setPopupVisible(false);
    UKUITaskButton::dragLeaveEvent(event);
}

void UKUITaskGroup::mouseMoveEvent(QMouseEvent* event)
{
    // if dragging the taskgroup, do not show the popup
    setPopupVisible(false, true);
    UKUITaskButton::mouseMoveEvent(event);
}

/************************************************

 ************************************************/
bool UKUITaskGroup::onWindowChanged(WId window, NET::Properties prop, NET::Properties2 prop2)
{ // returns true if the class is preserved
    bool needsRefreshVisibility{false};
    QVector<UKUITaskButton *> buttons;
    if (mButtonHash.contains(window))
        buttons.append(mButtonHash.value(window));

    // If group is based on that window properties must be changed also on button group
    if (window == windowId())
        buttons.append(this);

    if (!buttons.isEmpty())
    {
        // if class is changed the window won't belong to our group any more
        if (parentTaskBar()->isGroupingEnabled() && prop2.testFlag(NET::WM2WindowClass))
        {
            KWindowInfo info(window, 0, NET::WM2WindowClass);
            if (info.windowClassClass() != mGroupName)
            {
                onWindowRemoved(window);
                return false;
            }
        }
        // window changed virtual desktop
        if (prop.testFlag(NET::WMDesktop) || prop.testFlag(NET::WMGeometry))
        {
            if (parentTaskBar()->isShowOnlyOneDesktopTasks()
                    || parentTaskBar()->isShowOnlyCurrentScreenTasks())
            {
                needsRefreshVisibility = true;
            }
        }

        if (prop.testFlag(NET::WMVisibleName) || prop.testFlag(NET::WMName))
            std::for_each(buttons.begin(), buttons.end(), std::mem_fn(&UKUITaskButton::updateText));

        // XXX: we are setting window icon geometry -> don't need to handle NET::WMIconGeometry
        // Icon of the button can be based on windowClass
        if (prop.testFlag(NET::WMIcon) || prop2.testFlag(NET::WM2WindowClass))
            std::for_each(buttons.begin(), buttons.end(), std::mem_fn(&UKUITaskButton::updateIcon));

        if (prop.testFlag(NET::WMState))
        {
            KWindowInfo info{window, NET::WMState};
            if (info.hasState(NET::SkipTaskbar))
                onWindowRemoved(window);
            std::for_each(buttons.begin(), buttons.end(), std::bind(&UKUITaskButton::setUrgencyHint, std::placeholders::_1, info.hasState(NET::DemandsAttention)));

            if (parentTaskBar()->isShowOnlyMinimizedTasks())
            {
                needsRefreshVisibility = true;
            }
        }
    }

    if (needsRefreshVisibility)
        refreshVisibility();

    return true;
}

/************************************************

 ************************************************/
void UKUITaskGroup::groupPopupShown(UKUITaskGroup * const sender)
{
    //close all popups (should they be visible because of close delay)
    if (this != sender && isVisible())
            setPopupVisible(false, true/*fast*/);
}

void UKUITaskGroup::removeWidget()
{

}

void UKUITaskGroup::showPreview()
{
    XImage *img = NULL;
    Display *display = NULL;
    XWindowAttributes attr;
    //removeWidget();
    for (UKUITaskButtonHash::const_iterator it = mButtonHash.begin();it != mButtonHash.end();it++)
    {
        display = XOpenDisplay(NULL);
        XGetWindowAttributes(display, it.key(), &attr);
        img = XGetImage(display, it.key(), 0, 0, attr.width, attr.height, 0xffffffff,ZPixmap);

        QPixmap thumbnail = qimageFromXImage(img).scaled(THUMBNAIL_WIDTH,THUMBNAIL_HEIGHT,Qt::KeepAspectRatio,Qt::FastTransformation);
        thumbnail.save(QString("/tmp/picture/%1.png").arg(it.key()));
        //QLabel * label = new QLabel(mPopup); // 创建堆对象

        UKUITaskButton *btn = it.value();
        btn->setFixedSize(thumbnail.width(),thumbnail.height());
        btn->setIcon(thumbnail);
        btn->setIconSize(thumbnail.rect().size());

        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);/*not show title*/
        //btn->setStyleSheet(QString("border-image:url(/tmp/picture/%1.png)").arg(mButtonHash.begin().key()));
        //mPopup->addButton(btn);
//        mPopup->setLayout(new QHBoxLayout);
        mPopup->layout()->addWidget(btn);
        qDebug()<<"btn->text() is:"<<btn->text();
        XDestroyImage(img);
        XCloseDisplay(display);
    }
    plugin()->willShowWindow(mPopup);
    mPopup->show();

   emit popupShown(this);
}
