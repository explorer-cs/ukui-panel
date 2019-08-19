#ifndef PANELPLUGINSMODEL_H
#define PANELPLUGINSMODEL_H
#include <QAbstractListModel>
#include "ukuipanel.h"
#include "plugin.h"

class UkuiPanel;
class Plugin;

namespace LXQt
{
    class PluginInfo;
    struct PluginData;
}


class PanelPluginsModel : public QAbstractListModel
{
    Q_OBJECT
public:	
    PanelPluginsModel(UkuiPanel * panel,
                      QString const & namesKey,
                      QStringList const & desktopDirs);

    //来自于QAbstractListModel的纯虚函数
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

signals:
    /*!
     * \brief pluginAdded gets emitted whenever a new Plugin is added
     * to the panel.
     */
    void pluginAdded(Plugin * plugin);
    /*!
     * \brief pluginRemoved gets emitted whenever a Plugin is removed.
     * \param plugin The Plugin that was removed. This could be a nullptr.
     */
    void pluginRemoved(Plugin * plugin);
    /*!
     * \brief pluginMoved gets emitted whenever a Plugin is moved.
     *
     * This signal gets emitted in movePlugin, onMovePluginUp and
     * onMovePluginDown.
     *
     * \param plugin The Plugin that was moved. This could be a nullptr.
     *
     * \sa pluginMovedUp
     */
    void pluginMoved(Plugin * plugin); //plugin can be nullptr in case of move of not loaded plugin
public slots:
    void addPlugin(const LXQt::PluginInfo &desktopFile);
    Plugin const *pluginByID(QString id) const;
    void removePlugin();


private:
    void loadPlugins(QStringList const & desktopDirs);

    QPointer<Plugin> loadPlugin(LXQt::PluginInfo const & desktopFile, QString const & settingsGroup);

    QString findNewPluginSettingsGroup(const QString &pluginType) const;

    QStringList pluginNames() const;

    UkuiPanel * mPanel;
    typedef QList<QPair <QString/*name*/, QPointer<Plugin> > > pluginslist_t;
    pluginslist_t mPlugins;

    void removePlugin(pluginslist_t::iterator plugin);

    const QString mNamesKey;
};
#endif // PANELPLUGINSMODEL_H
