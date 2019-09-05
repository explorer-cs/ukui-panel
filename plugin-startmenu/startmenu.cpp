#include "startmenu.h"
//#include "ui_startmenu.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

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
    //mWidget.button()->setFixedHeight(panel()->iconSize());
    //mWidget.button()->setFixedWidth(panel()->iconSize());
      //mWidget.lineEdit()->setFixedHeight(panel()->iconSize());
    //  qDebug()<<"colorpicke icon"<<endl;

}

StartMenuWidget::StartMenuWidget(QWidget *parent):
    QFrame(parent),
    mMainWindow(NULL)
{
    //QFontMetrics fm (mLineEdit.font());
    //mLineEdit.setFixedWidth ( 10*fm.width (QStringLiteral("a")) );


    //mMainWindow = new MainWindow;
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins (0, 0, 0, 0);
    layout->setSpacing (1);
    setLayout(layout);
    layout->addWidget (&mButton);

    //layout->addWidget (&mLineEdit);


    mButton.setAutoRaise(true);
    //mButton.setIcon(XdgIcon::fromTheme(QStringLiteral("color-picker"), QStringLiteral("kcolorchooser")));

    mCapturing = false;
    connect(&mButton, SIGNAL(clicked()), this, SLOT(captureMouse()));
    mButton.setObjectName("mButton");
    //gn-游戏娱乐-灰色.svg图标在 ukui-panel/plugin-startmenu/data/img/mainviewwidget 文件目录下，png格式等也可以加载
    mButton.setStyleSheet("#mButton{border-image:url(/usr/share/ukui-panel/plugin-startmenu/img/3.svg);}");
    qDebug()<<PACKAGE_DATA_DIR<<endl;


}



StartMenuWidget::~StartMenuWidget()
{
}


void StartMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!mCapturing)
        return;
    WId id = QApplication::desktop()->winId();
    //QPixmap pixmap = qApp->primaryScreen()->grabWindow(id, event->globalX(), event->globalY(), 1, 1);

    //QImage img = pixmap.toImage();
   // QColor col = QColor(img.pixel(0,0));

    //mLineEdit.setText (col.name());

    mCapturing = false;
    //releaseMouse();

}


void StartMenuWidget::captureMouse()
{
   //grabMouse(Qt::CrossCursor);
   mCapturing = true;
   mMainWindow = new MainWindow;
       if(mMainWindow != NULL)
       {
           mMainWindow->setGeometry(QRect(0,QApplication::desktop()->availableGeometry().height()-532,390,532));
           mMainWindow->show();
           mMainWindow->raise();
           mMainWindow->activateWindow();

       }

}



