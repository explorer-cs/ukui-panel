#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include "../panel/iukuipanelplugin.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include "src/SideBarWidget/sidebarwidget.h"
#include "src/MainViewWidget/mainviewwidget.h"
namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow, public IUKUIPanelPlugin
{
    Q_OBJECT

public:
    explicit StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo);
    ~StartMenu();
    QString themeId() const;
    QWidget *widget();
private:
    Ui::StartMenu *ui;
    //主窗口样式
    QWidget* mainwidget=NULL;
    QHBoxLayout* mainlayout=NULL;

    //侧边栏
    SideBarWidget* sidebarwid=NULL;

    //主视图
    MainViewWidget* mainviewwid=NULL;

protected:
    void init_mainwindow();

    bool event(QEvent *event);//鼠标点击窗口外部事件

private slots:
    /**
     * @显示全屏窗口
     * @param arg分类窗口编号
     */
    void show_fullscreen_widget(int arg);
    /**
     * @显示默认(还原)窗口
     * @param arg分类窗口编号
     */
    void show_default_widget(int arg);
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
