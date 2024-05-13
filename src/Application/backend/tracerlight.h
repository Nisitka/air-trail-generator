#ifndef TRACERLIGHT_H
#define TRACERLIGHT_H

#include <QVector3D>

#include "ray.h"
#include "./GIS/blockinformer.h"

// Пускает лучи по карте
class TracerLight
{
public:
    TracerLight(BlockInformer* blocks);

    // Испустить луч
    QVector <QVector3D> emitRay(Ray* ray,              // Какой луч
                                const QVector3D& pos); // От куда

private:

    //
    BlockInformer* blocks;
};

#endif // TRACERLIGHT_H
