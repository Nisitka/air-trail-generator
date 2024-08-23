#ifndef TRACERLIGHT_H
#define TRACERLIGHT_H

#include <QVector3D>

#include "ray.h"

#include "./GIS/heightmeter.h"
#include "./GIS/rzinformer.h"

// Пускает лучи по карте
class TracerLight
{
public:
    TracerLight(HeightMeter* height, RZInformer* radioZone);

    // Испустить луч
    void emitRay(Ray* ray,             // Какой луч
                 const QVector3D& pos, // От куда
                 QList <QVector3D>& idBlocks); // Помещаем id дискрет

private:

    //
    HeightMeter* Height;

    //
    RZInformer* radioZone;
};

#endif // TRACERLIGHT_H
