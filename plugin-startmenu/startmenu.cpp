#include "startmenu.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

#include <lxqt-globalkeys.h>

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
//    QSize size;
//    size.setHeight(40);
//    size.setWidth(40);
//    mWidget.button()->setFixedHeight(40);
//    mWidget.button()->setIconSize(size);
//    mWidget.button()->setFixedWidth(60);
//      mWidget.lineEdit()->setFixedHeight(80);

}

StartMenuWidget::StartMenuWidget(QWidget *parent):
    QFrame(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins (0, 0, 0, 0);
    layout->setSpacing (1);
    setLayout(layout);
    layout->addWidget (&mButton);
    layout->addWidget(&mButton2);


    //mButton.setAutoRaise(true);
    mButton.setFixedSize(60,40);
    mButton2.setFixedSize(40,40);



    mCapturing = false;
    connect(&mButton, SIGNAL(clicked()), this, SLOT(captureMouse()));

    mButton.setStyleSheet(
                //正常状态样式
                "QToolButton{"
                /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
                "qproperty-icon:url(/usr/share/plugin-startmenu/img/startmenu.svg);"
                "qproperty-iconSize:40px 40px;"
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:0px;"                     //边框宽度像素
                "border-radius:0px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "font:SimSun 14px;"                       //字体，字体大小
                "color:rgba(0,0,0,100);"                //字体颜色
                "padding:0px;"                          //填衬
                "border-bottom-style:solid"
                "}"
                //鼠标悬停样式
                "QToolButton:hover{"
                "background-color:rgba(190,216,239,20%);"
                "}"
                //鼠标按下样式
                "QToolButton:pressed{"
                "background-color:rgba(190,216,239,12%);"
                "}"
                );
    mButton2.setStyleSheet(
                //正常状态样式
                "QToolButton{"
                /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
                "qproperty-icon:url(/usr/share/plugin-startmenu/img/taskview.svg);"
                "qproperty-iconSize:24px 24px;"
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:0px;"                     //边框宽度像素
                "border-radius:0px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "font:bold 14px;"                       //字体，字体大小
                "color:rgba(0,0,0,100);"                //字体颜色
                "padding:0px;"                          //填衬
                "}"
                //鼠标悬停样式
                "QToolButton:hover{"
                "background-color:rgba(190,216,239,20%);"
                "}"
                //鼠标按下样式
                "QToolButton:pressed{"
                "background-color:rgba(190,216,239,12%);"
                "}"
                );
}




StartMenuWidget::~StartMenuWidget()
{
}


void StartMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{
//    if (!mCapturing)
//        return;
//    WId id = QApplication::desktop()->winId();
//    qDebug()<<id<<endl;
}


void StartMenuWidget::captureMouse()
{
    if(QFileInfo::exists(QString("/usr/bin/ukui-menu")))
    {
    QProcess *process =new QProcess(this);
    process->startDetached("/usr/bin/ukui-menu");
    }
    else{qDebug()<<"not find /usr/bin/ukui-start-menu"<<endl;}
}

void StartMenuWidget::contextMenuEvent(QContextMenuEvent *event) {
  //创建一个菜单 添加事件
qDebug()<<"contextMenuEvent    right press event";
st_menu=new QMenu;
st_menu->setContextMenuPolicy(Qt::CustomContextMenu);

st_menu->setStyleSheet(
                     "QMenu {"
                     "background-color:rgb(21,26,30);"
                     "border-color:rgba(255,255,255,30);"    //边框颜色
                     "font:SimSun 14px;"                       //字体，字体大小
                     "color:rgba(255,255,255,100);"                //字体颜色
                    " }"

                    //鼠标悬停样式
                    "QMenu:hover{"
                    "background-color:rgba(190,216,239,30%);"
                    "}"
                    //鼠标按下样式
                    "QMenu:selected{"
                    "background-color:rgba(190,216,239,30%);"
                    "}"
                    );
QAction *act_1;
act_1=new QAction(this);
act_1->setText("任务栏布局");
QAction *act_2;
act_2=new QAction(this);
act_2->setText("设置任务栏");

// connect(act_2,SIGNAL(triggered(bool)),this,SLOT(configpanel()));
QAction *act_3;
act_3=new QAction(this);
act_3->setText("编辑分类菜单");
QAction *act_4;
act_4=new QAction(this);
act_4->setText("控制面板");
QAction *act_5;
act_5=new QAction(this);
act_5->setText("文件管理器");
QAction *act_6;
act_6=new QAction(this);
act_6->setText("命令行");
QAction *act_7;
act_7=new QAction(this);
act_7->setText("关机或注销");
QAction *act_8;
act_8=new QAction(this);
act_8->setText("显示桌面");
st_menu->addAction(act_1);
st_menu->addAction(act_2);
st_menu->addAction(act_3);
st_menu->addAction(act_4);
st_menu->addAction(act_5);
st_menu->addAction(act_6);
st_menu->addAction(act_7);
st_menu->addAction(act_8);
st_menu->exec(QCursor::pos());




}

void StartMenuWidget::configpanel()
{
//    mConfigDialog = new ConfigPanelDialog(this, nullptr);
//    mConfigDialog->show();


//    ConfigPanelWidget *mPanelPage;
//    UKUIPanel *falsepanel;
//    mPanelPage = new ConfigPanelWidget(falsepanel, this);

}
