#ifndef UKUIPLUGINMOVEPROCESSOR_H
#define UKUIPLUGINMOVEPROCESSOR_H

#include <QWidget>
#include <QVariantAnimation>
#include <QEvent>
#include "plugin.h"
#include "lxqtpanelglobals.h"

/*declare class*/
class UkuiPanelLayout;
class QLayoutItem;

class UkuiPluginMoveProcessor : public QWidget
{
    Q_OBJECT
public:
    explicit UkuiPluginMoveProcessor(UkuiPanelLayout *layout, Plugin *plugin);
    ~UkuiPluginMoveProcessor();

    Plugin *plugin() const { return mPlugin; }

signals:
    void finished();

public slots:
    void start();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void doStart();
    void doFinish(bool cancel);

private:
    enum MarkType
    {
        TopMark,
        BottomMark,
        LeftMark,
        RightMark
    };

    struct MousePosInfo
    {
        int index;
        QLayoutItem *item;
        bool after;
    };

    UkuiPanelLayout *mLayout;
    Plugin *mPlugin;
    int mDestIndex;

    MousePosInfo itemByMousePos(const QPoint mouse) const;
    void drawMark(QLayoutItem *item, MarkType markType);

signals:

public slots:
};

class CursorAnimation: public QVariantAnimation
{
    Q_OBJECT
public:
    void updateCurrentValue(const QVariant &value) { QCursor::setPos(value.toPoint()); }
};

#endif // UKUIPLUGINMOVEPROCESSOR_H
