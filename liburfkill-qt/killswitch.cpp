#include <QtDBus>
#include <QDebug>

#include "urfkill.h"
#include "killswitch.h"

QString Killswitch::getObjectPath(UrfEnumType type)
{
    switch (type) {
        case URF_ENUM_TYPE_WLAN:
            return QString(URFKILL_OBJPATH"/WLAN");
        case URF_ENUM_TYPE_BLUETOOTH:
            return QString(URFKILL_OBJPATH"/BLUETOOTH");
        case URF_ENUM_TYPE_UWB:
            return QString(URFKILL_OBJPATH"/UWB");
        case URF_ENUM_TYPE_WIMAX:
            return QString(URFKILL_OBJPATH"/WIMAX");
        case URF_ENUM_TYPE_WWAN:
            return QString(URFKILL_OBJPATH"/WWAN");
        case URF_ENUM_TYPE_GPS:
            return QString(URFKILL_OBJPATH"/GPS");
        case URF_ENUM_TYPE_FM:
            return QString(URFKILL_OBJPATH"/FM");
        default:
            return NULL;
    }
}

void Killswitch::refreshState()
{
    m_state = killswitchIface->property("state").toInt();
}

void Killswitch::stateChanged(int state)
{
    //qDebug() << "state changed!";
    refreshState();
    emit triggerStateChanged();
}

Killswitch::Killswitch(UrfEnumType type)
{
    QDBusConnection conn = QDBusConnection::systemBus();
    if (!QDBusConnection::systemBus().isConnected()) {
        qDebug() << "Cannot connect to the D-Bus system bus.";

        return;
    }

    QString objPath = getObjectPath(type);
    killswitchIface = new QDBusInterface(URFKILL_SERVICE, objPath, URFKILL_KILLSWITCH_INTERFACE, conn, this);
    if (!killswitchIface->isValid()) {
        qDebug() << "Can not create DBus interface!";
        qDebug() << QDBusConnection::systemBus().lastError().message();

        return;
    }

    refreshState();

    connect(killswitchIface, SIGNAL(StateChanged(int)), this, SLOT(stateChanged(int)));
}

Killswitch::~Killswitch()
{
}

int Killswitch::state() const
{
    return m_state;
}
