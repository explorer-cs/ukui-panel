#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include "../panel/iukuipanelplugin.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include "src/SideBarWidget/sidebarwidget.h"
#include "src/MainViewWidget/mainviewwidget.h"
#include "src/MainWindow/mainwindow.h"
#include <QDebug>

class StartMenu : public QObject, public IUKUIPanelPlugin
{
    Q_OBJECT

public:
    explicit StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo);
    ~StartMenu();
    QString themeId() const;
    QWidget *widget();
private:

    MainWindow      *mMainWindow;
};

class UKUIStartMenuLibrary: public QObject, public IUKUIPanelPluginLibrary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lxqt.org/Panel/PluginInterface/3.0")
    Q_INTERFACES(IUKUIPanelPluginLibrary)
public:
    IUKUIPanelPlugin *instance(const IUKUIPanelPluginStartupInfo &startupInfo) const
    {
        return new StartMenu(startupInfo);
    }
};
#endif // STARTMENU_H
