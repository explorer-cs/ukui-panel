#include "startmenu.h"

#include "ui_startmenu.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QDesktopWidget>



StartMenu::StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    IUKUIPanelPlugin(startupInfo)
{
    realign();
}


StartMenu::~StartMenu()
{
}


void StartMenu::realign()
{
//    mWidget.button()->setFixedHeight(panel()->iconSize());
//    mWidget.button()->setFixedWidth(panel()->iconSize());
//    mWidget.lineEdit()->setFixedHeight(panel()->iconSize());
}

//void StartMenu::init_startmenu_window()
//{
//    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::SplashScreen);
////    this->setStyleSheet("background-color:#0e1316;");
////    this->setWindowOpacity(0.95);//设置总体透明度
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->setAutoFillBackground(false);
//    ui->mainToolBar->hide();
//    ui->menuBar->hide();
//    ui->statusBar->hide();
//    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
//    this->setMinimumSize(390,532);
//    this->setContentsMargins(0,0,0,0);

//    sidebarwid=new SideBarWidget();
//    mainviewwid=new MainViewWidget();
//    mainwidget=new QWidget();
//    mainwidget->setStyleSheet("background:transparent;");

//    this->setCentralWidget(mainwidget);
//    mainlayout=new QHBoxLayout;
//    mainlayout->addWidget(sidebarwid);
//    mainlayout->addWidget(mainviewwid);
//    mainlayout->setContentsMargins(0,0,0,0);
//    mainlayout->setSpacing(0);
//    centralWidget()->setLayout(mainlayout);

//    connect(sidebarwid, SIGNAL(send_commonusebtn_signal()), mainviewwid, SLOT(load_commonuse_widget()));
//    connect(sidebarwid,SIGNAL(send_letterbtn_signal()), mainviewwid, SLOT(load_letter_widget()));
//    connect(sidebarwid, SIGNAL(send_functionbtn_signal()), mainviewwid, SLOT(load_function_widget()));

//    connect(sidebarwid,SIGNAL(send_fullscreen_commonusebtn_signal()),
//            mainviewwid,SLOT(load_fullcommonuse_widget()));
//    connect(sidebarwid,SIGNAL(send_fullscreen_letterbtn_signal()),
//            mainviewwid,SLOT(load_fullletter_widget()));
//    connect(sidebarwid, SIGNAL(send_fullscreen_functionbtn_signal()),
//            mainviewwid, SLOT(load_fullfunction_widget()));

//    connect(mainviewwid,SIGNAL(send_fullscreenbtn_signal(int)),this,SLOT(show_fullscreen_widget(int)));
//    connect(mainviewwid, SIGNAL(send_defaultbtn_signal(int)),this,SLOT(show_default_widget(int)));
//}
