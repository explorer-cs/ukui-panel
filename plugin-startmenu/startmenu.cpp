#include "startmenu.h"
#include "ui_startmenu.h"
#include <QDebug>


StartMenu::StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    IUKUIPanelPlugin(startupInfo),
    mMainWindow(NULL)
{
    mMainWindow = new MainWindow;
    if(mMainWindow != NULL)
    {
        mMainWindow->setGeometry(QRect(0,QApplication::desktop()->availableGeometry().height()-532,390,532));
        mMainWindow->show();
        mMainWindow->raise();
        mMainWindow->activateWindow();
    }

}

StartMenu::~StartMenu()
{
    if(mMainWindow != NULL)
    {
        delete mMainWindow;
        mMainWindow = NULL;
    }
}


QString StartMenu:: themeId() const
{
    return "";
}
QWidget *StartMenu::widget()
{
    return NULL;
}


