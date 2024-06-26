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
    GeoColumn::setCountUnit(200);

    // Размеры дискретпространства
    lenghtUnit = 20;
    heightUnit = 20;

    //
    actionArea = new GeoArea(wArea, lArea); //Map;

    //
    map = nullptr;
    dirNameTmpMap = QApplication::applicationDirPath() +
            "\\blocks\\tmpMap.map";

    // Сразу узнаем размер дискреты в байт
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    GeoColumn column;
    ds << column;
    sizeColumn = data.size();

    //
    data.clear();
    ds << mapData;
    sizeOptData = data.size();
    data.clear();
}

int geoGenerator::lenghtBlock() const
{
    //return actionArea->getLenBlock();
    return lenghtUnit;
}

int geoGenerator::heightBlock() const
{
    //return actionArea->getHeightBlock();
    return heightUnit;
}

void geoGenerator::toZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    //
    if (inActionArea(idX, idY))
    {
        actionArea->getColumn(idX, idY)->toZD(idH);
    }
    else
    {
        /* Изменяется соответствующая ячейка данных */
    }
}

void geoGenerator::clearZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    //
    if (inActionArea(idX, idY))
    {
        actionArea->getColumn(idX, idY)->removeZD(idH);
    }
    else
    {
        /* Изменяется соответствующая ячейка данных */
    }
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

    delete map;
    QFile::remove(dirNameTmpMap);
    Wmap = W; Lmap = L; Hmap = H;
    int countColumns = Wmap * Lmap;

    //
    GeoColumn::setCountUnit(Hmap);
    actionArea->resize(wArea, lArea);

    // Сразу узнаем размер дискреты в байт
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    GeoColumn column;
    ds << column;
    sizeColumn = data.size();

    //
    map = new QFile(dirNameTmpMap);

    // Кол-во сегметов данных
    int curColumns = countColumns;
    int v = 20000;
    QVector <int> parts;
    while (curColumns > 0)
    {
        if (curColumns - v > 0)
        {
            parts.append(v);
        }
        else
        {
            parts.append(curColumns);
        }

            curColumns -= v;
        }

    map->open(QIODevice::ReadWrite);

    // Записываем служебную информацию
    QByteArray optData;
    QDataStream dStream(&optData, QIODevice::ReadWrite);
    mapData.W = Wmap; mapData.H = Hmap; mapData.L = Lmap;
    dStream << mapData;
    //qDebug() << optData.size();
    map->write(optData);

    // Записываем дискреты
    int countParts = parts.size();
    for (int nP=0; nP<countParts; nP++)
    {
        QByteArray data;
        QDataStream ds(&data, QIODevice::ReadWrite);

        for (int i=0; i<parts[nP]; i++)
        {
            ds << column;
        }
        map->write(data);
    }

    // Сообщаем об завершении инициализации карты
    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::openMap(const QString &dirMapFile)
{
    buildStart();

    if (map != nullptr) map->close();
    delete map;
    //QFile::remove(dirNameTmpMap);

    //
    map = new QFile(dirMapFile);
    map->open(QIODevice::ReadWrite);

    //
    map->seek(0); // Служеб. инф-я находится вначале
    QDataStream data(map->read(sizeOptData));
    data >> mapData;
    Wmap = mapData.W; Lmap = mapData.L; Hmap = mapData.H;
    //qDebug() << Wmap << Lmap << Hmap;

    //
    GeoColumn::setCountUnit(Hmap);
    actionArea->resize(wArea, lArea);
    //actionArea->build(wArea, lArea, Hmap);

    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::setPosActionArea(int idXo_, int idYo_)
{
    //qDebug() << "set position actions area!";

    //
    idXo = idXo_;
    idYo = idYo_;

    //
    lastX = idXo + wArea;
    lastY = idYo + lArea;

    //
    QDataStream inData(map);
    for (int x=0; x<wArea; x++)
    {
        map->seek(sizeOptData + (idColumn(idXo+x, idYo)*sizeColumn));
        for (int y=0; y<lArea; y++)
        {
            inData >> actionArea->getColumn(x, y);
        }
    }

    //qDebug() << "setPosArea!";
}

int geoGenerator::idColumn(int idX, int idY) const
{
    return Lmap*idX + idY;
}

//void geoGenerator::updateBlock(int idColumn, const geoBlock& b) const
//{
//    QByteArray data;
//    QDataStream ds(&data, QIODevice::WriteOnly);
//    ds << b;

//    map->seek(sizeOptData + (sizeColumn * idColumn));
//    map->write(data, sizeColumn);

//    data.clear();
//}

//geoBlock geoGenerator::readBlock(int idColumn) const
//{
//    map->seek(sizeOptData + (sizeColumn * idColumn));
//    QDataStream inData(map->read(sizeColumn));

//    geoBlock b;
//    inData >> b;

//    return b;
//}

int geoGenerator::absolute(int idX, int idY, Coords::units units) const
{
    int h = -1;

    h = actionArea->getHeight(idX-idXo, idY-idYo);
    switch (units) {
    case Coords::m:
        h *= heightUnit;
        break;
    case Coords::id:
        /* ... */
        break;
    }

    return h;
}

int geoGenerator::max(Coords::units u) const
{
    int h = -1;

    h = Hmap;
    switch (u) {
    case Coords::m:
        h *= heightUnit;
        break;
    case Coords::id:
        /* ... */
        break;
    }

    return h;
}

int geoGenerator::countVertZD(int idX, int idY) const
{
    if (inActionArea(idX, idY))
    {
        return actionArea->getColumn(idX-idXo, idY-idYo)->countUnitZD();
    }
    else
    {
        return 0; /// <-- Заглушка
    }

}

bool geoGenerator::isZD(int idX, int idY, int idH) const
{
    if (inActionArea(idX, idY))
    {
        return actionArea->getColumn(idX-idXo, idY-idYo)->isZD(idH);
    }
    else
    {
        return 0; /// <-- Заглушка
    }
}

Coords geoGenerator::getCoords(int idX, int idY) const
{
    int X = idX;
    int Y = idY;
    int H = actionArea->getHeight(idX-idXo, idY-idYo);

    return Coords(X, Y, H, lenghtUnit);
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
    actionArea->getColumn(idX, idY)->setHeight(height);

    /// !!!!!
    // Сразу обновляем его значения в файле-карте

}

void geoGenerator::removeEarth(int idX, int idY, int countLayer)
{
    int idHo = actionArea->getHeight(idX, idY);

    int height = idHo - countLayer;
    if (height < 0) height = 0;
    actionArea->getColumn(idX, idY)->setHeight(height);

    /// !!!!!
    // Сразу обновляем его значения в файле-карте


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

bool geoGenerator::P(double p)
{
    int V = rand()%1000;
    double mP = (double) V/1000;

    return mP > (1 - p);
}
