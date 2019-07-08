#include <QObject>
#include <LXQt/Settings>

class PluginSettingsPrivate;

class PluginSettings : public QObject
{
public:	
	PluginSettings(LXQt::Settings *settings, const QString &group, QObject *parent = nullptr);
	QScopedPointer<PluginSettingsPrivate> d_ptr;
	Q_DECLARE_PRIVATE(PluginSettings)
};
class PluginSettingsFactory
{
public:
    static PluginSettings * create(LXQt::Settings *settings, const QString &group, QObject *parent = nullptr);
};

