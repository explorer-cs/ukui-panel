#include "startmenu.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

StartMenu::StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    IUKUIPanelPlugin(startupInfo)
{
    realign();
    mCapturing = false;
    connect(&mButton, SIGNAL(clicked()), this, SLOT(captureMouse()));

//    new FilectrlAdaptor(this);
//    QDBusConnection con=QDBusConnection::sessionBus();
//    if(!con.registerService("com.ukui.panel.position") ||
//            !con.registerObject("/pos",this))
//    {
//        qDebug()<<"fail";
//    }



}


StartMenu::~StartMenu()
{
}


void StartMenu::realign()
{
    mButton.setFixedSize(panel()->panelSize(),panel()->panelSize());
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
    qDebug()<<"mPlugin->panel()->position():"<<mPlugin->panel()->position();


}

void StartMenu::captureMouse()
{
    if(QFileInfo::exists(QString("/usr/bin/ukui-menu")))
    {
    QProcess *process =new QProcess(this);
    process->startDetached("/usr/bin/ukui-menu");
    }
    else{qDebug()<<"not find /usr/bin/ukui-start-menu"<<endl;}
}
bool StartMenu::GetPanelPosition(QString arg)
{
    qDebug()<<"AddToTaskbar   d-bus";
    return true;
}
/*
 * Implementation of adaptor class FilectrlAdaptor
 */

//FilectrlAdaptor::FilectrlAdaptor(QObject *parent)
//    : QDBusAbstractAdaptor(parent)
//{
//    // constructor
//    setAutoRelaySignals(true);
//}

//FilectrlAdaptor::~FilectrlAdaptor()
//{
//    // destructor
//}

//bool FilectrlAdaptor::GetPanelPosition(const QString &arg)
//{
//    // handle method call com.kylin.security.controller.filectrl.GetPanelPosition
//    bool out0;
//    QMetaObject::invokeMethod(parent(), "GetPanelPosition", Q_RETURN_ARG(bool, out0), Q_ARG(QString, arg));
//    emit addtak(3);
//    return out0;
//}
