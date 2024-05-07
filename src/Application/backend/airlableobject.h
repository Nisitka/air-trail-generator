#ifndef AIRLABLEOBJECT_H
#define AIRLABLEOBJECT_H

#include <QObject>

class AirLableObject
{
public:
    AirLableObject();

    void setNameAir(QString);
    void setLongAir(double);
    void setWightAir(double);
    void setSpeedAir(double);
    void setPhotoAir(QString);

    QString nameAir;
    double longsAir;
    double wightAir;
    double speedAir;
    QString photoAir;
};

#endif // AIRLABLEOBJECT_H
