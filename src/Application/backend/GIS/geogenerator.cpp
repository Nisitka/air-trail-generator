#include "geogenerator.h"

#include <QImage>
#include <QApplication>
#include <cmath>

#include <QDebug>

#include <QRgb>

geoGenerator::geoGenerator(int wArea_, int lArea_):
    wArea(wArea_), lArea(lArea_)
{
    //
    actionArea = new Map;

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

    //
    data.clear();
    ds << mapData;
    sizeOptData = data.size();
    data.clear();
}

void geoGenerator::toZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    int id = idBlock(idX, idY, idH);
    if (inActionArea(idX, idY, idH))
    {
        geoBlock* b = actionArea->getBlock(idX-idXo, idY-idYo, idH);
        b->toZD();
        //updateBlock(id, *b);
    }
    else
    {
        geoBlock b = readBlock(id);
        b.toZD();
        //updateBlock(id, b);
    }
}

void geoGenerator::clearZD(const QVector3D &posBlock) const
{
    int idX = posBlock.x();
    int idY = posBlock.y();
    int idH = posBlock.z();

    int id = idBlock(idX, idY, idH);
    if (inActionArea(idX, idY, idH))
    {
        geoBlock* b = actionArea->getBlock(idX-idXo, idY-idYo, idH);
        b->removeZD();
        //updateBlock(id, *b);
    }
    else
    {
        geoBlock b = readBlock(id);
        b.removeZD();
        //updateBlock(id, b);
    }
}

bool geoGenerator::inActionArea(int idX, int idY, int idH) const
{
    if (idX < idXo  || idY < idYo)  return false;
    if (idX > lastX || idY > lastY) return false;

    return true;
}

const geoBlock& geoGenerator::block(int idX, int idY, int idH) const
{
    if (inActionArea(idX, idY, idH))
    {
        return *actionArea->getBlock(idX-idXo, idY-idYo, idH);
    }
    else
    {
        cacheBlock = readBlock(idBlock(idX, idY, idH));
        return cacheBlock;
    }
}

void geoGenerator::initMap(int W, int L, int H)
{
    buildStart();

    delete map;
    QFile::remove(dirNameTmpMap);
    Wmap = W; Lmap = L; Hmap = H;
    int countBlocks = Wmap * Lmap * Hmap;

    //
    actionArea->build(wArea, lArea, Hmap);

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
                ds << block;
        }
            map->write(data);
    }

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
    actionArea->build(wArea, lArea, Hmap);

    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::setPosActionArea(int idXo_, int idYo_)
{
    //
    idXo = idXo_;
    idYo = idYo_;

    //
    lastX = idXo + wArea;
    lastY = idYo + lArea;

    //
    actionArea->clear();

    QDataStream inData(map);
    geoBlock b;
    for(int h=0; h<Hmap; h++)
    {
        map->seek(sizeOptData + (idBlock(idXo, idYo, h)*sizeBlock)); //
        for(int x=0; x<wArea; x++)
        {
            map->seek(sizeOptData + (idBlock(idXo+x, idYo, h)*sizeBlock)); //
            for (int y=0; y<lArea; y++)
            {
                inData >> b;
                actionArea->getBlock(x,y,h)->setValues(b);
            }
        }
    }

    //qDebug() << "setPosArea!";
}

int geoGenerator::idBlock(int idX, int idY, int idH) const
{
    return Wmap*Lmap*idH + Lmap*idX + idY;
}

void geoGenerator::updateBlock(int idBlock, const geoBlock& b) const
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << b;

    map->seek(sizeOptData + (sizeBlock * idBlock));
    map->write(data, sizeBlock);
}

geoBlock geoGenerator::readBlock(int idBlock) const
{
    map->seek(sizeOptData + (sizeBlock * idBlock));
    QDataStream inData(map->read(sizeBlock));

    geoBlock b;
    inData >> b;

    return b;
}

int geoGenerator::absolute(int idX, int idY, Map::units units) const
{
    int h = -1;

    switch (units) {
    case Map::m:
        h = actionArea->getHeight(idX-idXo, idY-idYo, units);

        break;
    case Map::id:
        h = actionArea->getHeight(idX-idXo, idY-idYo, units);

        break;
    }

    return h;
}

int geoGenerator::max(Map::units u) const
{
    int h = -1;

    switch (u) {
    case Map::m:
        h = actionArea->getMaxH();

        break;
    case Map::id:
        h = actionArea->getCountLayers();

        break;
    }

    return h;
}

int geoGenerator::countVertZD(int idX, int idY) const
{
    return actionArea->countZD(idX, idY);
}

Coords geoGenerator::getCoords(int idX, int idY) const
{
    int X = idX;
    int Y = idY;
    int H = actionArea->getHeight(idX-idXo, idY-idYo, Map::id);

    return Coords(X, Y, H, actionArea->getLenBlock());
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

    int idLast = idHo + countLayer;
    if (idLast > maxH) idLast = maxH;
    geoBlock* block;
    for (int idH = idHo; idH <= idLast; idH++)
    {
        block = actionArea->getBlock(idX, idY, idH);
        block->toEarth();

        // Сразу обновляем его значения в файле-карте
        updateBlock(idBlock(idXo+idX, idYo+idY, idH), *block);
    }
}

void geoGenerator::removeEarth(int idX, int idY, int countLayer)
{
    int idHo = actionArea->getHeight(idX, idY);

    int idLast = idHo - countLayer;
    if (idLast < 0) idLast = 0;
    geoBlock* block;
    for (int idH = idHo; idH > idLast; idH--)
    {
        block = actionArea->getBlock(idX, idY, idH);
        block->remove();

        // Сразу обновляем его значения в файле-карте
        updateBlock(idBlock(idXo+idX, idYo+idY, idH), *block);
    }
}

void geoGenerator::updateHeights(int idX, int idY, int W, int L)
{
    int idLastX = idX + W;
    int idLastY = idY + L;

    for (int X=idX; X<=idLastX; X++)
    {
        for (int Y=idY; Y<=idLastY; Y++)
        {
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
