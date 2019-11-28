/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2010-2012 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *   Kuzma Shapran <kuzma.shapran@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#ifndef UKUIQUICKLAUNCH_H
#define UKUIQUICKLAUNCH_H

#include "../panel/ukuipanel.h"
#include <QHash>
#include <QString>
#include <QMap>
#include "qlayout.h"
#include "qlayoutitem.h"
#include "qlayoutitem.h"
#include "qgridlayout.h"
//-----------------dbus
#include <QtCore/QObject>
#include <QtDBus/QtDBus>

QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE
//-----------------------

class XdgDesktopFile;
class QuickLaunchAction;
class QDragEnterEvent;
class QuickLaunchButton;
class QSettings;
class QLabel;

namespace LXQt {
class GridLayout;
}


/*! \brief Loader for "quick launcher" icons in the panel.
\author Petr Vanek <petr@scribus.info>
*/
class UKUIQuickLaunch : public QFrame
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "com.kylin.security.controller.filectrl")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.kylin.security.controller.filectrl\">\n"
"    <method name=\"AddToTaskbar\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
"    </method>\n"
"    <method name=\"RemoveFromTaskbar\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
"    </method>\n"
"    <method name=\"CheckIfExist\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")

public:
   UKUIQuickLaunch(IUKUIPanelPlugin *plugin, QWidget* parent = 0);
    ~UKUIQuickLaunch();

    int indexOfButton(QuickLaunchButton* button) const;
    int countOfButtons() const;

    void realign();
    //virtual QLayoutItem *takeAt(int index) = 0;
    void saveSettings();
    void showPlaceHolder();
    void AddToTaskb(QString *desktop);
    void AddToTaskbar(QString *filename,QString *exec,QString *iconpath);
    void CheckIfExist(QString *desktop);
    void RemoveFromTaskbar(QString *desktop);
    bool AddToTaskb(const QString &arg);

    friend class FilectrlAdaptor;

private:
    LXQt::GridLayout *mLayout;
    IUKUIPanelPlugin *mPlugin;
    QLabel *mPlaceHolder;

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);





private slots:
    void addButton(QuickLaunchAction* action);
    void checkButton(QuickLaunchAction* action);
    void checkButton(QString *filename);
    void removeButton(QString *filename);
    void removeButton(QuickLaunchAction* action);
    void switchButtons(QuickLaunchButton *button1, QuickLaunchButton *button2);
    void buttonDeleted();
    void buttonMoveLeft();
    void buttonMoveRight();

public slots:
    bool AddToTaskbar(QString arg);
    bool RemoveFromTaskbar(QString arg);
    bool CheckIfExist(QString arg);

};



class FilectrlAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.kylin.security.controller.filectrl")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.kylin.security.controller.filectrl\">\n"
"    <method name=\"AddToTaskbar\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
"    </method>\n"
"    <method name=\"RemoveFromTaskbar\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
"    </method>\n"
"    <method name=\"CheckIfExist\">\n"
"      <arg direction=\"out\" type=\"b\"/>\n"
"      <arg direction=\"in\" type=\"s\" name=\"arg\"/>\n"
"    </method>\n"
"  </interface>\n"
        "")
public:
    FilectrlAdaptor(QObject *parent);
    virtual ~FilectrlAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    bool AddToTaskbar(const QString &arg);
    bool CheckIfExist(const QString &arg);
    bool RemoveFromTaskbar(const QString &arg);

Q_SIGNALS: // SIGNALS

signals:
    void addtak(int);
};

class DBus : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface","com.kylin.security.controller.filectrl")
public:
    explicit DBus(QObject *parent = 0);


};
#endif
