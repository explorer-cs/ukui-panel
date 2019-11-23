#ifndef STARTMENU_H
#define STARTMENU_H

#include "../panel/iukuipanelplugin.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFrame>
#include <QFontMetrics>
#include <QLineEdit>
#include <QToolButton>
#include <XdgIcon>


#include <QMainWindow>
#include <QHBoxLayout>
#include <QDebug>
#include <QProcess>

#include "../panel/plugin.h"
#include "../panel/ukuipanel.h"
#define DEFAULT_SHORTCUT "Alt+F1"


class  PowerSwitchWidget: public QFrame
{
    Q_OBJECT
public:
    PowerSwitchWidget(QWidget* parent = nullptr);
    ~PowerSwitchWidget();

    QLineEdit *lineEdit() { return &mLineEdit; }
    QToolButton *button() { return &mButton; }


protected:
    void mouseReleaseEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void captureMouse();

private:
    QLineEdit mLineEdit;
    QToolButton mButton;
    bool mCapturing;
};



class PowerSwitch : public QObject, public IUKUIPanelPlugin
{
    Q_OBJECT
public:
    PowerSwitch(const IUKUIPanelPluginStartupInfo &startupInfo);
    ~PowerSwitch();

    virtual QWidget *widget() { return &mWidget; }
    virtual QString themeId() const { return QStringLiteral("startmenu"); }
    void realign();
    virtual IUKUIPanelPlugin::Flags flags() const { return PreferRightAlignment | HaveConfigDialog ; }
private:
    PowerSwitchWidget mWidget;


};

class PowerSwitchLibrary: public QObject, public IUKUIPanelPluginLibrary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lxqt.org/Panel/PluginInterface/3.0")
    Q_INTERFACES(IUKUIPanelPluginLibrary)
public:
    IUKUIPanelPlugin *instance(const IUKUIPanelPluginStartupInfo &startupInfo) const
    {
        return new PowerSwitch(startupInfo);
    }
};

#endif
