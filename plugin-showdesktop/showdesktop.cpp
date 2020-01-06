/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
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

#include <QAction>
#include <QX11Info>
//#include <XdgIcon>
#include "xdgicon.h"
//#include <LXQt/Notification>
#include "../common/lxqtnotification.h"
#include <KWindowSystem/KWindowSystem>
#include <KWindowSystem/NETWM>
#include "showdesktop.h"
#include "../panel/pluginsettings.h"

#define DEFAULT_SHORTCUT "Control+Alt+D"

#define DESKTOP_HEIGHT  (12)
#define DESKTOP_WIDTH   (40)

ShowDesktop::ShowDesktop(const IUKUIPanelPluginStartupInfo &startupInfo) :
    QObject(),
    IUKUIPanelPlugin(startupInfo)
{

    QAction * act = new QAction(XdgIcon::fromTheme("ukui-icon-theme-one"), tr(""), this);
    connect(act, SIGNAL(triggered()), this, SLOT(toggleShowingDesktop()));

    mButton.setDefaultAction(act);
    mButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mButton.setAutoRaise(true);
    realign();

}

void ShowDesktop::realign()
{
    if(panel()->isHorizontal())
    {
        mButton.setFixedSize(DESKTOP_HEIGHT,DESKTOP_WIDTH);
    }
    else
    {
       mButton.setFixedSize(DESKTOP_WIDTH,DESKTOP_HEIGHT);
    }
}

void ShowDesktop::toggleShowingDesktop()
{
    KWindowSystem::setShowingDesktop(!KWindowSystem::showingDesktop());
}

#undef DEFAULT_SHORTCUT
