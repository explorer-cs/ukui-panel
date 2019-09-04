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


#include "src/SideBarWidget/sidebarwidget.h"
#include "src/MainViewWidget/mainviewwidget.h"
#include "src/MainWindow/mainwindow.h"




#include <QMainWindow>
#include <QHBoxLayout>
#include <QDebug>

class StartMenuWidget: public QFrame
{
    Q_OBJECT
public:
    StartMenuWidget(QWidget* parent = nullptr);
    ~StartMenuWidget();

    QLineEdit *lineEdit() { return &mLineEdit; }
    QToolButton *button() { return &mButton; }


protected:
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void captureMouse();

private:
    QLineEdit mLineEdit;
    QToolButton mButton;
    bool mCapturing;
    MainWindow      *mMainWindow;
};



class StartMenu : public QObject, public IUKUIPanelPlugin
{
    Q_OBJECT
public:
    StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo);
    ~StartMenu();

    virtual QWidget *widget() { return &mWidget; }

    virtual QString themeId() const { return QStringLiteral("startmenu"); }

    bool isSeparate() const { return true; }

    void realign();

private:
    StartMenuWidget mWidget;

};

class ColorPickerLibrary: public QObject, public IUKUIPanelPluginLibrary
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

#endif
