#include <QtDebug>
#include "panelpluginsmodel.h"
#include "ukuipanelapplication.h"
#include <QDir>
#include <LXQt/lxqtplugininfo.h>
#include<memory>
PanelPluginsModel::PanelPluginsModel(UkuiPanel * panel,
				     QString const & namesKey,
				     QStringList const & desktopDirs)
	:QAbstractListModel{},
	mPanel(panel)
{
	qDebug()<< "UkuiPanelApplication::UkuiPanelApplication";
	loadPlugins(desktopDirs);
}	
int PanelPluginsModel::rowCount(const QModelIndex & parent/* = QModelIndex()*/) const    //QAbstractListModel的纯虚函数
{
}
QVariant PanelPluginsModel::data(const QModelIndex & index, int role/* = Qt::DisplayRole*/) const  //QAbstractListModel的纯虚函数
{
}
void PanelPluginsModel::loadPlugins(QStringList const & desktopDirs)
{
//	QStringList plugin_names = mPanel->settings()->value(mNamesKey).toStringList();
//	QString name= "taskbar";
//	QString type="taskbar";
	QString name= "desktopswitch";
	QString type="desktopswitch";
	LXQt::PluginInfoList list;
	QSet<QString> processed;

    for (const QString &desktopFilesDir : desktopDirs)
    {
        //qk
        const QDir dir(desktopFilesDir);
        const QFileInfoList files = dir.entryInfoList(QStringList(QString("%1.desktop").arg(type)), QDir::Files | QDir::Readable);
        for (const QFileInfo &file : files)
        {
                if (processed.contains(file.fileName()))
                    continue;

                processed << file.fileName();

                LXQt::PluginInfo item;
                item.load(file.canonicalFilePath());

                if (item.isValid() && item.serviceType() == "LXQtPanel/Plugin")
                    list.append(item);
        }
    }
    if(!list.isEmpty())
        loadPlugin(list.first(), name);
}


void PanelPluginsModel::addPlugin(const LXQt::PluginInfo &desktopFile)
{
    if (dynamic_cast<UkuiPanelApplication const *>(qApp)->isPluginSingletonAndRunnig(desktopFile.id()))
        return;

    QString name = findNewPluginSettingsGroup(desktopFile.id());

    QPointer<Plugin> plugin = loadPlugin(desktopFile, name);
    if (plugin.isNull())
        return;

    beginInsertRows(QModelIndex(), mPlugins.size(), mPlugins.size());
    mPlugins.append({name, plugin});
    endInsertRows();
    mPanel->settings()->setValue(mNamesKey, pluginNames());
    emit pluginAdded(plugin.data());
}

Plugin const * PanelPluginsModel::pluginByID(QString id) const
{
    for (auto const & p : mPlugins)
    {
        Plugin *plugin = p.second.data();
        if (plugin && plugin->desktopFile().id() == id)
            return plugin;
    }
    return nullptr;
}

QString PanelPluginsModel::findNewPluginSettingsGroup(const QString &pluginType) const
{
    QStringList groups = mPanel->settings()->childGroups();
    groups.sort();

    // Generate new section name
    QString pluginName = QString("%1").arg(pluginType);

    if (!groups.contains(pluginName))
        return pluginName;
    else
    {
        for (int i = 2; true; ++i)
        {
            pluginName = QString("%1%2").arg(pluginType).arg(i);
            if (!groups.contains(pluginName))
                return pluginName;
        }
    }
}

QPointer<Plugin> PanelPluginsModel::loadPlugin(LXQt::PluginInfo const & desktopFile, QString const & settingsGroup)
{
    std::unique_ptr<Plugin> plugin(new Plugin(desktopFile, mPanel->settings(), settingsGroup, mPanel));
    if (plugin->isLoaded())
    {
        connect(mPanel, &UkuiPanel::realigned, plugin.get(), &Plugin::realign);
        connect(plugin.get(), &Plugin::remove,
                this, static_cast<void (PanelPluginsModel::*)()>(&PanelPluginsModel::removePlugin));
        return plugin.release();
    }

    return nullptr;
}

QStringList PanelPluginsModel::pluginNames() const
{
    QStringList names;
    for (auto const & p : mPlugins)
        names.append(p.first);
    return names;
}

void PanelPluginsModel::removePlugin(pluginslist_t::iterator plugin)
{
    if (mPlugins.end() != plugin)
    {
        mPanel->settings()->remove(plugin->first);
        Plugin * p = plugin->second.data();
        const int row = plugin - mPlugins.begin();
        beginRemoveRows(QModelIndex(), row, row);
        mPlugins.erase(plugin);
        endRemoveRows();
        emit pluginRemoved(p); // p can be nullptr
        mPanel->settings()->setValue(mNamesKey, pluginNames());
        if (nullptr != p)
            p->deleteLater();
    }
}

void PanelPluginsModel::removePlugin()
{
    Plugin * p = qobject_cast<Plugin*>(sender());
    auto plugin = std::find_if(mPlugins.begin(), mPlugins.end(),
                               [p] (pluginslist_t::const_reference obj) { return p == obj.second; });
    removePlugin(std::move(plugin));
}


