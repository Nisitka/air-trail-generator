#ifndef TRACERLIGHT_H
#define TRACERLIGHT_H

#include <QVector3D>

#include "ray.h"

#include "./GIS/heightmeter.h"

// Пускает лучи по карте
class TracerLight
{
public:
    TracerLight(HeightMeter* height);

    // Испустить луч (не врежится ли он)
    bool emitRay(Ray* ray,               // Какой луч
                 const QVector3D& pos,   // От куда
                 int distance,           // На какое расстояние
                 QPoint& idInterColumn); // Точка пересечения (если такова есть)

private:

    //
    HeightMeter* Height;
};

#endif // TRACERLIGHT_H
