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
    QString prefix() const
    {
        if (!mSubGroups.empty())
            return mSubGroups.join('/');
        return QString();
    }

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

QVariant PluginSettings::value(const QString &key, const QVariant &defaultValue) const
{
    Q_D(const PluginSettings);
    d->mSettings->beginGroup(d->fullPrefix());
    QVariant value = d->mSettings->value(key, defaultValue);
    d->mSettings->endGroup();
    return value;
}

