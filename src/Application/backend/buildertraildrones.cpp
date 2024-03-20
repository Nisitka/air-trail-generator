#include "buildertraildrones.h"


#include <QDebug>

#include <cmath>
#include "ray.h"

builderTrailDrones::builderTrailDrones(Map* map): map(map)
{ 
    countHorPart = 360;
    countVerRay  = 180;
    longRay = 1000.0;

    //qDebug() << getDistance(0, 0, 3, 4) << "distance";

    buildZD();

    trail = nullptr;

    startPredictTrail(5, 5, 390, 190);
}

void builderTrailDrones::startPredictTrail(int idXa, int idYa, int idXb, int idYb)
{
    Wmap = map->getWidth();
    Lmap = map->getLength();
    Hmap = map->getCountLayers();

    //
    delete trail;
    trail = new Trail;

    Xb = idXb;
    Yb = idYb;

    curX = idXa;
    curY = idYa;
    curZ = map->getHeight(curX, curY) + 1;
    trail->addPoint(curX, curY, curZ);
    nextPointTrail(curX, curY, curZ);

    //double l = map->getLenBlock();

    while (getDistance(curX, curY, idXb, idYb) > 10) {
        predictFromRect();
        trail->addPoint(curX, curY, curZ);

        //qDebug() << curX << curY << curZ;
        nextPointTrail(curX, curY, curZ);
    }

    // Последняя точка всегда точка задачи
    curX = Xb;
    curY = Yb;
    curZ = map->getHeight(Xb, Yb);
    trail->addPoint(curX, curY, curZ);
    nextPointTrail(curX, curY, curZ);
}

void builderTrailDrones::predictFromRect()
{
    // Лучшая след. точка в зоне прогноза
    int Xp = curX;
    int Yp = curY;
    int Zp = curZ;

    // Лучшее оставшееся расстояние до финиша
    double minD = getDistance(Xp, Yp, Xb, Yb);

    // По вертикальным сегментам
    for (int i=0; i<countHorPart; i++)
    {
        for (int j=0; j<countVerRay; j++)
        {
            QVector <int*> way = ZD[i]->at(j)->getWay();
            int idX;
            int idY;
            int idH;

            // Полет луча
            int countDelta = way.size(); // кол-во дискрет одного луча
            int k=1;
            for (; k<countDelta; k++)
            {   // в пути луча содержатся относительные индексы
                int* l = way[k];

                idX = curX + l[Ray::X];
                idY = curY + l[Ray::Y];
                idH = curZ + l[Ray::Z];

                // если луч вышел за карту
                if (idY >= Lmap) {

                    break;
                }
                if (idY < 0) {

                    break;
                }

                if (idX >= Wmap) {

                    break;
                }
                if (idX < 0) {

                    break;
                }

                if (idH >= Hmap) {

                    break;
                }
                if (idH < 0) {

                    break;
                }

                // блок, в котором пролетает луч
                geoBlock* block = map->getBlock(idX, idY, idH);

                // Если блок на пути, является землей, то
                if (block->isEarth())
                {
                    // луч столкнулся с рельефом

                    break;
                }
                else
                {   // если блок в ЗО
                    if (block->isZD())
                    {
                        break;
                    }
                }
            }

            // Если луч прогноза дошел до конца
            if (k == countDelta)
            {
                double D = getDistance(idX, idY, Xb, Yb);
                //
                if (D < minD)
                {
                    minD = D;
                    Xp = idX;
                    Yp = idY;
                    Zp = idH;
                }
            }
        }
    }

    curX = Xp;
    curY = Yp;
    curZ = Zp;
}

double builderTrailDrones::getDistance(int Xa, int Ya, int Xb, int Yb)
{
    return sqrt((double)pow(Xa-Xb, 2) + pow(Ya-Yb, 2));
}

void builderTrailDrones::buildZD()
{
    double dE = (double) (2 * Pi) / countHorPart;
    double angleE;

    double dB = (double) Pi / countVerRay;
    double angleB;

    for (int i=0; i<countHorPart; i++)
    {
        ZD.append(new QVector<Ray*>);
        angleE = (double) i * dE; // азимут (радианы)

        for (int j=0; j<countVerRay; j++)
        {
            angleB = double(Pi / 2.0) - double(j * dB);

            //qDebug() << angleB << angleE;
            ZD.last()->append(new Ray(longRay, angleB, angleE));
        }
    }
}
