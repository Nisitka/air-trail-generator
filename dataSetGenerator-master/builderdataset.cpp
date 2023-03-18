#include "builderdataset.h"

#include <QDebug>

builderDataSet::builderDataSet(Map* map_)
{
    ON = false;

    map = map_;
}

void builderDataSet::run(int countData,
                         const QString& dirNetImages_,
                         const QString& dirQFunData_,
                         int countRect_)
{
    ON = true;

    countRect = countRect_;
    currentRect = 0;

    //
    dirNetImages = dirNetImages_;
    dirQFunData = dirQFunData_;

    countBuildData = countData;
    numCurrentData = 0;

    buildNewMap();
}

void builderDataSet::mapReady()
{
    if (ON)
    {
        // случайный азимут конечной точки
        double aE = (double)((double)(rand()%1000) / 1000) * 360;
        setAngleE(aE);

        w = map->getWidth();
        l = map->getLength();

        // случайный квадрат прогноза
        setCoordRect(rand()%w, rand()%l);

        generateZD(rand()%w, rand()%l, map->getCountLayers());
    }
}

void builderDataSet::readyZD()
{
    if (ON)
    {
        generateQFunData(dirQFunData, numCurrentData*countRect + currentRect);
        generateNetImage();
    }
}

void builderDataSet::readyNetImage()
{
    saveNetImage(dirNetImages + "/netImg_" + QString::number(numCurrentData*countRect + currentRect) + ".jpg");
}

void builderDataSet::readyQFunData()
{
    if (ON)
    {
        currentRect++; // каждый квадрат имеет случайный азимут конечной точки
        if (currentRect != countRect)
        {
            // случайный квадрат прогноза
            setCoordRect(rand()%w, rand()%l);

            // случайный азимут конечной точки
            double aE = (double)((double)(rand()%1000) / 1000) * 360;
            setAngleE(aE);

            readyZD();
        }
        else
        {
            currentRect = 0;

            readyData();
            numCurrentData++;
            if (numCurrentData != countBuildData)
            {
                buildNewMap();
            }
            else
            {
                ON = false;
                finish();
            }
        }
    }
}
