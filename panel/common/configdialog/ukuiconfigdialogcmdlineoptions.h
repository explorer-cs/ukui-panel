/*
 * UKUi - a lightweight, Qt based, desktop toolset
 * https://ukui.org
 *
 * Copyright (C) 2018  Luís Pereira <luis.artur.pereira@gmail.com>
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
 */

#ifndef UKUICONFIGDIALOGCMDLINEOPTIONS_H
#define UKUICONFIGDIALOGCMDLINEOPTIONS_H

#include "../ukuiglobals.h"

#include <QScopedPointer>
#include <QString>

class QCommandLineParser;

namespace UKUi {

class ConfigDialogCmdLineOptionsPrivate;

class UKUI_API ConfigDialogCmdLineOptions
{
public:
    ConfigDialogCmdLineOptions();
    ~ConfigDialogCmdLineOptions();

    bool setCommandLine(QCommandLineParser *parser);
    void process(QCommandLineParser &parser);

    QString page() const;

private:
    Q_DISABLE_COPY(ConfigDialogCmdLineOptions)
    QScopedPointer<ConfigDialogCmdLineOptionsPrivate> const d;
};

} // UKUi namespace

#endif // UKUICONFIGDIALOGCMDLINEOPTIONS_H
