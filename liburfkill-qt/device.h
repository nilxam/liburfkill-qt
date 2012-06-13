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

#ifndef __DEVICE_H
#define __DEVICE_H

#include <QVariant>
#include <QString>
#include <QDBusInterface>

#include "enum.h"

class Device : public QObject
{
    Q_OBJECT
public:
    Device(const QString &devicePath);
    ~Device();

    bool platform() const;
    bool hard() const;
    bool soft() const;
    QString name() const;
    uint type() const;
    uint index() const;
Q_SIGNALS:
    void triggerPropertyChanged();
public Q_SLOTS:
    void propertyChanged();
protected:
    QDBusInterface *deviceIface;
private:
    bool m_platform;
    bool m_hard;
    bool m_soft;
    QString m_name;
    uint m_type;
    uint m_index;

    void refreshDeviceProperties();
};

#endif
