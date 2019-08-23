#include "ukuipanel.h"
#include <KWindowSystem/KWindowSystem>
#include <LXQt/Settings>

#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QX11Info>
#include <QDebug>
#include <QString>
#include <QDesktopWidget>
#include <QMenu>
#include <QPushButton>
#include <QMessageBox>
#include <QDropEvent>
#include <XdgIcon>
#include <XdgDirs>

#include "windownotifier.h"
#include "ukuipanelapplication.h"
#include"ukuimenu.h"
#include "config/configpaneldialog.h"


// Config keys and groups
#define CFG_KEY_SCREENNUM          "desktop"
#define CFG_KEY_POSITION           "position"
#define CFG_KEY_PANELSIZE          "panelSize"
#define CFG_KEY_ICONSIZE           "iconSize"
#define CFG_KEY_LINECNT            "lineCount"
#define CFG_KEY_LENGTH             "width"
#define CFG_KEY_PERCENT            "width-percent"
#define CFG_KEY_ALIGNMENT          "alignment"
#define CFG_KEY_FONTCOLOR          "font-color"
#define CFG_KEY_BACKGROUNDCOLOR    "background-color"
#define CFG_KEY_BACKGROUNDIMAGE    "background-image"
#define CFG_KEY_OPACITY            "opacity"
#define CFG_KEY_RESERVESPACE       "reserve-space"
#define CFG_KEY_PLUGINS            "plugins"
#define CFG_KEY_HIDABLE            "hidable"
#define CFG_KEY_VISIBLE_MARGIN     "visible-margin"
#define CFG_KEY_ANIMATION          "animation-duration"
#define CFG_KEY_SHOW_DELAY         "show-delay"
#define CFG_KEY_LOCKPANEL          "lockPanel"




UkuiPanel::UkuiPanel(const QString &configGroup,LXQt::Settings *settings) : 
	QFrame(),
    mSettings(settings),
    mConfigGroup(configGroup),
    mPanelSize(0),
    mIconSize(0),
    mLineCount(0),
    mLength(0),
    mAlignment(AlignmentLeft),
    mPosition(ILXQtPanel::PositionBottom),
    mScreenNum(0), //whatever (avoid conditional on uninitialized value)
    mActualScreenNum(0),
    mHidable(false),
    mVisibleMargin(true),
    mHidden(false),
    mAnimationTime(0),
    mReserveSpace(true),
    mAnimation(nullptr),
    mLockPanel(false)
{

    //LXQtPanel (inherits QFrame) -> lav (QGridLayout) -> LXQtPanelWidget (QFrame) -> LXQtPanelLayout
    mUkuiPanelWidget = new QFrame(this);
    mUkuiPanelWidget->setObjectName("BackgroundWidget");
    QGridLayout* lav = new QGridLayout();
    lav->setContentsMargins(0, 0, 0, 0);
    setLayout(lav);
    this->layout()->addWidget(mUkuiPanelWidget);
    QPushButton *button =new QPushButton("kkkkkkkkkkkkkkkkk");
//    this->layout()->addWidget(button);


    mLayout = new UkuiPanelLayout(mUkuiPanelWidget);
    connect(mLayout, &UkuiPanelLayout::pluginMoved, this, &UkuiPanel::pluginMoved);
    
    if(mLayout == NULL){
	printf("button NULL-------------\n");
    } else{
	printf("button not NULL-------------\n");
    }
/*
   int left, top, right, bottom;
mLayout->getContentsMargins(&left,&top,&right,&bottom);
printf("left=%d\n",left);
printf("right=%d\n",right);
printf("top=%d\n",top);
printf("bottom=%d\n",bottom);

mLayout->setContentsMargins(0,0,400,40);
mLayout->getContentsMargins(&left,&top,&right,&bottom);
printf("left=%d\n",left);
printf("right=%d\n",right);
printf("top=%d\n",top);
printf("bottom=%d\n",bottom);
*/

//    mUkuiPanelWidget->setLayout(mLayout);
//
//QHBoxLayout *topLayout = new QHBoxLayout;
QHBoxLayout *topLayout = new QHBoxLayout;  

topLayout->setContentsMargins(0,890,100,900);

    topLayout->addWidget(button);
    mUkuiPanelWidget->resize(40,40);
    mUkuiPanelWidget->setLayout(topLayout);

//    this->setLayout(topLayout);
//    
    /*
    QVBoxLayout Q_V_L=new QVBoxLayout();
    Q_V_L->addLayout(topLayout);
    Q_V_L->setContentsMargins(0,0,0,0);
    mUkuiPanelWidget->setLayout(Q_V_L);
    this->setLayout(Q_V_L);
    */
//    mUkuiPanelWidget->layout()->addWidget(button);



    mLayout->setLineCount(mLineCount);
    qDebug()<< "UkuiPanel::UkuiPanel";
	Qt::WindowFlags flags = Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
	flags |= Qt::WindowDoesNotAcceptFocus;
	setWindowFlags(flags);
	setAttribute(Qt::WA_X11NetWmWindowTypeDock);
	setAttribute(Qt::WA_AlwaysShowToolTips);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_AcceptDrops);
	setWindowTitle("Ukui Panel");

	//添加插件
	loadPlugins();
	show();
}
UkuiPanel::~UkuiPanel()
{
}
void UkuiPanel::show()
{
    QWidget::show();
    KWindowSystem::setOnDesktop(effectiveWinId(), NET::OnAllDesktops);
}

bool UkuiPanel::event(QEvent *event)
{
    qDebug() <<  "UkuiPanel::event";
    switch (event->type())
    {
    case QEvent::ContextMenu:
	//面板右击菜单项
       showUkuiMenu();
        break;

    case QEvent::LayoutRequest:
        qDebug() << "realign-7";
//        emit realigned();
        break;

    case QEvent::WinIdChange:
    {
        // qDebug() << "WinIdChange" << hex << effectiveWinId();
        if(effectiveWinId() == 0)
            break;


        KWindowSystem::setType(effectiveWinId(), NET::Dock);

        break;
    }
    case QEvent::DragEnter:
        dynamic_cast<QDropEvent *>(event)->setDropAction(Qt::IgnoreAction);
        event->accept();
    case QEvent::Enter:
        break;
    case QEvent::Leave:
    case QEvent::DragLeave:
//        hidePanel();
        break;

    default:
        break;
    }

    return QFrame::event(event);

}
void UkuiPanel::showEvent(QShowEvent *event)
{
	qDebug() << "UkuiPanel::showEvent";
	setPanelGeometry();
	updateWmStrut();
}
void UkuiPanel::setPanelGeometry()
{
	qDebug() << "UkuiPanel::setPanelGeometry";
	const QRect currentScreen = QApplication::desktop()->screenGeometry();
    	QRect rect;

        rect.setHeight(40);
        rect.setWidth(currentScreen.width());

	//任务栏位置设置
	rect.moveBottom(currentScreen.bottom());
//	rect.moveTop(currentScreen.top());	
        this->setGeometry(rect);

}
void UkuiPanel::updateWmStrut()
{
	WId wid = effectiveWinId();
	const QRect wholeScreen = QApplication::desktop()->geometry();
	const QRect rect = geometry();

	if(wid == 0 || !isVisible())
		return;

	//任务栏位置设置
	/*
	KWindowSystem::setExtendedStrut(wid,
                                        0, 0, 0,			//Left
                                        0, 0, 0,			//Right
                                        40, rect.left(), rect.right(),	//Top
                                        0, 0, 0				//Bottom
                                        );
	*/

    KWindowSystem::setExtendedStrut(wid,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    40, rect.left(), rect.right()
                                    );
	
}
QStringList UkuiPanel::pluginDesktopDirs()
{
    qDebug() << "UkuiPanel::pluginDesktopDirs";
    QStringList dirs;
    dirs << QString(getenv("LXQT_PANEL_PLUGINS_DIR")).split(':', QString::SkipEmptyParts);
    dirs << QString("%1/%2").arg(XdgDirs::dataHome(), "/lxqt/lxqt-panel");
    dirs << PLUGIN_DESKTOPS_DIR;
    qDebug() << dirs;
    return dirs;
}
void UkuiPanel::loadPlugins()
{
    	qDebug() << "UkuiPanel::loadPlugins";
	QString names_key(mConfigGroup);
	names_key += '/';
	names_key += QLatin1String(CFG_KEY_PLUGINS);	
	mPlugins.reset(new PanelPluginsModel(this, names_key, pluginDesktopDirs()));
    connect(mPlugins.data(), &PanelPluginsModel::pluginAdded, mLayout, &UkuiPanelLayout::addPlugin);
    connect(mPlugins.data(), &PanelPluginsModel::pluginMovedUp, mLayout, &UkuiPanelLayout::moveUpPlugin);
    //reemit signals
    connect(mPlugins.data(), &PanelPluginsModel::pluginAdded, this, &UkuiPanel::pluginAdded);
    connect(mPlugins.data(), &PanelPluginsModel::pluginRemoved, this, &UkuiPanel::pluginRemoved);

    const auto plugins = mPlugins->plugins();
    for (auto const & plugin : plugins)
    {
	    printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
        mLayout->addPlugin(plugin);
	this->layout()->addWidget(plugin);
        connect(plugin, &Plugin::dragLeft, [this] { mShowDelayTimer.stop(); hidePanel(); });
    }
}

void UkuiPanel::showUkuiMenu(Plugin *plugin)
{
    Ukuimenu * menu = new Ukuimenu(tr("Panel"), this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    menu->setIcon(XdgIcon::fromTheme("configure-toolbars"));


    if (plugin)
    {
        QMenu *m = plugin->ukuiMenu();

        if (m)
        {
            menu->addTitle(plugin->windowTitle());
            const auto actions = m->actions();
            for (auto const & action : actions)
            {
                action->setParent(menu);
                action->setDisabled(false);
                menu->addAction(action);
            }
            delete m;
        }
    }
    /*add menu*/
    menu->addTitle(QIcon(), tr("Panel"));
    menu->addAction(XdgIcon::fromTheme(QLatin1String("configure")),
                   tr("Configure Panel"),
                   this, SLOT(showConfigDialog())
                  )->setDisabled(false);

    menu->addAction(XdgIcon::fromTheme("preferences-plugin"),
                   tr("Manage Widgets"),
                   this, SLOT(showAddPluginDialog())
                  )->setDisabled(false);

    UkuiPanelApplication *app= reinterpret_cast<UkuiPanelApplication*>(qApp);
    menu->addAction(XdgIcon::fromTheme(QLatin1String("list-add")),
                   tr("Add New Panel"),
                   app, SLOT(addNewPanel())
                  );
    if (app->count() > 1)/*more than one panels,can remove panels*/
    {
        menu->addAction(XdgIcon::fromTheme(QLatin1String("list-remove")),
                       tr("Remove Panel", "Menu Item"),
                       this, SLOT(userRequestForDeletion())
                      )->setDisabled(false);
    }

    QAction * act_lock = menu->addAction(tr("Lock This Panel"));
    act_lock->setCheckable(true);
    act_lock->setChecked(false);
    connect(act_lock, &QAction::triggered, [this] { mLockPanel = !mLockPanel; saveSettings(false); });


    menu->setGeometry(calculatePopupWindowPos(QCursor::pos(), menu->sizeHint()));
    willShowWindow(menu);
    menu->show();
}

void UkuiPanel::willShowWindow(QWidget * w)
{
    mStandaloneWindows->observeWindow(w);
}


QRect UkuiPanel::calculatePopupWindowPos(QPoint const & absolutePos, QSize const & windowSize) const
{
    int x = absolutePos.x(), y = absolutePos.y();

    switch (position())
    {
    case ILXQtPanel::PositionTop:
        y = globalGometry().bottom();
        break;

    case ILXQtPanel::PositionBottom:
        y = globalGometry().top() - windowSize.height();
        break;

    case ILXQtPanel::PositionLeft:
        x = globalGometry().right();
        break;

    case ILXQtPanel::PositionRight:
        x = globalGometry().left() - windowSize.width();
        break;
    }
    QRect res(QPoint(x, y), windowSize);

    QRect screen = QApplication::desktop()->screenGeometry(this);
    // NOTE: We cannot use AvailableGeometry() which returns the work area here because when in a
    // multihead setup with different resolutions. In this case, the size of the work area is limited
    // by the smallest monitor and may be much smaller than the current screen and we will place the
    // menu at the wrong place. This is very bad for UX. So let's use the full size of the screen.
    if (res.right() > screen.right())
        res.moveRight(screen.right());

    if (res.bottom() > screen.bottom())
        res.moveBottom(screen.bottom());

    if (res.left() < screen.left())
        res.moveLeft(screen.left());

    if (res.top() < screen.top())
        res.moveTop(screen.top());

    return res;
}

QRect UkuiPanel::calculatePopupWindowPos(const ILXQtPanelPlugin *plugin, const QSize &windowSize) const
{
    return geometry();
}

void UkuiPanel::saveSettings(bool _bVar)
{
    mDelaySave.stop();
    if (_bVar)
    {
        mDelaySave.start();
        return;
    }

    mSettings->beginGroup(mConfigGroup);

    //Note: save/load of plugin names is completely handled by mPlugins object
    //mSettings->setValue(CFG_KEY_PLUGINS, mPlugins->pluginNames());

    mSettings->setValue(CFG_KEY_PANELSIZE, mPanelSize);
    mSettings->setValue(CFG_KEY_ICONSIZE, mIconSize);
    mSettings->setValue(CFG_KEY_LINECNT, mLineCount);

    mSettings->setValue(CFG_KEY_LENGTH, mLength);
    mSettings->setValue(CFG_KEY_PERCENT, mLengthInPercents);

    mSettings->setValue(CFG_KEY_SCREENNUM, mScreenNum);
    //mSettings->setValue(CFG_KEY_POSITION, positionToStr(mPosition));

    mSettings->setValue(CFG_KEY_ALIGNMENT, mAlignment);

    mSettings->setValue(CFG_KEY_FONTCOLOR, mFontColor.isValid() ? mFontColor : QColor());
    mSettings->setValue(CFG_KEY_BACKGROUNDCOLOR, mBackgroundColor.isValid() ? mBackgroundColor : QColor());
    mSettings->setValue(CFG_KEY_BACKGROUNDIMAGE, QFileInfo(mBackgroundImage).exists() ? mBackgroundImage : QString());
    mSettings->setValue(CFG_KEY_OPACITY, mOpacity);
    mSettings->setValue(CFG_KEY_RESERVESPACE, mReserveSpace);

    mSettings->setValue(CFG_KEY_HIDABLE, mHidable);
    mSettings->setValue(CFG_KEY_VISIBLE_MARGIN, mVisibleMargin);
    mSettings->setValue(CFG_KEY_ANIMATION, mAnimationTime);
    mSettings->setValue(CFG_KEY_SHOW_DELAY, mShowDelayTimer.interval());

    mSettings->setValue(CFG_KEY_LOCKPANEL, mLockPanel);

    mSettings->endGroup();
}

void UkuiPanel::showConfigDialog()
{
    if (mConfigDialog.isNull())
        mConfigDialog = new ConfigPanelDialog(this, nullptr /*make it top level window*/);

    mConfigDialog->showConfigPanelPage();
    mStandaloneWindows->observeWindow(mConfigDialog.data());
    mConfigDialog->show();
    mConfigDialog->raise();
    mConfigDialog->activateWindow();
    WId wid = mConfigDialog->windowHandle()->winId();

    KWindowSystem::activateWindow(wid);
    KWindowSystem::setOnDesktop(wid, KWindowSystem::currentDesktop());
}

void UkuiPanel::showAddPluginDialog()
{
    if (mConfigDialog.isNull())
        mConfigDialog = new ConfigPanelDialog(this, nullptr /*make it top level window*/);

    mConfigDialog->showConfigPluginsPage();
    mStandaloneWindows->observeWindow(mConfigDialog.data());
    mConfigDialog->show();
    mConfigDialog->raise();
    mConfigDialog->activateWindow();
    WId wid = mConfigDialog->windowHandle()->winId();

    KWindowSystem::activateWindow(wid);
    KWindowSystem::setOnDesktop(wid, KWindowSystem::currentDesktop());
}

void UkuiPanel::setReserveSpace(bool reserveSpace, bool save)
{
    if (mReserveSpace == reserveSpace)
        return;

    mReserveSpace = reserveSpace;

    if (save)
        saveSettings(true);

    updateWmStrut();
}


bool UkuiPanel::isPluginSingletonAndRunnig(QString const & pluginId) const
{
    Plugin const * plugin = mPlugins->pluginByID(pluginId);
    if (nullptr == plugin)
        return false;
    else
        return plugin->iPlugin()->flags().testFlag(ILXQtPanelPlugin::SingleInstance);
}

 QRect UkuiPanel::globalGometry() const
 {
     return geometry();
 }

 void UkuiPanel::pluginFlagsChanged(const ILXQtPanelPlugin * plugin)
 {

 }

 void UkuiPanel::hidePanel()
 {
     if (mHidable && !mHidden
             && !mStandaloneWindows->isAnyWindowShown()
        )
         mHideTimer.start();
 }

 void UkuiPanel::pluginMoved(Plugin * plug)
 {
     //get new position of the moved plugin
     bool found{false};
     QString plug_is_before;
    /* for (int i=0; i<mLayout->count(); ++i)
     {
         Plugin *plugin = qobject_cast<Plugin*>(mLayout->itemAt(i)->widget());
         if (plugin)
         {
             if (found)
             {
                 //we found our plugin in previous cycle -> is before this (or empty as last)
                 plug_is_before = plugin->settingsGroup();
                 break;
             } else
                 found = (plug == plugin);
         }
     }
     mPlugins->movePlugin(plug, plug_is_before);
     */
 }



