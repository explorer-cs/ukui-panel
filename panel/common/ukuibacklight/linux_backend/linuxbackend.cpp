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

#include "driver/libbacklight_backend.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "driver/libbacklight_backend.c"
#ifdef __cplusplus
}
#endif

#include "linuxbackend.h"
#include <QTimer>
#include <QDebug>

namespace UKUi {

LinuxBackend::LinuxBackend(QObject *parent):VirtualBackEnd(parent)
{
    maxBacklight = ukui_backlight_backend_get_max();
    backlightStream = NULL;
    if( isBacklightAvailable() ) {
        char *driver = ukui_backlight_backend_get_driver();
        fileSystemWatcher = new QFileSystemWatcher(this);
        fileSystemWatcher->addPath(QString::fromLatin1("/sys/class/backlight/%1/actual_brightness").arg(QL1S(driver)));
        fileSystemWatcher->addPath(QString::fromLatin1("/sys/class/backlight/%1/brightness").arg(QL1S(driver)));
        fileSystemWatcher->addPath(QString::fromLatin1("/sys/class/backlight/%1/bl_power").arg(QL1S(driver)));
        free(driver);
        actualBacklight = ukui_backlight_backend_get();
        connect(fileSystemWatcher, &QFileSystemWatcher::fileChanged,
            this, &LinuxBackend::fileSystemChanged);
    }
}

LinuxBackend::~LinuxBackend()
{
    delete backlightStream;
}

int LinuxBackend::getBacklight()
{
    actualBacklight = ukui_backlight_backend_get();
    return actualBacklight;
}

int LinuxBackend::getMaxBacklight()
{
    return maxBacklight;
}

bool LinuxBackend::isBacklightAvailable()
{
    return maxBacklight > 0;
}

bool LinuxBackend::isBacklightOff()
{
    return ukui_backlight_is_backlight_off() > 0;
}

void LinuxBackend::setBacklight(int value)
{
    if( ! isBacklightAvailable() )
        return;
    if( backlightStream == NULL ) {
        FILE *stream = ukui_backlight_backend_get_write_stream();
        backlightStream = new QTextStream(stream);
        // Close stream after 60 seconds
        QTimer::singleShot(60000, this, SLOT(closeBacklightStream()));
    }
    // normalize the value (to work around an issue in QSlider)
    value = qBound(0, value, maxBacklight);
    *backlightStream << value << endl;
}

void LinuxBackend::closeBacklightStream()
{
    if( backlightStream != NULL ) {
        delete backlightStream;
        backlightStream = NULL;
    }
}

void LinuxBackend::fileSystemChanged(const QString & /*path*/)
{
    int value = actualBacklight;
    if( value != getBacklight() ) {
        emit backlightChanged(actualBacklight);
    }
}

} // namespace UKUi
