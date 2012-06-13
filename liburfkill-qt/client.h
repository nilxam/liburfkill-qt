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

#ifndef __CLIENT_H
#define __CLIENT_H

#include <QDBusInterface>
#include <QDBusObjectPath>
#include <QString>
#include <QList>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();

    bool setBlock(uint type, bool block);
    bool setBlockIdx(uint index, bool block);
    static bool isUrfkillRunning();
    static void daemonLaunch();

    QList<QDBusObjectPath> enumerateDevices() const;
    bool keyControl() const;
    QString daemonVersion() const;
    bool urfkillRunning() const;
Q_SIGNALS:
    void deviceAdded(QString device);
    void deviceChanged(QString device);
    void deviceRemoved(QString device);
    void urfkeyPressed(int key);
protected:
    QDBusInterface *clientIface;
private:
    void refreshDevicesData();

    bool m_keyControl;
    QString m_daemonVersion;
    QList<QDBusObjectPath> m_devicesList;
private slots:
    void gotDeviceAdded(QString device);
    void gotDeviceChanged(QString device);
    void gotDeviceRemoved(QString device);
};

#endif /* __CLIENT_H */
