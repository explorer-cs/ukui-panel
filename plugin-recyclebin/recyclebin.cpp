#include "recyclebin.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

#include <lxqt-globalkeys.h>

RecycleBin::RecycleBin(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    IUKUIPanelPlugin(startupInfo)
{
    realign();

}


RecycleBin::~RecycleBin()
{
}


void RecycleBin::realign()
{
//    QSize size;
//    size.setHeight(40);
//    size.setWidth(40);
//    mWidget.button()->setFixedHeight(40);
//    mWidget.button()->setIconSize(size);
//    mWidget.button()->setFixedWidth(60);
//      mWidget.lineEdit()->setFixedHeight(80);

}

RecycleBinWidget::RecycleBinWidget(QWidget *parent):
    QFrame(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins (0, 0, 0, 0);
    layout->setSpacing (1);
    setLayout(layout);
    layout->addWidget(&mButton2);

    mButton2.setFixedSize(40,40);

    mCapturing = false;
    connect(&mButton2, SIGNAL(clicked()), this, SLOT(captureMouse()));

    mButton2.setStyleSheet(
                //正常状态样式
                "QToolButton{"
                /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
                "qproperty-icon:url(/usr/share/plugin-recyclebin/img/recyclebin.svg);"
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




RecycleBinWidget::~RecycleBinWidget()
{
}


void RecycleBinWidget::mouseReleaseEvent(QMouseEvent *event)
{
//    if (!mCapturing)
//        return;
//    WId id = QApplication::desktop()->winId();
//    qDebug()<<id<<endl;
}


void RecycleBinWidget::captureMouse()
{
    if(QFileInfo::exists(QString("/usr/bin/ukui-menu")))
    {
    QProcess *process =new QProcess(this);
    process->startDetached("/usr/bin/ukui-menu");
    }
    else{qDebug()<<"not find /usr/bin/ukui-start-menu"<<endl;}
}

void RecycleBinWidget::contextMenuEvent(QContextMenuEvent *event) {
  //创建一个菜单 添加事件
qDebug()<<"contextMenuEvent    right press event";
}
