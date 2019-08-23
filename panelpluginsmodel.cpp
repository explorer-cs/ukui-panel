#include <QtDebug>
#include "panelpluginsmodel.h"
#include "ukuipanelapplication.h"
#include <QDir>
#include <LXQt/lxqtplugininfo.h>
#include <memory>
#include <QPointer>
#include <XdgIcon>

PanelPluginsModel::PanelPluginsModel(UkuiPanel * panel,
				     QString const & namesKey,
				     QStringList const & desktopDirs)
	:QAbstractListModel{},
    mPanel(panel),
    mNamesKey(namesKey)
{
	qDebug()<< "UkuiPanelApplication::UkuiPanelApplication";
	loadPlugins(desktopDirs);
}	
int PanelPluginsModel::rowCount(const QModelIndex & parent/* = QModelIndex()*/) const    //QAbstractListModel的纯虚函数
{
    return QModelIndex() == parent ? mPlugins.size() : 0;
}
QVariant PanelPluginsModel::data(const QModelIndex & index, int role/* = Qt::DisplayRole*/) const  //QAbstractListModel的纯虚函数
{
    Q_ASSERT(QModelIndex() == index.parent()&& 0 == index.column() && mPlugins.size() > index.row());

    pluginslist_t::const_reference plugin = mPlugins[index.row()];
    QVariant ret;
    switch (role)
    {
        case Qt::DisplayRole:
            if (plugin.second.isNull())
                ret = QString("<b>Unknown</b> (%1)").arg(plugin.first);
            else
                ret = QString("<b>%1</b> (%2)").arg(plugin.second->name(), plugin.first);
            break;
        case Qt::DecorationRole:
            if (plugin.second.isNull())
                ret = XdgIcon::fromTheme("preferences-plugin");
            else
                ret = plugin.second->desktopFile().icon(XdgIcon::fromTheme("preferences-plugin"));
            break;
        case Qt::UserRole:
                ret = QVariant::fromValue(const_cast<Plugin const *>(plugin.second.data()));
            break;
    }
    return ret;
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
    qDebug()<<QModelIndex()<<"para is:"<<mPlugins.size();
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
        qDebug()<<"QPointer<Plugin> PanelPluginsModel::loadPlugin---\n";
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

void PanelPluginsModel::onMovePluginUp(QModelIndex const & index)
{
    if (!isIndexValid(index))
        return;

    const int row = index.row();
    if (0 >= row)
        return; //can't move up

    beginMoveRows(QModelIndex(), row, row, QModelIndex(), row - 1);
    mPlugins.swap(row - 1, row);
    endMoveRows();
    pluginslist_t::const_reference moved_plugin = mPlugins[row - 1];
    pluginslist_t::const_reference prev_plugin = mPlugins[row];

    emit pluginMoved(moved_plugin.second.data());
    //emit signal for layout only in case both plugins are loaded/displayed
    if (!moved_plugin.second.isNull() && !prev_plugin.second.isNull())
        emit pluginMovedUp(moved_plugin.second.data());

    mPanel->settings()->setValue(mNamesKey, pluginNames());
}

bool PanelPluginsModel::isIndexValid(QModelIndex const & index) const
{
    return index.isValid() && QModelIndex() == index.parent()
        && 0 == index.column() && mPlugins.size() > index.row();
}


void PanelPluginsModel::onMovePluginDown(QModelIndex const & index)
{
    if (!isIndexValid(index))
        return;

    const int row = index.row();
    if (mPlugins.size() <= row + 1)
        return; //can't move down

    beginMoveRows(QModelIndex(), row, row, QModelIndex(), row + 2);
    mPlugins.swap(row, row + 1);
    endMoveRows();
    pluginslist_t::const_reference moved_plugin = mPlugins[row + 1];
    pluginslist_t::const_reference next_plugin = mPlugins[row];

    emit pluginMoved(moved_plugin.second.data());
    //emit signal for layout only in case both plugins are loaded/displayed
    if (!moved_plugin.second.isNull() && !next_plugin.second.isNull())
        emit pluginMovedUp(next_plugin.second.data());

    mPanel->settings()->setValue(mNamesKey, pluginNames());
}

void PanelPluginsModel::onRemovePlugin(QModelIndex const & index)
{
    if (!isIndexValid(index))
        return;

    auto plugin = mPlugins.begin() + index.row();
    if (plugin->second.isNull())
        removePlugin(std::move(plugin));
    else
        plugin->second->requestRemove();
}

void PanelPluginsModel::onConfigurePlugin(QModelIndex const & index)
{
    if (!isIndexValid(index))
        return;

    Plugin * const plugin = mPlugins[index.row()].second.data();
    if (nullptr != plugin && (ILXQtPanelPlugin::HaveConfigDialog & plugin->iPlugin()->flags()))
        plugin->showConfigureDialog();
}

QList<Plugin *> PanelPluginsModel::plugins() const
{
    QList<Plugin *> plugins;
    for (auto const & p : mPlugins)
        if (!p.second.isNull())
            plugins.append(p.second.data());
    return plugins;
}



