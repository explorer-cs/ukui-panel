#include "dbus.h"
#include "widget.h"
#include <QDebug>
DBus::DBus(QObject *parent) : QObject(parent)
{
    Widget w;
    w.show();
    qDebug()<<" d-bus-server"<<endl;

}

bool DBus::AddToTaskbar(QString arg)
{
    return false;
}

bool DBus::RemoveFromTaskbar(QString arg)
{
    return true;   
}
bool DBus::CheckIfExist(QString arg)
{
    return true;
}
