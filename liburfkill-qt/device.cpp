/**************************************************************************
 *                                                                        *
 *  Copyright (C) 2012 by Max Lin <max.lin@gmx.com>                       *
 *                                                                        *
 *  This program is free software; you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation; either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful, but   *
 *  WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *  General Public License for more details.                              *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program; see the file COPYING. If not, write to the   *
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 *  Boston, MA 02110-1301, USA.                                           *
 **************************************************************************/

#include <QtDBus>
#include <QDebug>

#include "urfkill.h"
#include "device.h"

void Device::refreshDeviceProperties()
{
    m_name = deviceIface->property("name").toString();
    m_hard = deviceIface->property("hard").toBool();
    m_soft = deviceIface->property("soft").toBool();
    m_type = deviceIface->property("type").toInt();
    m_index = deviceIface->property("index").toInt();
}

void Device::propertyChanged()
{
    //qDebug() << "changed!";
    refreshDeviceProperties();
    emit triggerPropertyChanged();
}

Device::Device(const QString &devicePath)
{
    QDBusConnection conn = QDBusConnection::systemBus();
    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug() << "Cannot connect to the D-Bus system bus.";

        return;
    }

    deviceIface = new QDBusInterface(URFKILL_SERVICE, devicePath, URFKILL_DEVICE_INTERFACE, conn, this);
    if (!deviceIface->isValid()) {
        qDebug() << "Can not create DBus interface!";
        qDebug() << QDBusConnection::systemBus().lastError().message();

        return;
    }

    refreshDeviceProperties();

    connect(deviceIface, SIGNAL(Changed()), this, SLOT(propertyChanged()));
}

Device::~Device()
{
}

bool Device::platform() const
{
    return m_platform;
}

bool Device::hard() const
{
    return m_hard;
}

bool Device::soft() const
{
    return m_soft;
}

QString Device::name() const
{
    return m_name;
}

uint Device::type() const
{
    return m_type;
}

uint Device::index() const
{
    return m_index;
}
