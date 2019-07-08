#include <QtDebug>
#include "panelpluginsmodel.h"
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

	loadPlugin(list.first(), name);	
}

void PanelPluginsModel::loadPlugin(LXQt::PluginInfo const & desktopFile, QString const & settingsGroup)
{
        qDebug() << "hello2";
    std::unique_ptr<Plugin> plugin(new Plugin(desktopFile, mPanel->settings(), settingsGroup, mPanel));
//        return plugin.release();
}

