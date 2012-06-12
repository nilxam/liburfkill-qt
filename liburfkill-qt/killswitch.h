#ifndef __KILLSWITCH_H
#define __KILLSWITCH_H

#include <QVariant>
#include <QString>
#include <QDBusInterface>

#include "enum.h"

class Killswitch : public QObject
{
    Q_OBJECT
public:
    Killswitch(UrfEnumType type);
    ~Killswitch();

    int state() const;
Q_SIGNALS:
    void triggerStateChanged();
public Q_SLOTS:
    void stateChanged(int state);
protected:
    QDBusInterface *killswitchIface;
private:
    int m_state;

    void refreshState();
    QString getObjectPath(UrfEnumType type);
};

#endif
