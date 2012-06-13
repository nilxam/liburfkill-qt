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

#include <QCoreApplication>
#include <QDebug>
#include <QtDBus>
#include <QList>
#include <QDBusObjectPath>

#include <liburfkill-qt/device.h>
#include <liburfkill-qt/killswitch.h>
#include <liburfkill-qt/client.h>

#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (!Client::isUrfkillRunning()){
        qDebug() << "URfkill Daemon not running!";

        qDebug() << "Try to start URfkill daemon...";
        Client::daemonLaunch();
        qDebug() << "Please re-launch program!";
        exit(1);
    }

    Client *client = new Client;
    Killswitch *ks = new Killswitch(URF_ENUM_TYPE_BLUETOOTH);
    Test *test = new Test;
    QObject::connect(ks, SIGNAL(triggerStateChanged()), test, SLOT(gotKillswitchChanged()));

    if (argv[1])
        client->setBlockIdx(1,true);
    else
        client->setBlockIdx(1,false);

    QList<QDBusObjectPath> devices = client->enumerateDevices();
    qDebug() << "Found " << devices.count() << " devices!!";
    foreach(QDBusObjectPath udi, devices) {
        Device *device = new Device(udi.path());
        QObject::connect(device, SIGNAL(triggerPropertyChanged()), test, SLOT(gotDeviceChanged()));
        qDebug() << "index: " << device->index() << " hard: " << device->hard() << " soft: " << device->soft();
        qDebug() << "Found the device:" << udi.path();
    }

    app.exec();
}
