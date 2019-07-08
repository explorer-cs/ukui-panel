#include "pluginsettings.h"
class PluginSettingsPrivate
{
public:
    PluginSettingsPrivate(LXQt::Settings* settings, const QString &group)
        : mSettings(settings)
        , mOldSettings(settings)
        , mGroup(group)
    {
    }

    QString prefix() const;
    inline QString fullPrefix() const
    {
        return mGroup + "/" + prefix();
    }

    LXQt::Settings *mSettings;
    LXQt::SettingsCache mOldSettings;
    QString mGroup;
    QStringList mSubGroups;
};

PluginSettings::PluginSettings(LXQt::Settings* settings, const QString &group, QObject *parent)
	: QObject(parent)
	  ,d_ptr(new PluginSettingsPrivate {settings, group})
{
	
}
PluginSettings* PluginSettingsFactory::create(LXQt::Settings *settings, const QString &group, QObject *parent/* = nullptr*/)
{
    return new PluginSettings{settings, group, parent};
}

