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
