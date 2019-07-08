#ifndef PLUGIN_H
#define PLUGIN_H
#include <LXQt/lxqtplugininfo.h>
#include <QFrame>
#include <LXQt/Settings>
#include "ukuipanel.h"
#include "pluginsettings.h"
#include "ilxqtpanelplugin.h"

class UkuiPanel;
class Plugin : public QFrame
{
public:	
	Plugin(const LXQt::PluginInfo &desktopFile, LXQt::Settings *settings, const QString &settingsGroup, UkuiPanel *panel);
private:
	PluginSettings *mSettings;	
	ILXQtPanelPluginLibrary const * findStaticPlugin(const QString &libraryName);
	bool loadLib(ILXQtPanelPluginLibrary const * pluginLib);
	const LXQt::PluginInfo mDesktopFile;
	ILXQtPanelPlugin *mPlugin;
	QWidget *mPluginWidget;
	UkuiPanel *mPanel;
};	
#endif // PLUGIN_H
