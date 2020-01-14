/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * UKUi - a lightweight, Qt based, desktop toolset
 * https://ukui.org
 *
 * Copyright: 2011 Razor team
 *            2014 UKUi team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *   Maciej Płaza <plaza.maciej@gmail.com>
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

#ifndef UKUITASKGROUP_H
#define UKUITASKGROUP_H

#include "../panel/iukuipanel.h"
#include "../panel/iukuipanelplugin.h"
#include "ukuitaskbar.h"
#include "ukuigrouppopup.h"
#include "ukuitaskbutton.h"
#include <KF5/KWindowSystem/kwindowsystem.h>

class QVBoxLayout;
class IUKUIPanelPlugin;

class UKUIGroupPopup;
class UKUiMasterPopup;

class UKUITaskGroup: public UKUITaskButton
{
    Q_OBJECT

public:
    UKUITaskGroup(const QString & groupName, WId window, UKUITaskBar * parent);

    QString groupName() const { return mGroupName; }

    int buttonsCount() const;
    int visibleButtonsCount() const;

    UKUITaskButton * addWindow(WId id);
    UKUITaskButton * checkedButton() const;

    // Returns the next or the previous button in the popup
    // if circular is true, then it will go around the list of buttons
    UKUITaskButton * getNextPrevChildButton(bool next, bool circular);

    bool onWindowChanged(WId window, NET::Properties prop, NET::Properties2 prop2);
    void setAutoRotation(bool value, IUKUIPanel::Position position);
    Qt::ToolButtonStyle popupButtonStyle() const;
    void setToolButtonsStyle(Qt::ToolButtonStyle style);

    void setPopupVisible(bool visible = true, bool fast = false);
    void showPreview();
    void removeWidget();

public slots:
    void onWindowRemoved(WId window);

protected:
    QMimeData * mimeData();

    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);
    void dragEnterEvent(QDragEnterEvent * event);
    void dragLeaveEvent(QDragLeaveEvent * event);
    void contextMenuEvent(QContextMenuEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    int recalculateFrameHeight() const;
    int recalculateFrameWidth() const;

    void draggingTimerTimeout();

private slots:
    void onClicked(bool checked);
    void onChildButtonClicked();
    void onActiveWindowChanged(WId window);
    void onDesktopChanged(int number);

    void closeGroup();
    void refreshIconsGeometry();
    void refreshVisibility();
    void groupPopupShown(UKUITaskGroup* sender);

signals:
    void groupBecomeEmpty(QString name);
    void visibilityChanged(bool visible);
    void popupShown(UKUITaskGroup* sender);

private:
    QString mGroupName;
    UKUIGroupPopup * mPopup;
    UKUITaskButtonHash mButtonHash;
    bool mPreventPopup;
    bool mSingleButton; //!< flag if this group should act as a "standard" button (no groupping or only one "shown" window in group)

    QSize recalculateFrameSize();
    QPoint recalculateFramePosition();
    void recalculateFrameIfVisible();
    void regroup();
};

#endif // UKUITASKGROUP_H
