#include "tracerlight.h"

TracerLight::TracerLight(HeightMeter* height, RZInformer* rZone):
    Height(height), radioZone(rZone)
{

}

void TracerLight::emitRay(Ray *ray, const QVector3D &pos, QVector <QVector3D>& idBlocks)
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
    int countDelta = way.size(); // кол-во дискрет одного луча
    for (int k=1; k<countDelta; k++)
    {   // в пути луча содержатся относительные индексы
        int* l = way[k];

        // id очередной дискреты
        idX = curX + l[Ray::X];
        idY = curY + l[Ray::Y];
        idH = curZ + l[Ray::Z];

        // Если столбец этой дискреты выше луча, то
        if (Height->absolute(idX, idY, Coords::id) >= idH)
        {
            // луч столкнулся с рельефом
            return;
        }
        else
        {
            // Если он еще не в ЗО
            if (!radioZone->isZD(idX, idY, idH))
                idBlocks.append(QVector3D(idX, idY, idH));
        }
    }

    return;
}
