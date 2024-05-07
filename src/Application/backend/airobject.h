#ifndef AIROBJECT_H
#define AIROBJECT_H

#include <QObject>
#include <backend/airlableobject.h>

class AirObject : public AirLableObject
{

public:
    explicit AirObject();

public:

    QString getNameAir();
    double getLongAir();
    double getWightAir();
    double getSpeedAir();
    QString getPhotoAir();
};

#endif // AIROBJECT_H
