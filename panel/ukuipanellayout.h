#ifndef UKUIPANELLAYOUT_H
#define UKUIPANELLAYOUT_H

#include <QLayout>
#include <QList>
#include <QWidget>
#include <QLayoutItem>
#include "ilxqtpanel.h"
#include "lxqtpanelglobals.h"


class MoveInfo;
class QMouseEvent;
class QEvent;

class Plugin;
class LayoutItemGrid;

class UkuiPanelLayout : public QLayout
{
    Q_OBJECT
public:
    explicit UkuiPanelLayout(QWidget *parent);
    ~UkuiPanelLayout();

    void addItem(QLayoutItem *item);
    QLayoutItem *itemAt(int index) const;
    QLayoutItem *takeAt(int index);
    int count() const;
    void moveItem(int from, int to, bool withAnimation=false);

    QSize sizeHint() const;
    //QSize minimumSize() const;
    void setGeometry(const QRect &geometry);

    bool isHorizontal() const;

    void invalidate();

    int lineCount() const;
    void setLineCount(int value);

    int lineSize() const;
    void setLineSize(int value);

    ILXQtPanel::Position position() const { return mPosition; }
    void setPosition(ILXQtPanel::Position value);

    /*! \brief Force the layout to re-read items/plugins "static" configuration
     */
    void rebuild();

    static bool itemIsSeparate(QLayoutItem *item);
signals:
    void pluginMoved(Plugin * plugin);

public slots:
    void startMovePlugin();
    void finishMovePlugin();
    void moveUpPlugin(Plugin * plugin);
    void addPlugin(Plugin * plugin);

private:
    mutable QSize mMinPluginSize;
    LayoutItemGrid *mLeftGrid;
    LayoutItemGrid *mRightGrid;
    ILXQtPanel::Position mPosition;
    bool mAnimate;


    void setGeometryHoriz(const QRect &geometry);
    void setGeometryVert(const QRect &geometry);
    void globalIndexToLocal(int index, LayoutItemGrid **grid, int *gridIndex);
    void globalIndexToLocal(int index, LayoutItemGrid **grid, int *gridIndex) const;

    void setItemGeometry(QLayoutItem *item, const QRect &geometry, bool withAnimation);
};

#endif // UKUIPANELLAYOUT_H
