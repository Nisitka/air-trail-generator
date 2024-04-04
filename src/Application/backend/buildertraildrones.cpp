#include "buildertraildrones.h"


#include <QDebug>

#include <cmath>
#include "ray.h"

builderTrailDrones::builderTrailDrones(Map* map): map(map)
{ 
    countHorPart = 360;
    countVerRay  = 180;
    longRay = 1000.0;

    isEditOptPred = true;
    setOptPredict();

    trail = nullptr;

    startPredictTrail(5, 5, 390, 190);
}

void builderTrailDrones::setRpredict(int countDiscretes)
{
    longRay = (double)countDiscretes * map->getLenBlock();

    isEditOptPred = true;
}

void builderTrailDrones::setOptPredict()
{
    startSetOptPredict();

    buildZD();

    isEditOptPred = false;
    finishSetOptPredict();
}

void builderTrailDrones::runPredictRect(int idXa, int idYa, int idZa, int idXb, int idYb, int idZb)
{
    // Обновляем настройки торлько если они изменились
    if (isEditOptPred)
        setOptPredict();

    int predX, predY, predZ;
    predictFromRect(idXa, idYa, idZa, idXb, idYb, idZb, predX, predY, predZ);

    finishPredOnlyRect(predX, predY, predZ);
}

void builderTrailDrones::startPredictTrail(int idXa, int idYa, int idXb, int idYb)
{
    if (isEditOptPred)
        setOptPredict();

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
        predictFromRect(curX, curY, curZ, Xb, Yb, -1, curX, curY, curZ);
        trail->addPoint(curX, curY, curZ);

        nextPointTrail(curX, curY, curZ);
    }

    // Последняя точка всегда точка задачи
    curX = Xb;
    curY = Yb;
    curZ = map->getHeight(Xb, Yb);
    trail->addPoint(curX, curY, curZ);
    nextPointTrail(curX, curY, curZ);
}

void builderTrailDrones::predictFromRect(int  idXa,   int idYa,    int idZa,
                                         int  idXb,   int idYb,    int idZb,
                                         int& idXres, int& idYres, int& idZres)
{
    // Лучшая след. точка в зоне прогноза
    int Xp = idXa;
    int Yp = idYa;
    int Zp = idZa;

    // Лучшее оставшееся расстояние до финиша
    double minD = getDistance(Xp, Yp, idXb, idYb);

    // По вертикальным сегментам
    double D;
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
                D = getDistance(idX, idY, Xb, Yb);
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

    idXres = Xp;
    idYres = Yp;
    idZres = Zp;
}

double builderTrailDrones::getDistance(int Xa, int Ya, int Xb, int Yb)
{
    return sqrt((double)pow(Xa-Xb, 2) + pow(Ya-Yb, 2));
}

void builderTrailDrones::buildZD()
{   
    int numOper = 0;
    int dPart;

    if (ZD.size() > 0)
    {
        int cDelZD = ZD.size();
        dPart = countHorPart + cDelZD;

        for (int i=0; i<cDelZD; i++)
        {
            int cVerRay = ZD.at(i)->size();
            for (int j=0; j<cVerRay; j++)
            {
                delete ZD.at(i)->at(j);
            }

            ZD[i]->clear();
            delete ZD[i];

            numOper++;
            procSetOptPred((double)numOper/dPart * 100);
        }
        ZD.clear();
    }
    else
    {
        dPart = countHorPart;
    }

    /*       */
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

        numOper++;
        procSetOptPred((double)numOper/dPart * 100);
    }
}
