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

#include "ukuiquicklaunch.h"
#include "quicklaunchbutton.h"
#include "quicklaunchaction.h"
#include "../panel/iukuipanelplugin.h"
#include <QDesktopServices>
#include <QDragEnterEvent>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QLabel>
#include <QMessageBox>
#include <QToolButton>
#include <QUrl>
#include <QDebug>
#include <XdgDesktopFile>
#include <XdgIcon>
#include <LXQt/GridLayout>
#include "../panel/pluginsettings.h"
#include <QTableWidget>
using namespace  std;

UKUIQuickLaunch::UKUIQuickLaunch(IUKUIPanelPlugin *plugin, QWidget* parent) :
    QFrame(parent),
    mPlugin(plugin),
    mPlaceHolder(0)
{
    setAcceptDrops(true);

    mLayout = new LXQt::GridLayout(this);
    setLayout(mLayout);

    QString desktop;
    QString file;
    QString execname;
    QString exec;
    QString icon;

    const auto apps = mPlugin->settings()->readArray("apps");
    for (const QMap<QString, QVariant> &app : apps)
    {
        desktop = app.value("desktop", "").toString();
        file = app.value("file", "").toString();
        if (!desktop.isEmpty())
        {
            XdgDesktopFile xdg;
            if (!xdg.load(desktop))
            {
                qDebug() << "XdgDesktopFile" << desktop << "is not valid";
                continue;
            }
            if (!xdg.isSuitable())
            {
                qDebug() << "XdgDesktopFile" << desktop << "is not applicable";
                continue;
            }

            addButton(new QuickLaunchAction(&xdg, this));
        }
        else if (! file.isEmpty())
        {
            addButton(new QuickLaunchAction(file, this));
        }
        else
        {
            execname = app.value("name", "").toString();
            exec = app.value("exec", "").toString();
            icon = app.value("icon", "").toString();
            if (icon.isNull())
            {
                qDebug() << "Icon" << icon << "is not valid (isNull). Skipped.";
                continue;
            }
            addButton(new QuickLaunchAction(execname, exec, icon, this));
        }
    } // for

    if (mLayout->isEmpty())
        showPlaceHolder();

    realign();
    mLayout->setSpacing(80);
}


UKUIQuickLaunch::~UKUIQuickLaunch()
{
}


int UKUIQuickLaunch::indexOfButton(QuickLaunchButton* button) const
{
    return mLayout->indexOf(button);
}


int UKUIQuickLaunch::countOfButtons() const
{
    return mLayout->count();
}


void UKUIQuickLaunch::realign()
{
    mLayout->setEnabled(false);
    IUKUIPanel *panel = mPlugin->panel();

    if (mPlaceHolder)
    {
        mLayout->setColumnCount(1);
        mLayout->setRowCount(1);
    }
    else
    {
        if (panel->isHorizontal())
        {
            mLayout->setRowCount(panel->lineCount());
            mLayout->setColumnCount(0);
        }
        else
        {
            mLayout->setColumnCount(panel->lineCount());
            mLayout->setRowCount(0);
        }
    }
    mLayout->setEnabled(true);
}

void UKUIQuickLaunch::addButton(QuickLaunchAction* action)
{
    mLayout->setEnabled(false);
    QuickLaunchButton* btn = new QuickLaunchButton(action, mPlugin, this);
    btn->setFixedSize(45,40);
    mLayout->addWidget(btn);

    //set button style
    btn->setStyleSheet(
                //正常状态样式
                "QToolButton{"
                /*"background-color:rgba(100,225,100,80%);"//背景色（也可以设置图片）*/
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:0px;"                     //边框宽度像素
                "border-radius:0px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "font:bold 14px;"                       //字体，字体大小
                "color:rgba(0,0,0,100);"                //字体颜色
                "padding:0px;"                          //填衬
                "}"
                //鼠标按下样式
                "QToolButton:pressed{"
                "background-color:rgba(190,216,239,12%);"
                "}"
                //鼠标悬停样式
                "QToolButton:hover{"
                "background-color:rgba(190,216,239,20%);"
                "}");

    connect(btn, SIGNAL(switchButtons(QuickLaunchButton*,QuickLaunchButton*)), this, SLOT(switchButtons(QuickLaunchButton*,QuickLaunchButton*)));
    connect(btn, SIGNAL(buttonDeleted()), this, SLOT(buttonDeleted()));
    connect(btn, SIGNAL(movedLeft()), this, SLOT(buttonMoveLeft()));
    connect(btn, SIGNAL(movedRight()), this, SLOT(buttonMoveRight()));

    mLayout->removeWidget(mPlaceHolder);
    delete mPlaceHolder;
    mPlaceHolder = 0;
    mLayout->setEnabled(true);
    realign();
}


//void UKUIQuickLaunch::addButton(QString *filename,QuickLaunchAction* action)
//{

//    mLayout->setEnabled(false);
//    QuickLaunchButton* btn = new QuickLaunchButton(filename,action, mPlugin, this);
//    mLayout->addWidget(btn);
//    mbtnmap.insert(*filename,btn);


//    connect(btn, SIGNAL(switchButtons(QuickLaunchButton*,QuickLaunchButton*)), this, SLOT(switchButtons(QuickLaunchButton*,QuickLaunchButton*)));
//    connect(btn, SIGNAL(buttonDeleted()), this, SLOT(buttonDeleted()));
//    connect(btn, SIGNAL(movedLeft()), this, SLOT(buttonMoveLeft()));
//    connect(btn, SIGNAL(movedRight()), this, SLOT(buttonMoveRight()));

//    mLayout->removeWidget(mPlaceHolder);
//    delete mPlaceHolder;
//    mPlaceHolder = 0;
//    mLayout->setEnabled(true);
//    realign();
//}

void UKUIQuickLaunch::removeButton(QString *filename)
{
    int i = 0;
    QLayoutItem *child;

    while ((child = mLayout->layout()->itemAt(i))) {
        qDebug()<<i;
        QuickLaunchButton *b = qobject_cast<QuickLaunchButton*>(mLayout->itemAt(i)->widget());
        //qDebug()<<"b->file_name   >>>"<<b->file_name;
            if (b->file_name == filename) {
                qDebug()<<"child   >>>"<<child;
                //mLayout->removeItem(child);
                mLayout->removeWidget(b);
                b->deleteLater();
            } else {
                ++i;
            }
        }
        saveSettings();
}


void UKUIQuickLaunch::dragEnterEvent(QDragEnterEvent *e)
{
    // Getting URL from mainmenu...
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
        return;
    }

    if (e->source() && e->source()->parent() == this)
    {
        e->acceptProposedAction();
    }
}


void UKUIQuickLaunch::dropEvent(QDropEvent *e)
{
    const auto urls = e->mimeData()->urls().toSet();
    for (const QUrl &url : urls)
    {
        QString fileName(url.isLocalFile() ? url.toLocalFile() : url.url());
        QFileInfo fi(fileName);
        XdgDesktopFile xdg;
        if (xdg.load(fileName))
        {
            if (xdg.isSuitable())
                addButton(new QuickLaunchAction(&xdg, this));
        }
        else if (fi.exists() && fi.isExecutable() && !fi.isDir())
        {
            addButton(new QuickLaunchAction(fileName, fileName, "", this));
        }
        else if (fi.exists())
        {
            addButton(new QuickLaunchAction(fileName, this));
        }
        else
        {
            qWarning() << "XdgDesktopFile" << fileName << "is not valid";
            QMessageBox::information(this, tr("Drop Error"),
                              tr("File/URL '%1' cannot be embedded into QuickLaunch for now").arg(fileName)
                            );
        }
    }
    saveSettings();
    QString filepath="/home/hepuyao/桌面/firefox.desktop";
    AddToTaskbar(&filepath);
}


void UKUIQuickLaunch::AddToTaskbar(QString *desktop)
{
    QString *mdesktop=desktop;
    const auto url=QUrl(*mdesktop);
    QString fileName(url.isLocalFile() ? url.toLocalFile() : url.url());
    QFileInfo fi(fileName);
    XdgDesktopFile xdg;
    //add by QuickLaunchAction(&xdg, this)
    if (xdg.load(fileName))
    {
        if (xdg.isSuitable())
            addButton(new QuickLaunchAction(&xdg, this));
    }
    else if (fi.exists() && fi.isExecutable() && !fi.isDir())
    {
        addButton(new QuickLaunchAction(fileName, fileName, "", this));
    }
    else if (fi.exists())
    {
        addButton(new QuickLaunchAction(fileName, this));
    }
    else
    {
        qWarning() << "XdgDesktopFile" << fileName << "is not valid";
        QMessageBox::information(this, tr("Drop Error"),
                          tr("File/URL '%1' cannot be embedded into QuickLaunch for now").arg(fileName)
                        );
    }
    saveSettings();
}

void UKUIQuickLaunch::AddToTaskbar(QString *filename, QString *exec, QString *iconpath)
{
    QString *filename1=filename;
    addButton(new QuickLaunchAction(*filename,*exec,*iconpath,this));
    saveSettings();
}

void  UKUIQuickLaunch::CheckIfExist(QString *filename)
{
    int i = 0;
    QLayoutItem *child;

    while ((child = mLayout->layout()->itemAt(i))) {
        qDebug()<<i;
        QuickLaunchButton *b = qobject_cast<QuickLaunchButton*>(mLayout->itemAt(i)->widget());
        if (b->file_name == filename) {
            qDebug()<<" already  insert"<<child;
        } else {
            ++i;
            qDebug()<<"don't insert";
        }
     }

}

void UKUIQuickLaunch::RemoveFromTaskbar(QString *filename)
{
    QString *file_name=filename;
    removeButton(file_name);

}

void UKUIQuickLaunch::switchButtons(QuickLaunchButton *button1, QuickLaunchButton *button2)
{
    if (button1 == button2)
        return;

    int n1 = mLayout->indexOf(button1);
    int n2 = mLayout->indexOf(button2);

    int l = qMin(n1, n2);
    int m = qMax(n1, n2);

    mLayout->moveItem(l, m);
    mLayout->moveItem(m-1, l);
    saveSettings();
}


//void UKUIQuickLaunch::buttonDeleted(xdg)
//{

//    QLayoutItem *child;
//    while ((child = mLayout->layout()->itemAt(i))) {
//            if (child->widget() == btn) {
//                qDebug()<<"child   >>>"<<child;
//                mLayout->removeItem(child);
//            } else {
//                ++i;
//            }
//        }
//    mLayout->removeWidget(btn);
//    btn->deleteLater();
//    saveSettings();

//    if (mLayout->isEmpty())
//        showPlaceHolder();
//    realign();
//}

void UKUIQuickLaunch::buttonDeleted()
{
    QuickLaunchButton *btn = qobject_cast<QuickLaunchButton*>(sender());
    if (!btn)
        return;
    mLayout->removeWidget(btn);
    btn->deleteLater();
    saveSettings();

    if (mLayout->isEmpty())
        showPlaceHolder();
    realign();
}


void UKUIQuickLaunch::buttonMoveLeft()
{
    /*old code
    QuickLaunchButton *btn = qobject_cast<QuickLaunchButton*>(sender());
    if (!btn)
        return;

    int index = indexOfButton(btn);
    if (index > 0)
    {
        mLayout->moveItem(index, index - 1);
        saveSettings();
    }
    */
    QString filename="firefox";
//    QString file_name=filename;
//    qDebug()<<"filename   >>>"<<filename;
//    qDebug()<<"filename&   >>>"<<&filename;
//    QString exec="firefox";
//    QString iconpath="/usr/share/icons/hicolor/128x128/apps/chromium-browser.png";
  // qDebug()<<CheckIfExist(&filename);
    removeButton(&filename);


}


void UKUIQuickLaunch::buttonMoveRight()
{
    /*  old code
    QuickLaunchButton *btn1 = qobject_cast<QuickLaunchButton*>(sender());
    if (!btn1)
        return;

    int index = indexOfButton(btn1);
    if (index < countOfButtons() - 1)
    {
        mLayout->moveItem(index, index + 1);
        saveSettings();
    }
    */
//    QString filename2="qtcreator";
//    QString exec2="qtcreator";
//    QString iconpath2="/home/hepuyao/图片/001.png";
//    AddToTaskbar(&filename2,&exec2,&iconpath2);
//    QString filename="firefox";
//    QString exec="firefox";
//    QString iconpath="/home/hepuyao/图片/002.png";
//    AddToTaskbar(&filename,&exec,&iconpath);

//    QString filename="firefox";
//    QString exec="firefox";
//    QString iconpath="/usr/share/icons/hicolor/128x128/apps/chromium-browser.png";
//    AddToTaskbar(&filename,&exec,&iconpath);

//    filename="baidunetdisk";
//    exec="baidunetdisk";
//    iconpath="/usr/share/icons/hicolor/128x128/apps/baidunetdisk.png";
//    AddToTaskbar(&filename,&exec,&iconpath);


     QString filename="fcitx";
     QString exec="fcitx";
     QString iconpath="/usr/share/icons/hicolor/128x128/apps/fcitx.png";
     AddToTaskbar(&filename,&exec,&iconpath);

         filename="baidunetdisk";
         exec="baidunetdisk";
         iconpath="/usr/share/icons/hicolor/128x128/apps/baidunetdisk.png";
         AddToTaskbar(&filename,&exec,&iconpath);

//              filename="firefox";
//              exec="firefox";
//              iconpath="/usr/share/icons/hicolor/128x128/apps/chromium-browser.png";
//             AddToTaskbar(&filename,&exec,&iconpath);

    

}


void UKUIQuickLaunch::saveSettings()
{
    PluginSettings *settings = mPlugin->settings();
    settings->remove("apps");

    QList<QMap<QString, QVariant> > hashList;
    int size = mLayout->count();
    for (int j = 0; j < size; ++j)
    {
        QuickLaunchButton *b = qobject_cast<QuickLaunchButton*>(mLayout->itemAt(j)->widget());
        if (!b)
            continue;

        // convert QHash<QString, QString> to QMap<QString, QVariant>
        QMap<QString, QVariant> map;
        QHashIterator<QString, QString> it(b->settingsMap());
        while (it.hasNext())
        {
            it.next();
            map[it.key()] = it.value();
        }
        hashList << map;
    }

    settings->setArray("apps", hashList);
    hashList.removeLast();

}


void UKUIQuickLaunch::showPlaceHolder()
{
    if (!mPlaceHolder)
    {
        mPlaceHolder = new QLabel(this);
        mPlaceHolder->setAlignment(Qt::AlignCenter);
        mPlaceHolder->setObjectName("QuickLaunchPlaceHolder");
        mPlaceHolder->setText(tr("Drop application\nicons here"));
    }

    mLayout->addWidget(mPlaceHolder);
}
