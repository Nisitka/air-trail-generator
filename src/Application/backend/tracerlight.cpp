#include "tracerlight.h"

TracerLight::TracerLight(BlockInformer* blocks):
    blocks(blocks)
{

}

QVector <QVector3D> TracerLight::emitRay(Ray *ray, const QVector3D &pos)
{
    QVector <int*> way = ray->getWay();
    int idX;
    int idY;
    int idH;

    //
    int curX = pos.x();
    int curY = pos.y();
    int curZ = pos.z();

    // Полет луча
    QVector <QVector3D> idBlocks;
    int countDelta = way.size(); // кол-во дискрет одного луча
    for (int k=1; k<countDelta; k++)
    {   // в пути луча содержатся относительные индексы
        int* l = way[k];

        // id очередной дискреты
        idX = curX + l[Ray::X];
        idY = curY + l[Ray::Y];
        idH = curZ + l[Ray::Z];

        // Дискрета, в которой пролетает луч
        const geoBlock& block = blocks->block(idX, idY, idH);

        // Если блок на пути, является землей, то
        if (block.isEarth())
        {
            // луч столкнулся с рельефом
            return idBlocks;
        }
        else
        {
            idBlocks.append(QVector3D(idX, idY, idH));
        }
    }

    return idBlocks;
}
