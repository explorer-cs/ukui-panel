#include "segmentation.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

#define DESKTOP_HEIGHT  (12)
#define DESKTOP_WIDTH   (30)

Segmentation::Segmentation(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    IUKUIPanelPlugin(startupInfo)
{
//    mButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    mButton.setAutoRaise(true);
    realign();
    mCapturing = false;
    mButton.setFixedSize(DESKTOP_HEIGHT,DESKTOP_WIDTH);
    mButton.setStyleSheet(
                //正常状态样式
                "QToolButton{"
                /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
                "qproperty-icon:url(/usr/share/plugin-segmentation/img/segmentation.svg);"
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
                );


}


Segmentation::~Segmentation()
{
}


void Segmentation::realign()
{
//    if(panel()->isHorizontal())
//    {
//        mButton.setFixedSize(DESKTOP_HEIGHT,DESKTOP_WIDTH);
//        mButton.setStyleSheet(
//                    //正常状态样式
//                    "QToolButton{"
//                    /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
//                    "qproperty-icon:url(/usr/share/plugin-segmentation/img/segmentation.svg);"
//                    "qproperty-iconSize:40px 40px;"
//                    "border-style:outset;"                  //边框样式（inset/outset）
//                    "border-width:0px;"                     //边框宽度像素
//                    "border-radius:0px;"                   //边框圆角半径像素
//                    "border-color:rgba(255,255,255,30);"    //边框颜色
//                    "font:SimSun 14px;"                       //字体，字体大小
//                    "color:rgba(0,0,0,100);"                //字体颜色
//                    "padding:0px;"                          //填衬
//                    "border-bottom-style:solid"
//                    "}"
//                    );
//    }
//    else
//    {
//       mButton.setFixedSize(DESKTOP_WIDTH,DESKTOP_HEIGHT);
//       mButton.setStyleSheet(
//                   //正常状态样式
//                   "QToolButton{"
//                   /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
//                   "qproperty-icon:url(/usr/share/plugin-segmentation/img/segmentationh.svg);"
//                   "qproperty-iconSize:40px 40px;"
//                   "border-style:outset;"                  //边框样式（inset/outset）
//                   "border-width:0px;"                     //边框宽度像素
//                   "border-radius:0px;"                   //边框圆角半径像素
//                   "border-color:rgba(255,255,255,30);"    //边框颜色
//                   "font:SimSun 14px;"                       //字体，字体大小
//                   "color:rgba(0,0,0,100);"                //字体颜色
//                   "padding:0px;"                          //填衬
//                   "border-bottom-style:solid"
//                   "}"
//                   );
//    }
}
