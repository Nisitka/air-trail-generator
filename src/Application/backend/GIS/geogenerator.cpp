#include "geogenerator.h"

#include <QImage>
#include <QApplication>
#include <cmath>

#include <QDebug>

#include <QRgb>

geoGenerator::geoGenerator()
{
    isLocked = false;

    //
    mapFile = new MapFile;
}

void geoGenerator::getSizeMap(int &W, int &L, int &H) const
{
    mapFile->getSize(W, L, H);
}

int geoGenerator::lenghtBlock() const
{
    return mapFile->lenghtUnit();
}

int geoGenerator::heightBlock() const
{
    return mapFile->heightUnit();
}

void geoGenerator::initMap(const MapData DataMap,
                           const QString& dirName)
{
    buildStart();

    Wmap = DataMap.W;
    Lmap = DataMap.L;
    Hmap = DataMap.H;

    //
    mapFile->init(dirName,
                  Wmap, Lmap, Hmap);

    // Сообщаем об завершении инициализации карты
    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::openMap(const QString &dirMapFile)
{
    buildStart();

    //
    mapFile->open(dirMapFile);

    int Wmap, Lmap;
    mapFile->getSize(Wmap, Lmap, Hmap);

    //
    buildFinish(Wmap, Lmap, Hmap);
}

int geoGenerator::absolute(int idX, int idY, Coords::units units) const
{
    int h = -1;

    //
    h = mapFile->getHeight(idX, idY);

    switch (units) {
    case Coords::m:
        h *= mapFile->heightUnit();
        break;
    case Coords::id:
        /* ... */
        break;
    }

    return h;
}

int geoGenerator::max(Coords::units u) const
{
    return mapFile->getMaxHeight(u);
}

Coords geoGenerator::getCoords(int idX, int idY) const
{
    int X = idX;
    int Y = idY;
    int H = mapFile->getHeight(idX, idY);

    /// !!!!!!!!!!!
    int lUnit = mapFile->lenghtUnit();

    return Coords(X, Y, H, lUnit);
}

void geoGenerator::loadTerrain(const QString& dirNameFile)
{
    buildStart();

    /* ... */

    buildFinish(Wmap, Lmap, Hmap);
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

    mapFile->editHeightMatrix(idX, idY, w, l, dH);
}

void geoGenerator::updateHeights(int idX, int idY, int W, int L)
{
    int idLastX = idX + W;
    int idLastY = idY + L;

    qDebug() << "update heights!";

    for (int X=idX; X<=idLastX; X++)
    {
        for (int Y=idY; Y<=idLastY; Y++)
        {
            // Присваеваем каждому(ой) столбцу(дискрете) новую высоту

        }
    }
}
