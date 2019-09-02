#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "src/SideBarWidget/sidebarwidget.h"
#include "src/MainViewWidget/mainviewwidget.h"
#include "../panel/iukuipanelplugin.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFrame>
#include <QFontMetrics>
#include <QLineEdit>
#include <QToolButton>
#include <XdgIcon>
namespace Ui {
class StartMenu;
}
class StartMenu : public QObject, public IUKUIPanelPlugin
{
    Q_OBJECT
public:
    StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo);
    ~StartMenu();

    virtual QWidget *widget() { return &mWidget; }
    virtual QString themeId() const { return QStringLiteral("ColorPicker"); }

    bool isSeparate() const { return true; }

    void realign();
    QLineEdit *lineEdit() { return &mLineEdit; }
    QToolButton *button() { return &mButton; }


private:
    QWidget mWidget;
    QLineEdit mLineEdit;
    QToolButton mButton;
};

class StartMenuLibrary: public QObject, public IUKUIPanelPluginLibrary
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "lxqt.org/Panel/PluginInterface/3.0")
    Q_INTERFACES(IUKUIPanelPluginLibrary)
public:
    IUKUIPanelPlugin *instance(const IUKUIPanelPluginStartupInfo &startupInfo) const
    {
        return new StartMenu(startupInfo);
    }
protected:
    void init_startmenu_window();

};

#endif // MAINWINDOW_H
