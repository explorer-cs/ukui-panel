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

#include "ukuibacklight.h"
#include "ukuibacklight/virtual_backend.h"
#include "ukuibacklight/linux_backend/linuxbackend.h"

namespace UKUi {

Backlight::Backlight(QObject *parent):QObject(parent)
{
    m_backend = (VirtualBackEnd *) new LinuxBackend(this);
    connect(m_backend, &VirtualBackEnd::backlightChanged, this, &Backlight::backlightChangedSlot);
}

Backlight::~Backlight()
{
    delete m_backend;
}

int Backlight::getBacklight()
{
    return m_backend->getBacklight();
}

int Backlight::getMaxBacklight()
{
    return m_backend->getMaxBacklight();
}

bool Backlight::isBacklightAvailable()
{
    return m_backend->isBacklightAvailable();
}

bool Backlight::isBacklightOff()
{
    return m_backend->isBacklightOff();
}

void Backlight::setBacklight(int value)
{
    m_backend->setBacklight(value);
}

void Backlight::backlightChangedSlot(int value)
{
    emit backlightChanged(value);
}

} // namespace UKUi
