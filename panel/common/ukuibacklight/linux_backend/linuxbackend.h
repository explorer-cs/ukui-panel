/*
 * Copyright (C) 2016  P.L. Lucas
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef __LinuxBackend_H__
#define __LinuxBackend_H__

#include "../virtual_backend.h"
#include <QFileSystemWatcher>
#include <QTextStream>

namespace UKUi
{

class LinuxBackend:public VirtualBackEnd
{
Q_OBJECT

public:    
    LinuxBackend(QObject *parent = 0);
    ~LinuxBackend();
    
    bool isBacklightAvailable();
    bool isBacklightOff();
    void setBacklight(int value);
    int getBacklight();
    int getMaxBacklight();
    
signals:
    void backlightChanged(int value);

private slots:
    void closeBacklightStream();
    void fileSystemChanged(const QString & path);

private:
    QTextStream *backlightStream;
    int maxBacklight;
    int actualBacklight;
    QFileSystemWatcher *fileSystemWatcher;
};

} // namespace UKUi

#endif  // __LinuxBackend_H__