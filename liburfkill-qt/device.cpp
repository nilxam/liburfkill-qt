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
