/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Marat "Morion" Talipov <morion.self@gmail.com>
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
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef CONFIGPANELWIDGET_H
#define CONFIGPANELWIDGET_H

#include "../ukuipanel.h"
#include <QSettings>
#include <QTimer>
//#include <LXQt/ConfigDialog>
#include "../common/lxqtconfigdialog.h"

class UKUIPanel;

namespace Ui {
    class ConfigPanelWidget;
}

class ConfigPanelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigPanelWidget(UKUIPanel *panel, QWidget *parent = 0);
    ~ConfigPanelWidget();

    int screenNum() const { return mScreenNum; }
    IUKUIPanel::Position position() const { return mPosition; }
    void updateIconThemeSettings();
    IUKUIPanel::Position mPosition;

signals:
    void changed();

public slots:
    void reset();

void positionChanged_top();
void positionChanged_bottom();
void positionChanged_left();
void positionChanged_right();
void panelSizeChange_m();
void panelSizeChange_l();
void panelSizeChange_xl();


private slots:
    void editChanged();
    void widthTypeChanged();
    void positionChanged();
    void pickFontColor();
    void pickBackgroundColor();
    void pickBackgroundImage();

private:
    Ui::ConfigPanelWidget *ui;
    UKUIPanel *mPanel;
    int mScreenNum;


    void addPosition(const QString& name, int screen, UKUIPanel::Position position);
    void fillComboBox_position();
    void fillComboBox_alignment();
    void fillComboBox_icon();
    int indexForPosition(int screen, IUKUIPanel::Position position);
    int getMaxLength();

    // new values
    QColor mFontColor;
    QColor mBackgroundColor;

    // old values for reset
    int mOldPanelSize;
    int mOldIconSize;
    int mOldLineCount;
    int mOldLength;
    bool mOldLengthInPercents;
    UKUIPanel::Alignment mOldAlignment;
    IUKUIPanel::Position mOldPosition;
    bool mOldHidable;
    bool mOldVisibleMargin;
    int mOldAnimation;
    int mOldShowDelay;
    int mOldScreenNum;
    QColor mOldFontColor;
    QColor mOldBackgroundColor;
    QString mOldBackgroundImage;
    int mOldOpacity;
    bool mOldReserveSpace;
};

#endif
