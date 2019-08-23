#ifndef PLUGIN_H
#define PLUGIN_H
#include <LXQt/lxqtplugininfo.h>
#include <QFrame>
#include <LXQt/Settings>
#include <QPointer>
#include "ukuipanel.h"
#include "pluginsettings.h"
#include "ilxqtpanelplugin.h"
#include "lxqtpanelglobals.h"
#include "ilxqtpanel.h"

class QPluginLoader;
class QSettings;
class ILXQtPanelPlugin;
class ILXQtPanelPluginLibrary;
class UkuiPanel;
class QMenu;

class Plugin : public QFrame
{
    Q_OBJECT
public:
    enum Alignment {
        AlignLeft,
        AlignRight
    };
	Plugin(const LXQt::PluginInfo &desktopFile, LXQt::Settings *settings, const QString &settingsGroup, UkuiPanel *panel);

    QMenu* ukuiMenu() const;

    const LXQt::PluginInfo desktopFile() const { return mDesktopFile; }

    const ILXQtPanelPlugin * iPlugin() const { return mPlugin; }

    bool isLoaded() const { return mPlugin != 0; }
    Alignment alignment() const { return mAlignment; }

    void setAlignment(Alignment alignment);

    void saveSettings();

    bool isSeparate() const;
    bool isExpandable() const;

    /*define*/
    QString name() const { return mName; }

    // For QSS properties ..................
    static QColor moveMarkerColor() { return mMoveMarkerColor; }
    static void setMoveMarkerColor(QColor color) { mMoveMarkerColor = color; }



signals:
    void startMove();
    void remove();
    void dragLeft();
private:

    PluginSettings *mSettings;

	ILXQtPanelPluginLibrary const * findStaticPlugin(const QString &libraryName);

	bool loadLib(ILXQtPanelPluginLibrary const * pluginLib);

	const LXQt::PluginInfo mDesktopFile;

    bool loadModule(const QString &libraryName);

    void watchWidgets(QObject * const widget);

    void unwatchWidgets(QObject * const widget);

	ILXQtPanelPlugin *mPlugin;

	QWidget *mPluginWidget;

	UkuiPanel *mPanel;
    /*define a name for member*/
    QString mName;
    QPointer<QDialog> mConfigDialog; //!< plugin's config dialog (if any)
    QPluginLoader *mPluginLoader;
    Alignment mAlignment;
    static QColor mMoveMarkerColor;
public slots:
    void realign();
    void showConfigureDialog();
    void requestRemove();
    void settingsChanged();

};	
#endif // PLUGIN_H
