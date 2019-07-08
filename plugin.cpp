#include "plugin.h"
#include "ukuipanel.h"
#include "ilxqtpanelplugin.h"
#include "plugin-desktopswitch/desktopswitch.h"
#include <memory>
extern void * loadPluginTranslation_desktopswitch_helper;
Plugin::Plugin(const LXQt::PluginInfo &desktopFile, LXQt::Settings *settings, const QString &settingsGroup, UkuiPanel *panel):
	QFrame(panel)
{
	mSettings = PluginSettingsFactory::create(settings, settingsGroup);
	if(ILXQtPanelPluginLibrary const * pluginLib = findStaticPlugin(desktopFile.id()))
	{
		loadLib(pluginLib);
	}
}
namespace
{
    typedef std::unique_ptr<ILXQtPanelPluginLibrary> plugin_ptr_t;
    typedef std::tuple<QString, plugin_ptr_t, void *> plugin_tuple_t;

    static plugin_tuple_t const static_plugins[] = {
#if defined(WITH_DESKTOPSWITCH_PLUGIN)
        std::make_tuple(QLatin1String("desktopswitch"), plugin_ptr_t{new DesktopSwitchPluginLibrary}, loadPluginTranslation_desktopswitch_helper),// desktopswitch
#endif
    };
    static constexpr plugin_tuple_t const * const plugins_begin = static_plugins;
    static constexpr plugin_tuple_t const * const plugins_end = static_plugins + sizeof (static_plugins) / sizeof (static_plugins[0]);

    struct assert_helper
    {
        assert_helper()
        {
//            Q_ASSERT(std::is_sorted(plugins_begin, plugins_end
//                        , [] (plugin_tuple_t const & p1, plugin_tuple_t const & p2) -> bool { return std::get<0>(p1) < std::get<0>(p2); }));
        }
    };
    static assert_helper h;
}

ILXQtPanelPluginLibrary const * Plugin::findStaticPlugin(const QString &libraryName)
{
    qDebug() << "libraryName="   << libraryName;
    // find a static plugin library by name -> binary search
    plugin_tuple_t const * plugin = std::lower_bound(plugins_begin, plugins_end, libraryName
            , [] (plugin_tuple_t const & plugin, QString const & name) -> bool { return std::get<0>(plugin) < name; });
    if (plugins_end != plugin && libraryName == std::get<0>(*plugin))
        return std::get<1>(*plugin).get();
    return nullptr;
}
bool Plugin::loadLib(ILXQtPanelPluginLibrary const * pluginLib)
{
    ILXQtPanelPluginStartupInfo startupInfo;
    startupInfo.settings = mSettings;
    startupInfo.desktopFile = &mDesktopFile;
//    startupInfo.lxqtPanel = mPanel;  //需要去掉注释，会报错，接下来研究

    mPlugin = pluginLib->instance(startupInfo);

    mPluginWidget = mPlugin->widget();
    return true;
}

