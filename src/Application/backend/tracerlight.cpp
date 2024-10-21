#include "tracerlight.h"

#include <QDebug>

TracerLight::TracerLight(HeightMeter* height):
    Height(height)
{

}

bool TracerLight::emitRay(Ray *ray,
                          const QVector3D &pos,
                          int distance,
                          QPoint &idInterColumn)
{
    bool intersection = false;


    return intersection;
}
