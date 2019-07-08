#ifndef PANELPLUGINSMODEL_H
#define PANELPLUGINSMODEL_H
#include <QAbstractListModel>
#include "ukuipanel.h"
#include "plugin.h"
class UkuiPanel;
class Plugin;
class PanelPluginsModel : public QAbstractListModel
{
public:	
    PanelPluginsModel(UkuiPanel * panel,
                      QString const & namesKey,
                      QStringList const & desktopDirs);

    //来自于QAbstractListModel的纯虚函数
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
private:
    void loadPlugins(QStringList const & desktopDirs);
    void loadPlugin(LXQt::PluginInfo const & desktopFile, QString const & settingsGroup);
    UkuiPanel * mPanel;
};
#endif // PANELPLUGINSMODEL_H
