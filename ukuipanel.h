#ifndef UKUIPANEL_H
#define UKUIPANEL_H
#include <QFrame>
#include <QtDebug>
#include "panelpluginsmodel.h"
#include <LXQt/Settings>
#include "ilxqtpanel.h"

#define CFG_KEY_PLUGINS            	"plugins"
#define PLUGIN_DESKTOPS_DIR		"/usr/share/lxqt/lxqt-panel/"   //临时位置，后面要获取安装目录 set(PLUGIN_DESKTOPS_DIR \"${CMAKE_INSTALL_FULL_DATAROOTDIR}/lxqt/${PROJECT}\")

class PanelPluginsModel;
class UkuiPanel : public QFrame 
{
	friend class PanelPluginsModel;
public:
        UkuiPanel(const QString &configGroup,LXQt::Settings *settings);
        ~UkuiPanel();
protected:
	bool event(QEvent *event);
	void showEvent(QShowEvent *event) ;
private :
	QString mConfigGroup;
	void loadPlugins();
	QScopedPointer<PanelPluginsModel> mPlugins;
	QStringList pluginDesktopDirs();
	LXQt::Settings *mSettings;
	LXQt::Settings *settings() const { return mSettings; }
public slots:
//	void show();
private slots:
	void setPanelGeometry();
	void updateWmStrut();
};
#endif // UKUIPANEL_H
