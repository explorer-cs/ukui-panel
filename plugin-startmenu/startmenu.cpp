#include "startmenu.h"
#include "lxqtmainmenuconfiguration.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

#include <lxqt-globalkeys.h>

StartMenu::StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    mShortcut(0),
    IUKUIPanelPlugin(startupInfo)
{
    realign();
    mShortcut = GlobalKeyShortcut::Client::instance()->addAction(QString{}, QStringLiteral("/panel/%1/show_hide").arg(settings()->group()), StartMenu::tr("Show/hide main menu"), this);
    if (mShortcut)
    {
        connect(mShortcut, &GlobalKeyShortcut::Action::registrationFinished, [this] {
            if (mShortcut->shortcut().isEmpty())
                mShortcut->changeShortcut(QStringLiteral(DEFAULT_SHORTCUT));
        });
        connect(mShortcut, &GlobalKeyShortcut::Action::activated, [this] {
            if (!mHideTimer.isActive())
                // Delay this a little -- if we don't do this, search field
                // won't be able to capture focus
                // See <https://github.com/lxqt/lxqt-panel/pull/131> and
                // <https://github.com/lxqt/lxqt-panel/pull/312>
                mDelayedPopup.start();
        });
    }

}


StartMenu::~StartMenu()
{
}


void StartMenu::realign()
{
    QSize size;
    size.setHeight(40);
    size.setWidth(40);
    m2Widget.button()->setFixedHeight(40);
    m2Widget.button()->setIconSize(size);
    m2Widget.button()->setFixedWidth(60);
      m2Widget.lineEdit()->setFixedHeight(80);
      qDebug()<<"startmenu icon"<<m2Widget.button()->iconSize()<<endl;

}

StartMenuWidget::StartMenuWidget(QWidget *parent):
    QFrame(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins (0, 0, 0, 0);
    layout->setSpacing (1);
    setLayout(layout);
    layout->addWidget (&mButton);


    //mButton.setAutoRaise(true);
    mButton.setFixedSize(600,40);



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
                "font:bold 14px;"                       //字体，字体大小
                "color:rgba(0,0,0,100);"                //字体颜色
                "padding:0px;"                          //填衬
                "}"
                //鼠标按下样式
                "QToolButton:pressed{"
                "background-color:rgba(190,216,239,12%);"
                "}"
                //鼠标悬停样式
                "QToolButton:hover{"
                "background-color:rgba(190,216,239,20%);"
                "}");
}



StartMenuWidget::~StartMenuWidget()
{
}


void StartMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!mCapturing)
        return;
    WId id = QApplication::desktop()->winId();
    qDebug()<<id<<endl;
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

QDialog *StartMenu::configureDialog()
{
    qDebug()<<mShortcut<<endl;
    qDebug( )<<DEFAULT_SHORTCUT<<endl;
    return new LXQtMainMenuConfiguration(settings(), mShortcut, QStringLiteral(DEFAULT_SHORTCUT));
}


