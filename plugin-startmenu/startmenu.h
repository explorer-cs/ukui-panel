#ifndef STARTMENU_H
#define STARTMENU_H

#include "../panel/iukuipanelplugin.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFrame>
#include <QFontMetrics>
#include <QLineEdit>
#include <QToolButton>
#include <XdgIcon>


#include <QMainWindow>
#include <QHBoxLayout>
#include <QDebug>
#include <QProcess>

#include "../panel/plugin.h"
#include "../panel/ukuipanel.h"
//#include "../panel/config/configpaneldialog.h"
#include "../panel/config/configpanelwidget.h"
#include <QMenu>
#include <QtDBus/QtDBus>
<<<<<<< HEAD
=======
#define DEFAULT_SHORTCUT "Alt+F1"
>>>>>>> master


class StartMenu : public QObject, public IUKUIPanelPlugin
{
    Q_OBJECT
<<<<<<< HEAD
=======
//    //use d-bus model to Interaction with ukui-menu
//    Q_CLASSINFO("D-Bus Interface", "com.ukui.panel.positon")
//    Q_CLASSINFO("D-Bus position", ""
//"  <interface name=\"com.ukui.panel.position\">\n"
//"    <method name=\"GetPanelPosition\">\n"
//"      <arg direction=\"out\" type=\"b\"/>\n"
//"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
//"    </method>\n"
//"  </interface>\n"
//        "")

>>>>>>> master
public:
    StartMenu(const IUKUIPanelPluginStartupInfo &startupInfo);
    ~StartMenu();

    virtual QWidget *widget() { return &mButton; }
    virtual QString themeId() const { return QStringLiteral("startmenu"); }
    void realign();
    virtual IUKUIPanelPlugin::Flags flags() const { return PreferRightAlignment | HaveConfigDialog ; }
private:
    //StartMenuWidget mWidget;
    IUKUIPanelPlugin *mPlugin;
    QToolButton mButton;
    StartMenu *mStartMenu;
    bool mCapturing;

<<<<<<< HEAD
=======
public slots:
    bool GetPanelPosition(QString arg);
>>>>>>> master
private slots:
    void captureMouse();

};

<<<<<<< HEAD
=======
//class FilectrlAdaptor: public QDBusAbstractAdaptor
//{
//    Q_OBJECT

//    //use d-bus model to Interaction with ukui-menu
//    Q_CLASSINFO("D-Bus Interface", "com.ukui.panel.position")
//    Q_CLASSINFO("D-Bus Introspection", ""
//"  <interface name=\"com.ukui.panel.position\">\n"
//"    <method name=\"GetPanelPosition\">\n"
//"      <arg direction=\"out\" type=\"b\"/>\n"
//"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
//"    </method>\n"
//"  </interface>\n"
//        "")
//public:
//    FilectrlAdaptor(QObject *parent);
//    virtual ~FilectrlAdaptor();

//public: // PROPERTIES
//public Q_SLOTS: // METHODS
//    bool GetPanelPosition(const QString &arg);

//Q_SIGNALS: // SIGNALS

//signals:
//    void addtak(int);
//};

>>>>>>> master
class StartMenuLibrary: public QObject, public IUKUIPanelPluginLibrary
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "lxqt.org/Panel/PluginInterface/3.0")
    Q_INTERFACES(IUKUIPanelPluginLibrary)
public:
    IUKUIPanelPlugin *instance(const IUKUIPanelPluginStartupInfo &startupInfo) const
    {
        return new StartMenu(startupInfo);
    }
};


#endif
