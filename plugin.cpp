#include "plugin.h"
#include "ukuipanel.h"
#include "ilxqtpanelplugin.h"
#include "plugin-desktopswitch/desktopswitch.h"
#include <memory>
#include <XdgIcon>
#include <QDebug>
#include <QProcessEnvironment>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QPluginLoader>
#include <QGridLayout>
#include <QDialog>
#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>
#include <memory>
#include <kwindowsystem.h>

#include <LXQt/Settings>
#include <LXQt/Translator>
#include <XdgIcon>

// statically linked built-in plugins
#include "plugin-desktopswitch/desktopswitch.h" // desktopswitch
extern void * loadPluginTranslation_desktopswitch_helper;


QColor Plugin::mMoveMarkerColor= QColor(255, 0, 0, 255);


Plugin::Plugin(const LXQt::PluginInfo &desktopFile, LXQt::Settings *settings, const QString &settingsGroup, UkuiPanel *panel):
    QFrame(panel),
    mDesktopFile(desktopFile),
    mPluginLoader(0),
    mPlugin(0),
    mPluginWidget(0),
    mAlignment(AlignLeft),
    mPanel(panel)
{

    setWindowTitle(desktopFile.name());
    mName = desktopFile.name();

    bool found = false;
	mSettings = PluginSettingsFactory::create(settings, settingsGroup);
	if(ILXQtPanelPluginLibrary const * pluginLib = findStaticPlugin(desktopFile.id()))
	{
        found = true;
        loadLib(pluginLib);
	}
    if (!isLoaded())
    {
        if (!found)
            qDebug() << QString("Plugin %1 not found in the").arg(desktopFile.id());

        return;
    }

    if (mPluginWidget)
    {
	    printf("mPluginWidget  === true\n");
        QGridLayout* layout = new QGridLayout(this);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        setLayout(layout);
        layout->addWidget(mPluginWidget, 0, 0);
    }

    saveSettings();

    // delay the connection to settingsChanged to avoid conflicts
    // while the plugin is still being initialized
   //connect(mSettings, &PluginSettings::settingsChanged,
            //this, &Plugin::settingsChanged);

}
namespace
{
    typedef std::unique_ptr<ILXQtPanelPluginLibrary> plugin_ptr_t;
    typedef std::tuple<QString, plugin_ptr_t, void *> plugin_tuple_t;

    static plugin_tuple_t const static_plugins[] = {
//#if defined(WITH_DESKTOPSWITCH_PLUGIN)
    std::make_tuple(QLatin1String("desktopswitch"), plugin_ptr_t{new DesktopSwitchPluginLibrary}, nullptr),// desktopswitch
//#endif
    };
    static constexpr plugin_tuple_t const * const plugins_begin = static_plugins;
    static constexpr plugin_tuple_t const * const plugins_end = static_plugins + sizeof (static_plugins) / sizeof (static_plugins[0]);

    struct assert_helper
    {
        assert_helper()
        {
           Q_ASSERT(std::is_sorted(plugins_begin, plugins_end
                       , [] (plugin_tuple_t const & p1, plugin_tuple_t const & p2) -> bool { return std::get<0>(p1) < std::get<0>(p2); }));
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
    startupInfo.lxqtPanel = mPanel;  //需要去掉注释，会报错，接下来研究

    mPlugin = pluginLib->instance(startupInfo);

    mPluginWidget = mPlugin->widget();
    if (mPluginWidget)
    {
        mPluginWidget->setObjectName(mPlugin->themeId());
        watchWidgets(mPluginWidget);
    }
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return true;
}

QMenu *Plugin::ukuiMenu() const
{
    QString name = this->name().replace("&", "&&");
    QMenu* menu = new QMenu(windowTitle());

    if (mPlugin->flags().testFlag(ILXQtPanelPlugin::HaveConfigDialog))
    {
        QAction* configAction = new QAction(
            XdgIcon::fromTheme(QLatin1String("preferences-other")),
            tr("Configure \"%1\"").arg(name), menu);
        menu->addAction(configAction);
        connect(configAction, SIGNAL(triggered()), this, SLOT(showConfigureDialog()));
    }

    QAction* moveAction = new QAction(XdgIcon::fromTheme("transform-move"), tr("Move \"%1\"").arg(name), menu);
    menu->addAction(moveAction);
    connect(moveAction, SIGNAL(triggered()), this, SIGNAL(startMove()));

    menu->addSeparator();

    QAction* removeAction = new QAction(
        XdgIcon::fromTheme(QLatin1String("list-remove")),
        tr("Remove \"%1\"").arg(name), menu);
    menu->addAction(removeAction);
    connect(removeAction, SIGNAL(triggered()), this, SLOT(requestRemove()));

    return menu;
}

void Plugin::realign()
{
    if (mPlugin)
        mPlugin->realign();
}

void Plugin::showConfigureDialog()
{
    if (!mConfigDialog)
        mConfigDialog = mPlugin->configureDialog();

    if (!mConfigDialog)
        return;

    connect(this, &Plugin::destroyed, mConfigDialog.data(), &QWidget::close);
    mPanel->willShowWindow(mConfigDialog);
    mConfigDialog->show();
    mConfigDialog->raise();
    mConfigDialog->activateWindow();

    WId wid = mConfigDialog->windowHandle()->winId();
    KWindowSystem::activateWindow(wid);
    KWindowSystem::setOnDesktop(wid, KWindowSystem::currentDesktop());
}

void Plugin::requestRemove()
{
    emit remove();
    deleteLater();
}


// load dynamic plugin from a *.so module
bool Plugin::loadModule(const QString &libraryName)
{
    mPluginLoader = new QPluginLoader(libraryName);

    if (!mPluginLoader->load())
    {
        qWarning() << mPluginLoader->errorString();
        return false;
    }

    QObject *obj = mPluginLoader->instance();
    if (!obj)
    {
        qWarning() << mPluginLoader->errorString();
        return false;
    }

    ILXQtPanelPluginLibrary* pluginLib= qobject_cast<ILXQtPanelPluginLibrary*>(obj);
    if (!pluginLib)
    {
        qWarning() << QString("Can't load plugin \"%1\". Plugin is not a ILXQtPanelPluginLibrary.").arg(mPluginLoader->fileName());
        delete obj;
        return false;
    }
    return loadLib(pluginLib);
}

void Plugin::watchWidgets(QObject * const widget)
{
    // the QWidget might not be fully constructed yet, but we can rely on the isWidgetType()
    if (!widget->isWidgetType())
        return;
    widget->installEventFilter(this);
    // watch also children (recursive)
    for (auto const & child : widget->children())
    {
        watchWidgets(child);
    }
}

void Plugin::unwatchWidgets(QObject * const widget)
{
    widget->removeEventFilter(this);
    // unwatch also children (recursive)
    for (auto const & child : widget->children())
    {
        unwatchWidgets(child);
    }
}


void Plugin::saveSettings()
{
    /*
    mSettings->setValue("alignment", (mAlignment == AlignLeft) ? "Left" : "Right");
    mSettings->setValue("type", mDesktopFile.id());
    mSettings->sync();*/

}

void Plugin::setAlignment(Plugin::Alignment alignment)
{
    mAlignment = alignment;
    saveSettings();
}


void Plugin::settingsChanged()
{
    mPlugin->settingsChanged();
}

bool Plugin::isSeparate() const
{
   return mPlugin->isSeparate();
}


/************************************************

 ************************************************/
bool Plugin::isExpandable() const
{
    return mPlugin->isExpandable();
}



