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

void geoGenerator::toZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    // Изменяется соответствующая ячейка данных
    mapFile->setZD(idX, idY, idH, true);
}

void geoGenerator::clearZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    // Изменяется соответствующая ячейка данных
    mapFile->setZD(idX, idY, idH, false);
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

int geoGenerator::countVertZD(int idX, int idY) const
{
    //return actionArea->getColumn(idX-idXo, idY-idYo)->countUnitZD();

    return 0; /// <-- Заглушка !!!!!!!!!!!!!!!!!!!
}

bool geoGenerator::isZD(int idX, int idY, int idH) const
{
    return mapFile->isZD(idX, idY, idH);
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

    // Источник данных об рельефе
    QImage geoData(dirNameFile);

    // Полные размеры карты
    int Wmap = geoData.width();
    int Lmap = geoData.height();
    int Hmap = 256;

    // Размер активной зоны
    GeoColumn::setCountUnit(Hmap);

    int h;
    QColor color;
    for (int x=0; x<Wmap; x++)
    {
        for (int y=0; y<Lmap; y++)
        {
            color = geoData.pixelColor(x, y);
            h = Hmap * ((double) ((double)color.blueF() +
                                          color.redF()  +
                                          color.greenF()) / 1.0);
            //heights.last()[y] = h;
        }
    }

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
