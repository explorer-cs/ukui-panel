#ifndef PLUGIN_H
#define PLUGIN_H
#include <LXQt/lxqtplugininfo.h>
#include <QFrame>
#include <LXQt/Settings>
#include "ukuipanel.h"
#include "pluginsettings.h"
#include "ilxqtpanelplugin.h"

class UkuiPanel;
class QMenu;
class Plugin : public QFrame
{
    Q_OBJECT
public:	
	Plugin(const LXQt::PluginInfo &desktopFile, LXQt::Settings *settings, const QString &settingsGroup, UkuiPanel *panel);

    QMenu* ukuiMenu() const;

    const LXQt::PluginInfo desktopFile() const { return mDesktopFile; }

    const ILXQtPanelPlugin * iPlugin() const { return mPlugin; }

    bool isLoaded() const { return mPlugin != 0; }

signals:
    void startMove();
    void remove();
private:
    /*define*/
    QString name() const { return mName; }
private:
    PluginSettings *mSettings;

	ILXQtPanelPluginLibrary const * findStaticPlugin(const QString &libraryName);

	bool loadLib(ILXQtPanelPluginLibrary const * pluginLib);

	const LXQt::PluginInfo mDesktopFile;

	ILXQtPanelPlugin *mPlugin;

	QWidget *mPluginWidget;

	UkuiPanel *mPanel;
    /*define a name for member*/
    QString mName;

public slots:
    void realign();
    void showConfigureDialog();
    void requestRemove();
};	
#endif // PLUGIN_H
