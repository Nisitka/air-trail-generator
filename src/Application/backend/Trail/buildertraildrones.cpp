#include "buildertraildrones.h"


#include <QDebug>

#include <cmath>
#include "../ray.h"

builderTrailDrones::builderTrailDrones(TracerLight* tracer): Tracer(tracer)
{ 
    countHorPart = 360;
    countVerRay  = 180;
    longRay = 1000.0;

    isEditOptPred = true;
    setOptPredict();

    trail = nullptr;
}

void builderTrailDrones::setRpredict(int countDiscretes)
{
    /// !!!!!
    longRay = (double)countDiscretes * 20.0; ///map->getLenBlock();

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
