#include "gis.h"

#include <QDebug>

GIS::GIS(mapManager* mapsInfo): GISInformer(),
    Enabled(true)
{
    // Отвечает за работу с рельефом карты
    geoBuilder = new geoGenerator(mapsInfo);
}

HeightMeter* GIS::getHeightMeter() const
{
    return geoBuilder;
}

GISInformer* GIS::Informer() /* const */
{
    return this;
}

int GIS::getH(int idX, int idY, Coords::units u) const
{
    return geoBuilder->absolute(idX, idY, u);
}

Coords GIS::getCoords(int idX, int idY) const
{
    if (Enabled)
        return geoBuilder->getCoords(idX, idY);
    else
        return Coords();
}

void GIS::loadTerrain(const QString &dirNameFile)
{
    geoBuilder->loadTerrain(dirNameFile);
}

void GIS::upEarth(int idX, int idY, int R)
{
    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    geoBuilder->editEarth(idXo, idYo, R, R, 1);

    changedMap(idXo, idYo, R, R);
}

void GIS::downEarth(int idX, int idY, int R)
{
    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    geoBuilder->editEarth(idXo, idYo, R, R, 3, geoGenerator::down);

    changedMap(idXo, idYo, R, R);
}
