#include "widget.h"
#include "ui_widget.h"
#include "dbus.h"
#include "dbus-adaptor.h"
#include <QDebug>
#include <QDBusConnection>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("服务端");
    register_dbus();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::register_dbus()
{
    DBus* dbus=new DBus;
    new FilectrlAdaptor(dbus);
    QDBusConnection con=QDBusConnection::sessionBus();
    if(!con.registerService("com.kylin.security.controller.filectrl") ||
            !con.registerObject("/",dbus))
    {
        qDebug()<<"fail";
    }
}
