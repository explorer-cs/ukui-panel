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
    //mWidget.button()->setFixedHeight(panel()->iconSize());
    //mWidget.button()->setFixedWidth(panel()->iconSize());
      //mWidget.lineEdit()->setFixedHeight(panel()->iconSize());
    //  qDebug()<<"colorpicke icon"<<endl;

}

StartMenuWidget::StartMenuWidget(QWidget *parent):
    QFrame(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins (0, 0, 0, 0);
    layout->setSpacing (1);
    setLayout(layout);
    layout->addWidget (&mButton);


    mButton.setAutoRaise(true);

    mCapturing = false;
    connect(&mButton, SIGNAL(clicked()), this, SLOT(captureMouse()));
    mButton.setObjectName("mButton");
    mButton.setStyleSheet("#mButton{border-image:url(/usr/share/plugin-startmenu/img/startmenu.svg);}");
    //mButton.setIcon(QIcon("/usr/share/ukui/img/startmenu.svg"));
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
    if(QFileInfo::exists(QString("/usr/bin/ukui-start-menu")))
    {
    QProcess *process =new QProcess(this);
    process->startDetached("/usr/bin/ukui-start-menu/ukui-start-menu");
    }
    else{qDebug()<<"not find /usr/bin/ukui-start-menu"<<endl;}
}

QDialog *StartMenu::configureDialog()
{
    qDebug()<<mShortcut<<endl;
    qDebug( )<<DEFAULT_SHORTCUT<<endl;
    return new LXQtMainMenuConfiguration(settings(), mShortcut, QStringLiteral(DEFAULT_SHORTCUT));
}


