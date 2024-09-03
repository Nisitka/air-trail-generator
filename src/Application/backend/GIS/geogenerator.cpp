#include "geogenerator.h"

#include <QImage>
#include <QApplication>
#include <cmath>

#include <QDebug>

#include <QRgb>

geoGenerator::geoGenerator(int wArea_, int lArea_):
    wArea(wArea_), lArea(lArea_)
{
    isLocked = false;

    //
    actionArea = new GeoArea(wArea, lArea); //Map;

    dirNameTmpMap = QApplication::applicationDirPath() +
            "\\blocks\\tmpMap.map";

    //
    mapFile = new MapFile;
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

    //
    if (inActionArea(idX, idY))
    {
        actionArea->getColumn(idX-idXo, idY-idYo)->toZD(idH);
    }
    // Изменяется соответствующая ячейка данных
    setZD(idX, idY, idH, true);
}

void geoGenerator::clearZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    //
    if (inActionArea(idX, idY))
    {
        actionArea->getColumn(idX-idXo, idY-idYo)->removeZD(idH);
    }
    // Изменяется соответствующая ячейка данных
    setZD(idX, idY, idH, false);
}

void geoGenerator::setZD(int idX, int idY, int idH,
                         bool statZD) const
{
    mapFile->setZD(idX, idY, idH, statZD);
}

bool geoGenerator::inActionArea(int idX, int idY) const
{
    if (idX < idXo  || idY < idYo)  return false;
    if (idX > lastX || idY > lastY) return false;

    return true;
}

void geoGenerator::initMap(int W, int L, int H)
{
    buildStart();

    //
    actionArea->resize(wArea, lArea);

    //
    mapFile->init(dirNameTmpMap,
                  W, L, Hmap);

    // Сообщаем об завершении инициализации карты
    buildFinish(W, L, Hmap);
}

void geoGenerator::openMap(const QString &dirMapFile)
{
    buildStart();

    //
    mapFile->open(dirMapFile);

    actionArea->resize(wArea, lArea);

    int Wmap, Lmap;
    mapFile->getSize(Wmap, Lmap, Hmap);

    //
    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::setPosActionArea(int idXo_, int idYo_)
{
    qDebug() << "Set position actions area: " << idXo_ << idYo_;

    //
    idXo = idXo_;
    idYo = idYo_;

    //
    lastX = idXo + wArea - 1;
    lastY = idYo + lArea - 1;

    for (int x=0; x<wArea; x++)
    {
        for (int y=0; y<lArea; y++)
        {
            mapFile->getColumn(actionArea->getColumn(x, y),
                               idXo+x, idYo+y);
        }
    }

    qDebug() << "Ready position action area!" << idXo << idYo;
}

int geoGenerator::absolute(int idX, int idY, Coords::units units) const
{
    int h = -1;

    if (inActionArea(idX, idY))
        h = actionArea->getHeight(idX-idXo, idY-idYo);
    else
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
    if (inActionArea(idX, idY))
    {
        return actionArea->getColumn(idX-idXo, idY-idYo)->countUnitZD();
    }
    else
    {
        return 0; /// <-- Заглушка !!!!!!!!!!!!!!!!!!!
    }

}

bool geoGenerator::isZD(int idX, int idY, int idH) const
{
    bool statZD = false;

    //
    if (inActionArea(idX, idY))
        statZD = actionArea->getColumn(idX-idXo, idY-idYo)->isZD(idH);
    else
        statZD = mapFile->isZD(idX, idY, idH);

    return statZD;
}

Coords geoGenerator::getCoords(int idX, int idY) const
{
    int X = idX;
    int Y = idY;
    int H = actionArea->getHeight(idX-idXo, idY-idYo);

    /// !!!!
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
    actionArea->resize(wArea, lArea);

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

    setPosActionArea(0, 0);

    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::editEarth(int idX, int idY, int w, int l, int dH, int t)
{
    // Перевод в индексы активной зоны
    int Xo = idX - idXo;
    int Yo = idY - idYo;

    //
    int lastX = Xo + w;
    int lastY = Yo + l;

    //
    if (Xo < 0) Xo = 0;
    if (Yo < 0) Yo = 0;
    if (lastX >= wArea) lastX = wArea - 1;
    if (lastY >= lArea) lastY = lArea - 1;

    //
    void (geoGenerator::*f)(int, int, int);
    switch (t) {
    case up:
        f = &geoGenerator::dropEarth;
        break;
    case down:
        f = &geoGenerator::removeEarth;
        break;
    }

    // Изменяем высоту по дискретам-столбикам
    for (int x = Xo; x < lastX; x++)
    {
        for (int y = Yo; y < lastY; y++)
        {
            (this->*f)(x, y, dH);
        }
    }
}

void geoGenerator::dropEarth(int idX, int idY, int countLayer)
{
    int idHo = actionArea->getHeight(idX, idY);

    int maxH = Hmap-1;

    int height = idHo + countLayer;
    if (height > maxH) height = maxH;

     setHeight(idX, idY, height);
}

void geoGenerator::removeEarth(int idX, int idY, int countLayer)
{
    int idHo = actionArea->getHeight(idX, idY);

    int height = idHo - countLayer;
    if (height < 0) height = 0;

    setHeight(idX, idY, height);
}

void geoGenerator::setHeight(int idX, int idY, int height)
{
    //
    actionArea->getColumn(idX, idY)->setHeight(height);

    //
    mapFile->setHeight(idX, idY, height);
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

void geoGenerator::buildFlatMap(int W, int L, int H)
{
    buildStart();

    GeoColumn::setCountUnit(H);
    actionArea->resize(W, L);

    buildFinish(W, L, H);
}
