#include "geogenerator.h"

#include <QImage>
#include <QApplication>
#include <cmath>

#include <QDebug>

#include <QRgb>

geoGenerator::geoGenerator(mapManager* manMap):
    manMap(manMap)
{
    isLocked = false;
}

void geoGenerator::getSizeMap(int &W, int &L, int &H) const
{
    manMap->getCurrentMap()->getSize(W, L, H);
}

int geoGenerator::lenghtBlock() const
{
    return manMap->getCurrentMap()->lenghtUnit();
}

int geoGenerator::heightBlock() const
{
    return manMap->getCurrentMap()->heightUnit();
}

int geoGenerator::absolute(int idX, int idY, Coords::units units) const
{
    int h = -1;

    const MapFile* map = manMap->getCurrentMap();

    //
    h = map->getHeight(idX, idY);

    switch (units) {
    case Coords::m:
        h *= map->heightUnit();
        break;
    case Coords::id:
        /* ... */
        break;
    }

    return h;
}

int geoGenerator::max(Coords::units u) const
{
    return manMap->getCurrentMap()->getMaxHeight(u);
}

Coords geoGenerator::getCoords(int idX, int idY) const
{
    const MapFile* map = manMap->getCurrentMap();

    int X = idX;
    int Y = idY;
    int H = map->getHeight(idX, idY);

    /// !!!!!!!!!!!
    int lUnit = map->lenghtUnit();

    return Coords(X, Y, H, lUnit);
}

void geoGenerator::loadTerrain(const QString& dirNameFile)
{
    /* ... */
}

void geoGenerator::editEarth(int idX, int idY, int w, int l, int dH, int t)
{
    switch (t) {
    case up:

        break;
    case down:
        dH *= -1;
        break;
    }

    manMap->getCurrentMap()->editHeightMatrix(idX, idY, w, l, dH);
}
