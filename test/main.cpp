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

    Client *client = new Client;
    if (!client->urfkillRunning()){
        qDebug() << "URfkill Daemon not running!";
        exit(1);
    }

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