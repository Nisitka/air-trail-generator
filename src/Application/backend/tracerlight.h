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
    void emitRay(Ray* ray,             // Какой луч
                 const QVector3D& pos, // От куда
                 QVector <QVector3D>& idBlocks); // Помещаем id дискрет

private:

    //
    BlockInformer* blocks;
};

#endif // TRACERLIGHT_H
