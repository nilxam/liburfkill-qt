#include <QtDBus>
#include <QDebug>
#include <QDBusReply>

#include "client.h"
#include "killswitch.h"
#include "device.h"
#include "urfkill.h"
#include "enum.h"

bool Client::isUrfkillRunning()
{
    QDBusConnection conn = QDBusConnection::systemBus();
    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug() << "Cannot connect to the D-Bus system bus.";

        return false;
    }   

    QDBusInterface checkIface(DBUS_SERVICE, DBUS_OBJPATH, DBUS_INTERFACE, conn, this);
    if (!checkIface.isValid()) {
        qDebug() << "Can not create DBus interface!";
        qDebug() << QDBusConnection::systemBus().lastError().message();

        return false;
    }

    QDBusReply<bool> rep = checkIface.call("NameHasOwner", "org.freedesktop.URfkill");

    return rep.value();
}

void Client::gotDeviceAdded(QString device)
{
    qDebug() << "device " << device << " added!";
    if (!m_devicesList.isEmpty())
        m_devicesList.clear();

    refreshDevicesData();
}

void Client::gotDeviceChanged(QString device)
{
    qDebug() << "device " << device << " changed!";
    if (!m_devicesList.isEmpty())
        m_devicesList.clear();

    refreshDevicesData();
}

void Client::gotDeviceRemoved(QString device)
{
    qDebug() << "device " << device << " removed!";
    if (!m_devicesList.isEmpty())
        m_devicesList.clear();

    refreshDevicesData();
}

bool Client::setBlock(uint type, bool block)
{
    QDBusReply<bool> reply = clientIface->call("Block", type, block);

    if (reply.isValid()) {
        return true;    
    } else {
        qDebug() << QString("D-Bus error: Call Block() failed!");
        return false;
    }
}

bool Client::setBlockIdx(uint index, bool block)
{
    QDBusReply<bool> reply = clientIface->call("BlockIdx", index, block);

    if (reply.isValid()) {
        return true;    
    } else {
        qDebug() << QString("D-Bus error: Call BlockIdx() failed!");
        return false;
    }
}

void Client::refreshDevicesData()
{
    QDBusReply<QList<QDBusObjectPath> > reply = clientIface->call("EnumerateDevices");

    if (reply.isValid()) {
        m_devicesList = reply.value();
    } else {
        qDebug() << QString("D-Bus error: Call EnumerateDevices() failed!");
    }
}

Client::Client() 
    : m_keyControl(false), m_daemonVersion(""), m_devicesList(), m_urfkillRunning(true)
{
    if (!isUrfkillRunning()){
        m_urfkillRunning = false;
        return;
    }

    QDBusConnection conn = QDBusConnection::systemBus();
    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug() << "Cannot connect to the D-Bus system bus.";

        return;
    }   

    clientIface = new QDBusInterface(URFKILL_SERVICE, URFKILL_OBJPATH, URFKILL_INTERFACE, conn, this);
    if (!clientIface->isValid()) {
        qDebug() << "Can not create DBus interface!";
        qDebug() << QDBusConnection::systemBus().lastError().message();

        return;
    }

    m_keyControl = clientIface->property("KeyControl").toBool();
    m_daemonVersion = clientIface->property("DaemonVersion").toString();

    refreshDevicesData();

    connect(clientIface, SIGNAL(DeviceAdded(QString)), this, SIGNAL(deviceAdded(QString)));
    connect(clientIface, SIGNAL(DeviceChanged(QString)), this, SIGNAL(deviceChanged(QString)));
    connect(clientIface, SIGNAL(DeviceRemoved(QString)), this, SIGNAL(deviceRemoved(QString)));
    connect(clientIface, SIGNAL(UrfkeyPressed(int)), this, SIGNAL(urfkeyPressed(int)));

    connect(clientIface, SIGNAL(DeviceAdded(QString)), this, SLOT(gotDeviceAdded(QString)));
    connect(clientIface, SIGNAL(DeviceChanged(QString)), this, SLOT(gotDeviceChanged(QString)));
    connect(clientIface, SIGNAL(DeviceRemoved(QString)), this, SLOT(gotDeviceRemoved(QString)));
}

Client::~Client()
{
}

QList<QDBusObjectPath> Client::enumerateDevices() const
{
    return m_devicesList;
}

bool Client::keyControl() const
{
    return m_keyControl;
}

QString Client::daemonVersion() const
{
    return m_daemonVersion;
}

bool Client::urfkillRunning() const
{
    return m_urfkillRunning;
}
