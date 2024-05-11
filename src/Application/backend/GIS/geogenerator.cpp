#include "geogenerator.h"

#include <QImage>
#include <QApplication>
#include <cmath>

#include <QDebug>

#include <QRgb>

geoGenerator::geoGenerator(int wArea_, int lArea_):
    wArea(wArea_), lArea(lArea_)
{
    idXo = 0;
    idYo = 0;

    Hmap = 256;

    //
    actionArea = new Map;
    actionArea->build(wArea, lArea, Hmap);

    //
    map = nullptr;
    dirNameTmpMap = QApplication::applicationDirPath() +
            "\\blocks\\tmpMap.map";

    // Сразу узнаем размер дискреты в байт
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    geoBlock b;
    ds << b;
    sizeBlock = data.size();
    //qDebug() << sizeBlock << "SIZE block";

    //initMap(1000, 1000, 256);
}

void geoGenerator::initMap(int W, int L, int H)
{
    delete map;
    QFile::remove(dirNameTmpMap);
    Wmap = W; Lmap = L; Hmap = H;
    int countBlocks = Wmap * Lmap * Hmap;

    map = new QFile(dirNameTmpMap);
    //
    geoBlock block;

    // Кол-во сегметов данных
    int curBlocks = countBlocks;
    int v = 20000;
    QVector <int> parts;
    while (curBlocks > 0)
    {
        if (curBlocks - v > 0)
        {
            parts.append(v);
        }
        else
        {
            parts.append(curBlocks);
        }

            curBlocks -= v;
        }

    map->open(QIODevice::ReadWrite);

    int countParts = parts.size();
    for (int nP=0; nP<countParts; nP++)
    {
        QByteArray data;
        QDataStream ds(&data, QIODevice::ReadWrite);

        for (int i=0; i<parts[nP]; i++)
        {
                ds << block;
        }
            map->write(data);
    }
}

void geoGenerator::openMap(const QString &dirMapFile)
{
    buildStart();

    if (map != nullptr) map->close();
    delete map;
    QFile::remove(dirNameTmpMap);

    Wmap = 1000; Lmap = 1000; Hmap = 256;

    map = new QFile(dirMapFile);
    map->open(QIODevice::ReadWrite);

    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::setPosActionArea(int idXo_, int idYo_)
{
    idXo = idXo_;
    idYo = idYo_;

    qDebug() << idXo << idYo;

    //
    actionArea->clear();

    for (int x=0; x<wArea; x++)
    {
        for (int y=0; y<lArea; y++)
        {
            for (int h=0; h<Hmap; h++)
            {
                actionArea->getBlock(x,y,h)->setValues(readBlock(idBlock(idXo+x,
                                                                         idYo+y,
                                                                         h)));
            }
        }
    }
    //qDebug() << "setPosArea!";

//    int h;
//    for (int x=0; x<wArea; x++)
//    {
//        for (int y=0; y<lArea; y++)
//        {
//            h = heights[idXo + x][idYo + y];
//            actionArea->setH(x, y, h);
//        }
//    }
}

int geoGenerator::idBlock(int idX, int idY, int idH)
{
    return Wmap*Lmap*idH + Lmap*idX + idY;
}

void geoGenerator::updateBlock(int idBlock, const geoBlock& b)
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << b;

    map->seek(sizeBlock * idBlock);
    map->write(data, sizeBlock);
}

geoBlock geoGenerator::readBlock(int idBlock)
{
    map->seek(sizeBlock * idBlock);
    QDataStream inData(map->read(sizeBlock));

    geoBlock b;
    inData >> b;

    return b;
}

int geoGenerator::absolute(int idX, int idY, Map::units u) const
{
    switch (u) {
    case Map::m:


        break;
    case Map::id:


        break;
    }
}

int geoGenerator::getH(int idX, int idY, int units) const
{
    return actionArea->getHeight(idX, idY, units);
}

Coords geoGenerator::getCoords(int idX, int idY) const
{
    int X = /*idXo + */idX;
    int Y = /*idYo + */idY;
    int H = getH(idX, idY, Map::id);

    return Coords(X, Y, H, actionArea->getLenBlock());
}

Map* geoGenerator::getMap() const
{
    return actionArea;
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
    actionArea->resize(wArea, lArea, Hmap);

    //
    heights.clear();

    int h;
    QColor color;
    for (int x=0; x<Wmap; x++)
    {
        heights.append(QVector<int>(Lmap));
        for (int y=0; y<Lmap; y++)
        {
            color = geoData.pixelColor(x, y);
            h = Hmap * ((double) ((double)color.blueF() +
                                          color.redF()  +
                                          color.greenF()) / 1.0);
            heights.last()[y] = h;
        }
    }

    setPosActionArea(0, 0);

    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::editEarth(int idX, int idY, int w, int l, int dH, int t)
{
    actionArea->editEarth(idX-idXo, idY-idYo, w, l, dH, t);

    //
    updateHeights(idX, idY, w, l);
}

void geoGenerator::updateHeights(int idX, int idY, int W, int L)
{
    int idLastX = idX + W;
    int idLastY = idY + L;

    for (int X=idX; X<=idLastX; X++)
    {
        for (int Y=idY; Y<=idLastY; Y++)
        {
//            heights[X][Y] =
//                actionArea->getHeight(idXo + X, idYo + Y);

            //
            for (int H=0; H<Hmap; H++)
            {
                updateBlock(idBlock(X, Y, H),
                            *actionArea->getBlock(X-idXo,Y-idYo,H));
            }
        }
    }
}

void geoGenerator::buildFlatMap(int W, int L, int H)
{
    buildStart();

    actionArea->resize(W, L, H);

    buildFinish(W, L, H);
}

void geoGenerator::buildRandomMap(double setBlockP, int countEpochs,
                                  int W, int L, int H,
                                  double lenBlock)
{
    buildStart();

    // устанавливаем длину ребра блока
    actionArea->setLenBlock(lenBlock);

    // берем актуальный размер карты
    int Wmap;
    int Lmap;
    int Hmap;
    actionArea->getSize(Wmap, Lmap, Hmap);

    // если размеры необходимо изменить
    if (Wmap != W || Lmap != L || Hmap != H)
    {
        // прежде чем генерировать рельеф, создадим карту
        actionArea->resize(W, L, H);
        actionArea->getSize(Wmap, Lmap, Hmap);
    }
    else
    {
        // иначе только очищаем карту с предыдущего раза
        actionArea->clear();
    }

    int countLayers = H;
    int countBlockLayer = W * L;

    int epochs = countEpochs;

    // начинаем с 1-го слоя (0-й всегда заполнен)
    for (int h=1; h<countLayers; h++)
    {
        //
        for (int i=0; i<countBlockLayer; i++)
        {
            // выбираем случайный блок
            int x = 1 + rand()%(W-2);
            int y = 1 + rand()%(L-2);

            // если снизу есть блок то с опр. вер-ю ставим блок
            if (actionArea->getBlock(x, y, h - 1)->isEarth() && P(setBlockP))
            {
                actionArea->getBlock(x, y, h)->toEarth();
            }
        }

        // выполняем все правила каждую эпоху
        for (int j=0; j<epochs + h/3; j++)
        {
            // для случанйых живых клеток
            for (int k=0; k<countBlockLayer; k++)
            {
                // выбираем случайный блок
                int x = 1 + rand()%(W-2);
                int y = 1 + rand()%(L-2);

                // если блок существует, то выполняем следующие правила:
                if (actionArea->getBlock(x, y, h)->isEarth())
                {
                    // 1)
                    if (sumEarth(x, y, h) >= 3) builtRandBlock(x, y, h);
                    else actionArea->getBlock(x, y, h)->toVoid();

                    // 2)
                    ///if (sumLive(x, y, h) <= 2) map->getBlock(x, y, h)->toVoid();
                }
            }
        }

        changedProcessBuild(100 * ((double) h / countBlockLayer));
    }

    buildFinish(Wmap, Lmap, Hmap);
}

int geoGenerator::sumEarth(int x, int y, int z)
{
    int count = 0;
    if (actionArea->getBlock(x + 1, y    , z)->isEarth()) count++;
    if (actionArea->getBlock(x - 1, y    , z)->isEarth()) count++;
    if (actionArea->getBlock(x    , y + 1, z)->isEarth()) count++;
    if (actionArea->getBlock(x    , y + 1, z)->isEarth()) count++;

    if (actionArea->getBlock(x + 1, y + 1, z)->isEarth()) count++;
    if (actionArea->getBlock(x + 1, y - 1, z)->isEarth()) count++;
    if (actionArea->getBlock(x - 1, y + 1, z)->isEarth()) count++;
    if (actionArea->getBlock(x - 1, y - 1, z)->isEarth()) count++;

    return count;
}

void geoGenerator::removeRandBlock(int x, int y, int z) // координаты относительно которого удаляем
{
    switch (rand()%4)
    {
        case 0:
            actionArea->getBlock(x + 1, y, z)->toVoid();
            break;
        case 1:
            actionArea->getBlock(x - 1, y, z)->toVoid();
            break;
        case 2:
            actionArea->getBlock(x, y + 1, z)->toVoid();
            break;
        case 3:
            actionArea->getBlock(x, y - 1, z)->toVoid();
            break;
    }
}

void geoGenerator::builtRandBlock(int x, int y, int z)
{
    if (P(0.850))
    {
        switch (rand()%4)
        {
            case 0:
                if(actionArea->getBlock(x + 1, y, z - 1)->isEarth())
                    actionArea->getBlock(x + 1, y, z)->toEarth();
                break;
            case 1:
                if(actionArea->getBlock(x - 1, y, z - 1)->isEarth())
                    actionArea->getBlock(x - 1, y, z)->toEarth();
                break;
            case 2:
                if(actionArea->getBlock(x, y + 1, z-1)->isEarth())
                    actionArea->getBlock(x, y + 1, z)->toEarth();
                break;
            case 3:
                if(actionArea->getBlock(x, y - 1, z - 1)->isEarth())
                    actionArea->getBlock(x, y - 1, z)->toEarth();
                break;
        }
    }
}

bool geoGenerator::P(double p)
{
    int V = rand()%1000;
    double mP = (double) V/1000;

    return mP > (1 - p);
}
