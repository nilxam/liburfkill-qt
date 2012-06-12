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
