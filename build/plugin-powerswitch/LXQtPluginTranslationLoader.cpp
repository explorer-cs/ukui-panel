/* This file has been generated by the CMake lxqt_plugin_translation_loader().
 * It loads LXQt plugin translations.
 *
 * Attention: All changes will be overwritten!!!
 */

#include <QCoreApplication>
#include <QLatin1String>

#include <LXQt/Translator>

/* Dummy helper symbol for referencing.
 * In case plugin is linked as static (lib*.a) unreferenced objects are stripped in linking time
 *  => we need to reference some symbol from this file to be not stripped as a whole.
 */
void * loadPluginTranslation_powerswitch_helper = nullptr;

static void loadPluginTranslation()
{
    //XXX: we don't use the QStringLiteral here because it causes SEGFAULT in static finalization time
    // (the string is stored in static QHash and it's destructor can reference already deleted static QString (generated by QStringLiteral))
    LXQt::Translator::translatePlugin(QLatin1String("powerswitch"), QLatin1String("ukui-panel"));
}

Q_COREAPP_STARTUP_FUNCTION(loadPluginTranslation)
