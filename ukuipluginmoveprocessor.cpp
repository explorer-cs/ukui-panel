#include "ukuipluginmoveprocessor.h"

#include "plugin.h"
#include "panel/ukuipanellayout.h"
#include <QMouseEvent>


/************************************************

 ************************************************/
UkuiPluginMoveProcessor::UkuiPluginMoveProcessor(UkuiPanelLayout *layout, Plugin *plugin):
    QWidget(plugin),
    mLayout(layout),
    mPlugin(plugin)
{
    mDestIndex = mLayout->indexOf(plugin);

    grabKeyboard();
}


/************************************************

 ************************************************/
UkuiPluginMoveProcessor::~UkuiPluginMoveProcessor()
{
}


/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::start()
{
    // We have not memoryleaks there.
    // The animation will be automatically deleted when stopped.
    CursorAnimation *cursorAnimation = new CursorAnimation();
    connect(cursorAnimation, SIGNAL(finished()), this, SLOT(doStart()));
    cursorAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    cursorAnimation->setDuration(150);

    cursorAnimation->setStartValue(QCursor::pos());
    cursorAnimation->setEndValue(mPlugin->mapToGlobal(mPlugin->rect().center()));
    cursorAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}


/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::doStart()
{
    setMouseTracking(true);
    show(); //  Only visible widgets can grab mouse input.
    grabMouse(mLayout->isHorizontal() ? Qt::SizeHorCursor : Qt::SizeVerCursor);
}


/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mouse = mLayout->parentWidget()->mapFromGlobal(event->globalPos());

    MousePosInfo pos = itemByMousePos(mouse);

    QLayoutItem *prevItem = 0;
    QLayoutItem *nextItem = 0;
    if (pos.after)
    {
        mDestIndex = pos.index + 1;
        prevItem = pos.item;
        nextItem = mLayout->itemAt(pos.index + 1);
    }
    else
    {
        prevItem = mLayout->itemAt(pos.index - 1);
        nextItem = pos.item;
        mDestIndex = pos.index;
    }

    bool plugSep = mPlugin->isSeparate();
    bool prevSep = UkuiPanelLayout::itemIsSeparate(prevItem);
    bool nextSep = UkuiPanelLayout::itemIsSeparate(nextItem);

    if (!nextItem)
    {
        if (mLayout->isHorizontal())
            drawMark(prevItem, prevSep ? RightMark : BottomMark);
        else
            drawMark(prevItem, prevSep ? BottomMark : RightMark);
        return;
    }

    if (mLayout->lineCount() == 1)
    {
        if (mLayout->isHorizontal())
            drawMark(nextItem, LeftMark);
        else
            drawMark(nextItem, TopMark);
        return;
    }


    if (!prevItem)
    {
        if (mLayout->isHorizontal())
            drawMark(nextItem, nextSep ? LeftMark : TopMark);
        else
            drawMark(nextItem, nextSep ? TopMark : LeftMark);
        return;
    }

    // We prefer to draw line at the top/left of next item.
    // But if next item and moved plugin have different types (separate an not) and
    // previous item hase same type as moved plugin we draw line at the end of previous one.
    if (plugSep != nextSep && plugSep == prevSep)
    {
        if (mLayout->isHorizontal())
            drawMark(prevItem, prevSep ? RightMark : BottomMark);
        else
            drawMark(prevItem, prevSep ? BottomMark : RightMark);
    }
    else
    {
        if (mLayout->isHorizontal())
            drawMark(nextItem, nextSep ? LeftMark : TopMark);
        else
            drawMark(nextItem, nextSep ? TopMark : LeftMark);
    }
}


/************************************************

 ************************************************/
UkuiPluginMoveProcessor::MousePosInfo UkuiPluginMoveProcessor::itemByMousePos(const QPoint mouse) const
{
    MousePosInfo ret;

    for (int i = mLayout->count()-1; i > -1; --i)
    {
        QLayoutItem *item = mLayout->itemAt(i);
        QRect itemRect = item->geometry();
        if (mouse.x() > itemRect.left() &&
            mouse.y() > itemRect.top())
        {

            ret.index = i;
            ret.item = item;
            if (mLayout->isHorizontal())
            {
                ret.after = UkuiPanelLayout::itemIsSeparate(item) ?
                        mouse.x() > itemRect.center().x() :
                        mouse.y() > itemRect.center().y() ;
            }
            else
            {
                ret.after = UkuiPanelLayout::itemIsSeparate(item) ?
                        mouse.y() > itemRect.center().y() :
                        mouse.x() > itemRect.center().x() ;
            }
            return ret;
        }
    }

    ret.index = 0;
    ret.item = mLayout->itemAt(0);
    ret.after = false;
    return ret;
}


/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::drawMark(QLayoutItem *item, MarkType markType)
{
    QWidget *widget = (item) ? item->widget() : 0;

    static QWidget *prevWidget = 0;
    if (prevWidget && prevWidget != widget)
        prevWidget->setStyleSheet("");

    prevWidget = widget;

    if (!widget)
        return;

    QString border1;
    QString border2;
    switch(markType)
    {
    case TopMark:
        border1 = "top";
        border2 = "bottom";
        break;

    case BottomMark:
        border1 = "bottom";
        border2 = "top";
        break;

    case LeftMark:
        border1 = "left";
        border2 = "right";
        break;

    case RightMark:
        border1 = "right";
        border2 = "left";
        break;

    }

    widget->setStyleSheet(QString("#%1 {"
                                  "border-%2: 2px solid rgba(%4, %5, %6, %7); "
                                  "border-%3: -2px solid; "
                                  "background-color: transparent; }")
                          .arg(widget->objectName())
                          .arg(border1)
                          .arg(border2)
                          .arg(Plugin::moveMarkerColor().red())
                          .arg(Plugin::moveMarkerColor().green())
                          .arg(Plugin::moveMarkerColor().blue())
                          .arg(Plugin::moveMarkerColor().alpha())
                          );
}


/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}


/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    releaseMouse();
    setMouseTracking(false);
    doFinish(false);
}

/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        doFinish(true);
        return;
    }
    QWidget::keyPressEvent(event);
}

/************************************************

 ************************************************/
void UkuiPluginMoveProcessor::doFinish(bool cancel)
{
    releaseKeyboard();

    drawMark(0, TopMark);

    if (!cancel)
    {
        int currentIdx = mLayout->indexOf(mPlugin);
        if (currentIdx == mDestIndex)
            return;

        if (mDestIndex > currentIdx)
            mDestIndex--;

        mLayout->moveItem(currentIdx, mDestIndex, true);
    }

    emit finished();
    deleteLater();
}
