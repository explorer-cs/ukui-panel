#ifndef DBUS_H
#define DBUS_H

#include <QObject>

class DBus : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface","com.kylin.security.controller.filectrl")
public:
    explicit DBus(QObject *parent = 0);

public slots:
    bool AddToTaskbar(QString arg);
    bool RemoveFromTaskbar(QString arg);
    bool CheckIfExist(QString arg);
};

#endif // DBUS_H
