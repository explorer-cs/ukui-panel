#include "ukuipanel.h"
#include <KWindowSystem/KWindowSystem>
#include <LXQt/Settings>

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QX11Info>
#include <QDebug>
#include <QString>
#include <QDesktopWidget>
#include <QMenu>
#include <QPushButton>
#include <QMessageBox>
#include <QDropEvent>
#include <XdgIcon>
#include <XdgDirs>

#include "windownotifier.h"
#include "ukuipanelapplication.h"
#include"ukuimenu.h"
#include "config/configpaneldialog.h"


// Config keys and groups
#define CFG_KEY_SCREENNUM          "desktop"
#define CFG_KEY_POSITION           "position"
#define CFG_KEY_PANELSIZE          "panelSize"
#define CFG_KEY_ICONSIZE           "iconSize"
#define CFG_KEY_LINECNT            "lineCount"
#define CFG_KEY_LENGTH             "width"
#define CFG_KEY_PERCENT            "width-percent"
#define CFG_KEY_ALIGNMENT          "alignment"
#define CFG_KEY_FONTCOLOR          "font-color"
#define CFG_KEY_BACKGROUNDCOLOR    "background-color"
#define CFG_KEY_BACKGROUNDIMAGE    "background-image"
#define CFG_KEY_OPACITY            "opacity"
#define CFG_KEY_RESERVESPACE       "reserve-space"
#define CFG_KEY_PLUGINS            "plugins"
#define CFG_KEY_HIDABLE            "hidable"
#define CFG_KEY_VISIBLE_MARGIN     "visible-margin"
#define CFG_KEY_ANIMATION          "animation-duration"
#define CFG_KEY_SHOW_DELAY         "show-delay"
#define CFG_KEY_LOCKPANEL          "lockPanel"




UkuiPanel::UkuiPanel(const QString &configGroup,LXQt::Settings *settings) : 
	QFrame(),
    mSettings(settings),
    mConfigGroup(configGroup),
    mPanelSize(0),
    mIconSize(0),
    mLineCount(0),
    mLength(0),
    mAlignment(AlignmentLeft),
    mPosition(ILXQtPanel::PositionBottom),
    mScreenNum(0), //whatever (avoid conditional on uninitialized value)
    mActualScreenNum(0),
    mHidable(false),
    mVisibleMargin(true),
    mHidden(false),
    mAnimationTime(0),
    mReserveSpace(true),
    mAnimation(nullptr),
    mLockPanel(false)
{

    //LXQtPanel (inherits QFrame) -> lav (QGridLayout) -> LXQtPanelWidget (QFrame) -> LXQtPanelLayout
    mUkuiPanelWidget = new QFrame(this);
    mUkuiPanelWidget->setObjectName("BackgroundWidget");
    QGridLayout* lav = new QGridLayout();
    lav->setContentsMargins(0, 0, 0, 0);
    setLayout(lav);
    this->layout()->addWidget(mUkuiPanelWidget);
    QPushButton *button =new QPushButton("kkkkkkkkkkkkkkkkk");
//    this->layout()->addWidget(button);d


    mLayout = new UkuiPanelLayout(mUkuiPanelWidget);
    connect(mLayout, &UkuiPanelLayout::pluginMoved, this, &UkuiPanel::pluginMoved);

    if(mLayout == NULL){
	printf("button NULL-------------\n");
    } else{
	printf("button not NULL-------------\n");
    }
/*
   int left, top, right, bottom;
mLayout->getContentsMargins(&left,&top,&right,&bottom);
printf("left=%d\n",left);
printf("right=%d\n",right);
printf("top=%d\n",top);
printf("bottom=%d\n",bottom);

mLayout->setContentsMargins(0,0,400,40);
mLayout->getContentsMargins(&left,&top,&right,&bottom);
printf("left=%d\n",left);
printf("right=%d\n",right);
printf("top=%d\n",top);
printf("bottom=%d\n",bottom);
*/

//    mUkuiPanelWidget->setLayout(mLayout);
//
//QHBoxLayout *topLayout = new QHBoxLayout;
//QHBoxLayout *topLayout = new QHBoxLayout;

//topLayout->setContentsMargins(0,890,100,900);

//    topLayout->addWidget(button);
//    mUkuiPanelWidget->resize(40,40);
//    mUkuiPanelWidget->setLayout(topLayout);

//    this->setLayout(topLayout);
//    
    /*
    QVBoxLayout Q_V_L=new QVBoxLayout();
    Q_V_L->addLayout(topLayout);
    Q_V_L->setContentsMargins(0,0,0,0);
    mUkuiPanelWidget->setLayout(Q_V_L);
    this->setLayout(Q_V_L);
    */
//    mUkuiPanelWidget->layout()->addWidget(button);



    mLayout->setLineCount(mLineCount);
    qDebug()<< "UkuiPanel::UkuiPanel";
	Qt::WindowFlags flags = Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
	flags |= Qt::WindowDoesNotAcceptFocus;
	setWindowFlags(flags);
	setAttribute(Qt::WA_X11NetWmWindowTypeDock);
	setAttribute(Qt::WA_AlwaysShowToolTips);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_AcceptDrops);
	setWindowTitle("Ukui Panel");

	//添加插件
	loadPlugins();
	show();
}
UkuiPanel::~UkuiPanel()
{
}
void UkuiPanel::show()
{
    QWidget::show();
    KWindowSystem::setOnDesktop(effectiveWinId(), NET::OnAllDesktops);
}

bool UkuiPanel::event(QEvent *event)
{
    //qDebug() <<  "UkuiPanel::event";
    switch (event->type())
    {
    case QEvent::ContextMenu:
	//面板右击菜单项
       showUkuiMenu();
        break;

    case QEvent::LayoutRequest:
        qDebug() << "realign-7";
//        emit realigned();
        break;

    case QEvent::WinIdChange:
    {
        // qDebug() << "WinIdChange" << hex << effectiveWinId();
        if(effectiveWinId() == 0)
            break;


        KWindowSystem::setType(effectiveWinId(), NET::Dock);

        break;
    }
    case QEvent::DragEnter:
        dynamic_cast<QDropEvent *>(event)->setDropAction(Qt::IgnoreAction);
        event->accept();
    case QEvent::Enter:
        break;
    case QEvent::Leave:
    case QEvent::DragLeave:
//        hidePanel();
        break;

    default:
        break;
    }

    return QFrame::event(event);

}
void UkuiPanel::showEvent(QShowEvent *event)
{
	qDebug() << "UkuiPanel::showEvent";
    setPanelGeometry();
	updateWmStrut();
}
/*old ukui-panel*/
/*
void UkuiPanel::setPanelGeometry(bool animate)
{
	qDebug() << "UkuiPanel::setPanelGeometry";
	const QRect currentScreen = QApplication::desktop()->screenGeometry();
    	QRect rect;

        rect.setHeight(40);
        rect.setWidth(currentScreen.width());

	//任务栏位置设置
	rect.moveBottom(currentScreen.bottom());
//	rect.moveTop(currentScreen.top());	
        this->setGeometry(rect);

}
*/
/*  ok 但是任务栏显示的位置不对
void UkuiPanel::setPanelGeometry(bool animate)
{
    const QRect currentScreen = QApplication::desktop()->screenGeometry(mActualScreenNum);
    QRect rect;

    if (isHorizontal())
    {
        // Horiz panel ***************************
        rect.setHeight(qMax(16, mPanelSize));
        if (mLengthInPercents)
            rect.setWidth(currentScreen.width() * mLength / 100.0);
        else
        {
            if (mLength <= 0)
                rect.setWidth(currentScreen.width() + mLength);
            else
                rect.setWidth(mLength);
        }

        rect.setWidth(qMax(rect.size().width(), mLayout->minimumSize().width()));

        // Horiz ......................
        switch (mAlignment)
        {
        case UkuiPanel::AlignmentLeft:
            rect.moveLeft(currentScreen.left());
            break;

        case UkuiPanel::AlignmentCenter:
            rect.moveCenter(currentScreen.center());
            break;

        case UkuiPanel::AlignmentRight:
            rect.moveRight(currentScreen.right());
            break;
        }

        // Vert .......................
        if (mPosition == ILXQtPanel::PositionTop)
        {
            if (mHidden)
                rect.moveBottom(currentScreen.top() + 4 - 1);
            else
                rect.moveTop(currentScreen.top());
        }
        else
        {
            if (mHidden)
                rect.moveTop(currentScreen.bottom() - 4 + 1);
            else
                rect.moveBottom(currentScreen.bottom());
        }
    }
    else
    {
        // Vert panel ***************************
        rect.setWidth(qMax(16, mPanelSize));
        if (mLengthInPercents)
            rect.setHeight(currentScreen.height() * mLength / 100.0);
        else
        {
            if (mLength <= 0)
                rect.setHeight(currentScreen.height() + mLength);
            else
                rect.setHeight(mLength);
        }

        rect.setHeight(qMax(rect.size().height(), mLayout->minimumSize().height()));

        // Vert .......................
        switch (mAlignment)
        {
        case UkuiPanel::AlignmentLeft:
            rect.moveTop(currentScreen.top());
            break;

        case UkuiPanel::AlignmentCenter:
            rect.moveCenter(currentScreen.center());
            break;

        case UkuiPanel::AlignmentRight:
            rect.moveBottom(currentScreen.bottom());
            break;
        }

        // Horiz ......................
        if (mPosition == ILXQtPanel::PositionLeft)
        {
            if (mHidden)
                rect.moveRight(currentScreen.left() + 4 - 1);
            else
                rect.moveLeft(currentScreen.left());
        }
        else
        {
            if (mHidden)
                rect.moveLeft(currentScreen.right() - 4 + 1);
            else
                rect.moveRight(currentScreen.right());
        }
    }
    if (rect != geometry())
    {
        setFixedSize(rect.size());
        if (animate)
        {
            if (mAnimation == nullptr)
            {
                mAnimation = new QPropertyAnimation(this, "geometry");
                mAnimation->setEasingCurve(QEasingCurve::Linear);
                //Note: for hiding, the margins are set after animation is finished
                connect(mAnimation, &QAbstractAnimation::finished, [this] { if (mHidden) setMargins(); });
            }
            mAnimation->setDuration(mAnimationTime);
            mAnimation->setStartValue(geometry());
            mAnimation->setEndValue(rect);
            //Note: for showing-up, the margins are removed instantly
            if (!mHidden)
                setMargins();
            mAnimation->start();
        }
        else
        {
            setMargins();
            setGeometry(rect);
        }
    }
}
*/

void UkuiPanel::setPanelGeometry(bool animate)
{
    const QRect currentScreen = QApplication::desktop()->screenGeometry(mActualScreenNum);
    QRect rect;

    if (isHorizontal())
    {
        // Horiz panel ***************************
        rect.setHeight(qMax(PANEL_MINIMUM_SIZE, mPanelSize));
        if (mLengthInPercents)
            rect.setWidth(currentScreen.width() * mLength / 100.0);
        else
        {
            if (mLength <= 0)
                rect.setWidth(currentScreen.width() + mLength);
            else
                rect.setWidth(mLength);
        }

        rect.setWidth(qMax(rect.size().width(), mLayout->minimumSize().width()));

        // Horiz ......................
        switch (mAlignment)
        {
        case UkuiPanel::AlignmentLeft:
            rect.moveLeft(currentScreen.left());
            break;

        case UkuiPanel::AlignmentCenter:
            rect.moveCenter(currentScreen.center());
            break;

        case UkuiPanel::AlignmentRight:
            rect.moveRight(currentScreen.right());
            break;
        }

        // Vert .......................
        if (mPosition == ILXQtPanel::PositionTop)
        {
            if (mHidden)
                rect.moveBottom(currentScreen.top() + PANEL_HIDE_SIZE - 1);
            else
                rect.moveTop(currentScreen.top());
        }
        else
        {
            if (mHidden)
                rect.moveTop(currentScreen.bottom() - PANEL_HIDE_SIZE + 1);
            else
                rect.moveBottom(currentScreen.bottom());
        }
    }
    else
    {
        // Vert panel ***************************
        rect.setWidth(qMax(PANEL_MINIMUM_SIZE, mPanelSize));
        if (mLengthInPercents)
            rect.setHeight(currentScreen.height() * mLength / 100.0);
        else
        {
            if (mLength <= 0)
                rect.setHeight(currentScreen.height() + mLength);
            else
                rect.setHeight(mLength);
        }

        rect.setHeight(qMax(rect.size().height(), mLayout->minimumSize().height()));

        // Vert .......................
        switch (mAlignment)
        {
        case UkuiPanel::AlignmentLeft:
            rect.moveTop(currentScreen.top());
            break;

        case UkuiPanel::AlignmentCenter:
            rect.moveCenter(currentScreen.center());
            break;

        case UkuiPanel::AlignmentRight:
            rect.moveBottom(currentScreen.bottom());
            break;
        }

        // Horiz ......................
        if (mPosition == ILXQtPanel::PositionLeft)
        {
            if (mHidden)
                rect.moveRight(currentScreen.left() + PANEL_HIDE_SIZE - 1);
            else
                rect.moveLeft(currentScreen.left());
        }
        else
        {
            if (mHidden)
                rect.moveLeft(currentScreen.right() - PANEL_HIDE_SIZE + 1);
            else
                rect.moveRight(currentScreen.right());
        }
    }
    if (rect != geometry())
    {
        setFixedSize(rect.size());
        if (animate)
        {
            if (mAnimation == nullptr)
            {
                mAnimation = new QPropertyAnimation(this, "geometry");
                mAnimation->setEasingCurve(QEasingCurve::Linear);
                //Note: for hiding, the margins are set after animation is finished
                connect(mAnimation, &QAbstractAnimation::finished, [this] { if (mHidden) setMargins(); });
            }
            mAnimation->setDuration(mAnimationTime);
            mAnimation->setStartValue(geometry());
            mAnimation->setEndValue(rect);
            //Note: for showing-up, the margins are removed instantly
            if (!mHidden)
                setMargins();
            mAnimation->start();
        }
        else
        {
            setMargins();
            setGeometry(rect);
        }
    }
}
void UkuiPanel::setMargins()
{
    if (mHidden)
    {
        if (isHorizontal())
        {
            if (mPosition == ILXQtPanel::PositionTop)
                mLayout->setContentsMargins(0, 0, 0, 4);
            else
                mLayout->setContentsMargins(0, 4, 0, 0);
        }
        else
        {
            if (mPosition == ILXQtPanel::PositionLeft)
                mLayout->setContentsMargins(0, 0, 4, 0);
            else
                mLayout->setContentsMargins(4, 0, 0, 0);
        }
        if (!mVisibleMargin)
            setWindowOpacity(0.0);
    }
    else {
        mLayout->setContentsMargins(0, 0, 0, 0);
        if (!mVisibleMargin)
            setWindowOpacity(1.0);
    }
}

void UkuiPanel::updateWmStrut()
{
	WId wid = effectiveWinId();
	const QRect wholeScreen = QApplication::desktop()->geometry();
	const QRect rect = geometry();

	if(wid == 0 || !isVisible())
		return;

	//任务栏位置设置
	/*
	KWindowSystem::setExtendedStrut(wid,
                                        0, 0, 0,			//Left
                                        0, 0, 0,			//Right
                                        40, rect.left(), rect.right(),	//Top
                                        0, 0, 0				//Bottom
                                        );
	*/

    KWindowSystem::setExtendedStrut(wid,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    40, rect.left(), rect.right()
                                    );
	
}
QStringList UkuiPanel::pluginDesktopDirs()
{
    qDebug() << "UkuiPanel::pluginDesktopDirs";
    QStringList dirs;
    dirs << QString(getenv("LXQT_PANEL_PLUGINS_DIR")).split(':', QString::SkipEmptyParts);
    dirs << QString("%1/%2").arg(XdgDirs::dataHome(), "/lxqt/lxqt-panel");
    dirs << PLUGIN_DESKTOPS_DIR;
    dirs << PLUGIN_DESKTOPS_LOCAL_DIR;
    qDebug() << dirs;
    return dirs;
}
void UkuiPanel::loadPlugins()
{
    qDebug() << "UkuiPanel::loadPlugins";
	QString names_key(mConfigGroup);
	names_key += '/';
	names_key += QLatin1String(CFG_KEY_PLUGINS);	
	mPlugins.reset(new PanelPluginsModel(this, names_key, pluginDesktopDirs()));
    connect(mPlugins.data(), &PanelPluginsModel::pluginAdded, mLayout, &UkuiPanelLayout::addPlugin);
    connect(mPlugins.data(), &PanelPluginsModel::pluginMovedUp, mLayout, &UkuiPanelLayout::moveUpPlugin);
    //reemit signals
    connect(mPlugins.data(), &PanelPluginsModel::pluginAdded, this, &UkuiPanel::pluginAdded);
    connect(mPlugins.data(), &PanelPluginsModel::pluginRemoved, this, &UkuiPanel::pluginRemoved);

    const auto plugins = mPlugins->plugins();
    for (auto const & plugin : plugins)
    {
	    printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
        mLayout->addPlugin(plugin);
        this->layout()->addWidget(plugin);
        connect(plugin, &Plugin::dragLeft, [this] { mShowDelayTimer.stop(); hidePanel(); });
    }
}

void UkuiPanel::showUkuiMenu(Plugin *plugin)
{
    Ukuimenu * menu = new Ukuimenu(tr("Panel"), this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    menu->setIcon(XdgIcon::fromTheme("configure-toolbars"));


    if (plugin)
    {
        QMenu *m = plugin->ukuiMenu();

        if (m)
        {
            menu->addTitle(plugin->windowTitle());
            const auto actions = m->actions();
            for (auto const & action : actions)
            {
                action->setParent(menu);
                action->setDisabled(false);
                menu->addAction(action);
            }
            delete m;
        }
    }
    /*add menu*/
    menu->addTitle(QIcon(), tr("Panel"));
    menu->addAction(XdgIcon::fromTheme(QLatin1String("configure")),
                   tr("Configure Panel"),
                   this, SLOT(showConfigDialog())
                  )->setDisabled(false);

    menu->addAction(XdgIcon::fromTheme("preferences-plugin"),
                   tr("Manage Widgets"),
                   this, SLOT(showAddPluginDialog())
                  )->setDisabled(false);

    UkuiPanelApplication *app= reinterpret_cast<UkuiPanelApplication*>(qApp);
    menu->addAction(XdgIcon::fromTheme(QLatin1String("list-add")),
                   tr("Add New Panel"),
                   app, SLOT(addNewPanel())
                  );
    if (app->count() > 1)/*more than one panels,can remove panels*/
    {
        menu->addAction(XdgIcon::fromTheme(QLatin1String("list-remove")),
                       tr("Remove Panel", "Menu Item"),
                       this, SLOT(userRequestForDeletion())
                      )->setDisabled(false);
    }

    QAction * act_lock = menu->addAction(tr("Lock This Panel"));
    act_lock->setCheckable(true);
    act_lock->setChecked(false);
    connect(act_lock, &QAction::triggered, [this] { mLockPanel = !mLockPanel; saveSettings(false); });


    menu->setGeometry(calculatePopupWindowPos(QCursor::pos(), menu->sizeHint()));
    willShowWindow(menu);
    menu->show();
}

void UkuiPanel::willShowWindow(QWidget * w)
{
    mStandaloneWindows->observeWindow(w);
}


QRect UkuiPanel::calculatePopupWindowPos(QPoint const & absolutePos, QSize const & windowSize) const
{
    int x = absolutePos.x(), y = absolutePos.y();

    switch (position())
    {
    case ILXQtPanel::PositionTop:
        y = globalGeometry().bottom();
        break;

    case ILXQtPanel::PositionBottom:
        y = globalGeometry().top() - windowSize.height();
        break;

    case ILXQtPanel::PositionLeft:
        x = globalGeometry().right();
        break;

    case ILXQtPanel::PositionRight:
        x = globalGeometry().left() - windowSize.width();
        break;
    }
    QRect res(QPoint(x, y), windowSize);

    QRect screen = QApplication::desktop()->screenGeometry(this);
    // NOTE: We cannot use AvailableGeometry() which returns the work area here because when in a
    // multihead setup with different resolutions. In this case, the size of the work area is limited
    // by the smallest monitor and may be much smaller than the current screen and we will place the
    // menu at the wrong place. This is very bad for UX. So let's use the full size of the screen.
    if (res.right() > screen.right())
        res.moveRight(screen.right());

    if (res.bottom() > screen.bottom())
        res.moveBottom(screen.bottom());

    if (res.left() < screen.left())
        res.moveLeft(screen.left());

    if (res.top() < screen.top())
        res.moveTop(screen.top());

    return res;
}

QRect UkuiPanel::calculatePopupWindowPos(const ILXQtPanelPlugin *plugin, const QSize &windowSize) const
{
    return geometry();
}

void UkuiPanel::saveSettings(bool _bVar)
{
    mDelaySave.stop();
    if (_bVar)
    {
        mDelaySave.start();
        return;
    }

    mSettings->beginGroup(mConfigGroup);

    //Note: save/load of plugin names is completely handled by mPlugins object
    //mSettings->setValue(CFG_KEY_PLUGINS, mPlugins->pluginNames());

    mSettings->setValue(CFG_KEY_PANELSIZE, mPanelSize);
    mSettings->setValue(CFG_KEY_ICONSIZE, mIconSize);
    mSettings->setValue(CFG_KEY_LINECNT, mLineCount);

    mSettings->setValue(CFG_KEY_LENGTH, mLength);
    mSettings->setValue(CFG_KEY_PERCENT, mLengthInPercents);

    mSettings->setValue(CFG_KEY_SCREENNUM, mScreenNum);
    //mSettings->setValue(CFG_KEY_POSITION, positionToStr(mPosition));

    mSettings->setValue(CFG_KEY_ALIGNMENT, mAlignment);

    mSettings->setValue(CFG_KEY_FONTCOLOR, mFontColor.isValid() ? mFontColor : QColor());
    mSettings->setValue(CFG_KEY_BACKGROUNDCOLOR, mBackgroundColor.isValid() ? mBackgroundColor : QColor());
    mSettings->setValue(CFG_KEY_BACKGROUNDIMAGE, QFileInfo(mBackgroundImage).exists() ? mBackgroundImage : QString());
    mSettings->setValue(CFG_KEY_OPACITY, mOpacity);
    mSettings->setValue(CFG_KEY_RESERVESPACE, mReserveSpace);

    mSettings->setValue(CFG_KEY_HIDABLE, mHidable);
    mSettings->setValue(CFG_KEY_VISIBLE_MARGIN, mVisibleMargin);
    mSettings->setValue(CFG_KEY_ANIMATION, mAnimationTime);
    mSettings->setValue(CFG_KEY_SHOW_DELAY, mShowDelayTimer.interval());

    mSettings->setValue(CFG_KEY_LOCKPANEL, mLockPanel);

    mSettings->endGroup();
}

void UkuiPanel::showConfigDialog()
{
    if (mConfigDialog.isNull())
        mConfigDialog = new ConfigPanelDialog(this, nullptr /*make it top level window*/);

    mConfigDialog->showConfigPanelPage();
    mStandaloneWindows->observeWindow(mConfigDialog.data());
    mConfigDialog->show();
    mConfigDialog->raise();
    mConfigDialog->activateWindow();
    WId wid = mConfigDialog->windowHandle()->winId();

    KWindowSystem::activateWindow(wid);
    KWindowSystem::setOnDesktop(wid, KWindowSystem::currentDesktop());
}


bool UkuiPanel::canPlacedOn(int screenNum, UkuiPanel::Position position)
{
    QDesktopWidget* dw = QApplication::desktop();

    switch (position)
    {
    case UkuiPanel::PositionTop:
        for (int i = 0; i < dw->screenCount(); ++i)
            if (dw->screenGeometry(i).bottom() < dw->screenGeometry(screenNum).top())
                return false;
        return true;

    case UkuiPanel::PositionBottom:
        for (int i = 0; i < dw->screenCount(); ++i)
            if (dw->screenGeometry(i).top() > dw->screenGeometry(screenNum).bottom())
                return false;
        return true;

    case UkuiPanel::PositionLeft:
        for (int i = 0; i < dw->screenCount(); ++i)
            if (dw->screenGeometry(i).right() < dw->screenGeometry(screenNum).left())
                return false;
        return true;

    case UkuiPanel::PositionRight:
        for (int i = 0; i < dw->screenCount(); ++i)
            if (dw->screenGeometry(i).left() > dw->screenGeometry(screenNum).right())
                return false;
        return true;
    }

    return false;
}


/************************************************

 ************************************************/
void UkuiPanel::setPanelSize(int value, bool save)
{
    if (mPanelSize != value)
    {
        mPanelSize = value;
        realign();

        if (save)
            saveSettings(true);
    }
}

void UkuiPanel::realign()
{
    if (!isVisible())
        return;
    setPanelGeometry();

    // Reserve our space on the screen ..........
    // It's possible that our geometry is not changed, but screen resolution is changed,
    // so resetting WM_STRUT is still needed. To make it simple, we always do it.
    updateWmStrut();
}


void UkuiPanel::showAddPluginDialog()
{
    if (mConfigDialog.isNull())
        mConfigDialog = new ConfigPanelDialog(this, nullptr /*make it top level window*/);

    mConfigDialog->showConfigPluginsPage();
    mStandaloneWindows->observeWindow(mConfigDialog.data());
    mConfigDialog->show();
    mConfigDialog->raise();
    mConfigDialog->activateWindow();
    WId wid = mConfigDialog->windowHandle()->winId();

    KWindowSystem::activateWindow(wid);
    KWindowSystem::setOnDesktop(wid, KWindowSystem::currentDesktop());
}

void UkuiPanel::setReserveSpace(bool reserveSpace, bool save)
{
    if (mReserveSpace == reserveSpace)
        return;

    mReserveSpace = reserveSpace;

    if (save)
        saveSettings(true);

    updateWmStrut();
}


bool UkuiPanel::isPluginSingletonAndRunnig(QString const & pluginId) const
{
    Plugin const * plugin = mPlugins->pluginByID(pluginId);
    if (nullptr == plugin)
        return false;
    else
        return plugin->iPlugin()->flags().testFlag(ILXQtPanelPlugin::SingleInstance);
}

 QRect UkuiPanel::globalGeometry() const
 {
     return geometry();
 }

 void UkuiPanel::pluginFlagsChanged(const ILXQtPanelPlugin * plugin)
 {

 }

 void UkuiPanel::hidePanel()
 {
     if (mHidable && !mHidden
             && !mStandaloneWindows->isAnyWindowShown()
        )
         mHideTimer.start();
 }

 void UkuiPanel::pluginMoved(Plugin * plug)
 {
     //get new position of the moved plugin
     bool found{false};
     QString plug_is_before;
    /* for (int i=0; i<mLayout->count(); ++i)
     {
         Plugin *plugin = qobject_cast<Plugin*>(mLayout->itemAt(i)->widget());
         if (plugin)
         {
             if (found)
             {
                 //we found our plugin in previous cycle -> is before this (or empty as last)
                 plug_is_before = plugin->settingsGroup();
                 break;
             } else
                 found = (plug == plugin);
         }
     }
     mPlugins->movePlugin(plug, plug_is_before);
     */
 }


 void UkuiPanel::setIconSize(int value, bool save)
 {
     if (mIconSize != value)
     {
         mIconSize = value;
         updateStyleSheet();
         mLayout->setLineSize(mIconSize);

         if (save)
             saveSettings(true);

         realign();
     }
 }


 /************************************************

  ************************************************/
 void UkuiPanel::setLineCount(int value, bool save)
 {
     if (mLineCount != value)
     {
         mLineCount = value;
         mLayout->setEnabled(false);
         mLayout->setLineCount(mLineCount);
         mLayout->setEnabled(true);

         if (save)
             saveSettings(true);

         realign();
     }
 }


 /************************************************

  ************************************************/
 void UkuiPanel::setLength(int length, bool inPercents, bool save)
 {
     if (mLength == length &&
             mLengthInPercents == inPercents)
         return;

     mLength = length;
     mLengthInPercents = inPercents;

     if (save)
         saveSettings(true);

     realign();
 }


 /************************************************

  ************************************************/
 void UkuiPanel::setPosition(int screen, UkuiPanel::Position position, bool save)
 {
     if (mScreenNum == screen &&
             mPosition == position)
         return;

     mActualScreenNum = screen;
     mPosition = position;
     mLayout->setPosition(mPosition);

     if (save)
     {
         mScreenNum = screen;
         saveSettings(true);
     }

     // Qt 5 adds a new class QScreen and add API for setting the screen of a QWindow.
     // so we had better use it. However, without this, our program should still work
     // as long as XRandR is used. Since XRandR combined all screens into a large virtual desktop
     // every screen and their virtual siblings are actually on the same virtual desktop.
     // So things still work if we don't set the screen correctly, but this is not the case
     // for other backends, such as the upcoming wayland support. Hence it's better to set it.
     if(windowHandle())
     {
         // QScreen* newScreen = qApp->screens().at(screen);
         // QScreen* oldScreen = windowHandle()->screen();
         // const bool shouldRecreate = windowHandle()->handle() && !(oldScreen && oldScreen->virtualSiblings().contains(newScreen));
         // Q_ASSERT(shouldRecreate == false);

         // NOTE: When you move a window to another screen, Qt 5 might recreate the window as needed
         // But luckily, this never happen in XRandR, so Qt bug #40681 is not triggered here.
         // (The only exception is when the old screen is destroyed, Qt always re-create the window and
         // this corner case triggers #40681.)
         // When using other kind of multihead settings, such as Xinerama, this might be different and
         // unless Qt developers can fix their bug, we have no way to workaround that.
         windowHandle()->setScreen(qApp->screens().at(screen));
     }

     realign();
 }

 /************************************************
  *
  ************************************************/
 void UkuiPanel::setAlignment(Alignment value, bool save)
 {
     if (mAlignment == value)
         return;

     mAlignment = value;

     if (save)
         saveSettings(true);

     realign();
 }

 /************************************************
  *
  ************************************************/
 void UkuiPanel::setFontColor(QColor color, bool save)
 {
     mFontColor = color;
     updateStyleSheet();

     if (save)
         saveSettings(true);
 }

 /************************************************

  ************************************************/
 void UkuiPanel::setBackgroundColor(QColor color, bool save)
 {
     mBackgroundColor = color;
     updateStyleSheet();

     if (save)
         saveSettings(true);
 }

 /************************************************

  ************************************************/
 void UkuiPanel::setBackgroundImage(QString path, bool save)
 {
     mBackgroundImage = path;
     updateStyleSheet();

     if (save)
         saveSettings(true);
 }


 /************************************************
  *
  ************************************************/
 void UkuiPanel::setOpacity(int opacity, bool save)
 {
     mOpacity = opacity;
     updateStyleSheet();

     if (save)
         saveSettings(true);
 }


 void UkuiPanel::updateStyleSheet()
 {
     QStringList sheet;
     sheet << QString("Plugin > QAbstractButton, LXQtTray { qproperty-iconSize: %1px %1px; }").arg(mIconSize);
     sheet << QString("Plugin > * > QAbstractButton, TrayIcon { qproperty-iconSize: %1px %1px; }").arg(mIconSize);

     if (mFontColor.isValid())
         sheet << QString("Plugin * { color: " + mFontColor.name() + "; }");

     QString object = mUkuiPanelWidget->objectName();

     if (mBackgroundColor.isValid())
     {
         QString color = QString("%1, %2, %3, %4")
             .arg(mBackgroundColor.red())
             .arg(mBackgroundColor.green())
             .arg(mBackgroundColor.blue())
             .arg((float) mOpacity / 100);
         sheet << QString("UkuiPanel #BackgroundWidget { background-color: rgba(" + color + "); }");
     }

     if (QFileInfo(mBackgroundImage).exists())
         sheet << QString("UkuiPanel #BackgroundWidget { background-image: url('" + mBackgroundImage + "');}");

     setStyleSheet(sheet.join("\n"));
 }

 void UkuiPanel::setVisibleMargin(bool visibleMargin, bool save)
 {
     if (mVisibleMargin == visibleMargin)
         return;

     mVisibleMargin = visibleMargin;

     if (save)
         saveSettings(true);

     realign();
 }


 void UkuiPanel::setAnimationTime(int animationTime, bool save)
 {
     if (mAnimationTime == animationTime)
         return;

     mAnimationTime = animationTime;

     if (save)
         saveSettings(true);
 }

 void UkuiPanel::setShowDelay(int showDelay, bool save)
 {
     if (mShowDelayTimer.interval() == showDelay)
         return;

     mShowDelayTimer.setInterval(showDelay);

     if (save)
         saveSettings(true);
 }


 void UkuiPanel::setHidable(bool hidable, bool save)
 {
     if (mHidable == hidable)
         return;

     mHidable = hidable;

     if (save)
         saveSettings(true);

     realign();
 }

 void UkuiPanel::setIconTheme(const QString& iconTheme)
 {
     UkuiPanelApplication *a = reinterpret_cast<UkuiPanelApplication*>(qApp);
     a->setIconTheme(iconTheme);
 }


 void UkuiPanel::updateConfigDialog() const
 {
     if (!mConfigDialog.isNull() && mConfigDialog->isVisible())
     {
         mConfigDialog->updateIconThemeSettings();
         const QList<QWidget*> widgets = mConfigDialog->findChildren<QWidget*>();
         for (QWidget *widget : widgets)
             widget->update();
     }
 }




