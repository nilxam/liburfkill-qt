#include <QDebug>

#include "test.h"

Test::Test()
{

}

void Test::gotDeviceChanged()
{
    qDebug() << "device property changed!";
}

void Test::gotKillswitchChanged()
{
    qDebug() << "killswitch state changed!";
}

