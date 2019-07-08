#include "ukuipanel.h"
#include <KWindowSystem/KWindowSystem>
#include <QDropEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <XdgDirs>
#include <LXQt/Settings>

UkuiPanel::UkuiPanel(const QString &configGroup,LXQt::Settings *settings) : 
	QFrame(),
	mSettings(settings),
	mConfigGroup(configGroup)
{
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
/*
void UkuiPanel::show()
{
	qDebug()<<  "kuiPanel::show";
//	QWidget::show();
}
*/
bool UkuiPanel::event(QEvent *event)
{
    qDebug() <<  "UkuiPanel::event";
    switch (event->type())
    {
    case QEvent::ContextMenu:
	//面板右击菜单项
//        showPopupMenu();
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
}
