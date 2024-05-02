#include "geogenerator.h"

#include <QImage>
#include <QApplication>
#include <cmath>

#include <QDebug>

#include <QRgb>

geoGenerator::geoGenerator(int wArea_, int lArea_,
                           QVector<QVector<int> *>* pHeights):
    wArea(wArea_), lArea(lArea_)
{
    idXo = 0;
    idYo = 0;

    //
    map = new Map;

    //heights = QVector<QVector<int> *>;
    pHeights = &heights;
}

int geoGenerator::getH(int idX, int idY) const
{
    map->getHeight(idX - idXo, idY - idYo, Map::m);
}

Coords* geoGenerator::getCoords(int idX, int idY) const
{
    int l = map->getLenBlock();

    int X = (idXo + idX) * l;
    int Y = (idYo + idY) * l;
    int H = getH(idX, idY);

    return new Coords(X, Y, H);
}

Map* geoGenerator::getMap() const
{
    return map;
}

void geoGenerator::openMap(const QString &dirMapFile)
{
    buildStart();

    // Источник данных об рельефе
    QImage geoData(dirMapFile);

    // Полные размеры карты
    int Wmap = geoData.width();
    int Lmap = geoData.height();
    int Hmap = 256;

    // Размер карты, олицитворяющей активную зону
    map->resize(wArea, lArea, Hmap);

    int h;
    QColor color;
    for (int x=0; x<Wmap; x++)
    {
        heights.append(new QVector<int>);
        for (int y=0; y<Lmap; y++)
        {
            color = geoData.pixelColor(x, y);
            h = Hmap * ((double) ((double)color.blueF() +
                                          color.redF()  +
                                          color.greenF()) / 1.0);
            heights.last()->append(h);
        }
    }

    setPosActionArea(0, 0);

    buildFinish(Wmap, Lmap, Hmap);
}

void geoGenerator::editEarth(int idXo, int idYo, int w, int l, int dH, int t)
{
    map->editEarth(idXo, idYo, w, l, dH, t);
}

void geoGenerator::setPosActionArea(int idXo_, int idYo_)
{
    idXo = idXo_;
    idYo = idYo_;

    //
    map->clear();

    int h;
    for (int x=0; x<wArea; x++)
    {
        for (int y=0; y<lArea; y++)
        {
            h = heights[idXo + x]->at(idYo + y);
            map->setH(x, y, h);
        }
    }
}

void geoGenerator::updateHeights(int idX, int idY, int W, int L)
{

}

void geoGenerator::buildFlatMap(int W, int L, int H)
{
    buildStart();

    map->resize(W, L, H);

    buildFinish(W, L, H);
}

void geoGenerator::buildRandomMap(double setBlockP, int countEpochs,
                                  int W, int L, int H,
                                  double lenBlock)
{
    buildStart();

    // устанавливаем длину ребра блока
    map->setLenBlock(lenBlock);

    // берем актуальный размер карты
    int Wmap;
    int Lmap;
    int Hmap;
    map->getSize(Wmap, Lmap, Hmap);

    // если размеры необходимо изменить
    if (Wmap != W || Lmap != L || Hmap != H)
    {
        // прежде чем генерировать рельеф, создадим карту
        map->resize(W, L, H);
        map->getSize(Wmap, Lmap, Hmap);
    }
    else
    {
        // иначе только очищаем карту с предыдущего раза
        map->clear();
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
            if (map->getBlock(x, y, h - 1)->isEarth() && P(setBlockP))
            {
                map->getBlock(x, y, h)->toEarth();
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
                if (map->getBlock(x, y, h)->isEarth())
                {
                    // 1)
                    if (sumEarth(x, y, h) >= 3) builtRandBlock(x, y, h);
                    else map->getBlock(x, y, h)->toVoid();

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
    if (map->getBlock(x + 1, y    , z)->isEarth()) count++;
    if (map->getBlock(x - 1, y    , z)->isEarth()) count++;
    if (map->getBlock(x    , y + 1, z)->isEarth()) count++;
    if (map->getBlock(x    , y + 1, z)->isEarth()) count++;

    if (map->getBlock(x + 1, y + 1, z)->isEarth()) count++;
    if (map->getBlock(x + 1, y - 1, z)->isEarth()) count++;
    if (map->getBlock(x - 1, y + 1, z)->isEarth()) count++;
    if (map->getBlock(x - 1, y - 1, z)->isEarth()) count++;

    return count;
}

void geoGenerator::removeRandBlock(int x, int y, int z) // координаты относительно которого удаляем
{
    switch (rand()%4)
    {
        case 0:
            map->getBlock(x + 1, y, z)->toVoid();
            break;
        case 1:
            map->getBlock(x - 1, y, z)->toVoid();
            break;
        case 2:
            map->getBlock(x, y + 1, z)->toVoid();
            break;
        case 3:
            map->getBlock(x, y - 1, z)->toVoid();
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
                if(map->getBlock(x + 1, y, z - 1)->isEarth())
                    map->getBlock(x + 1, y, z)->toEarth();
                break;
            case 1:
                if(map->getBlock(x - 1, y, z - 1)->isEarth())
                    map->getBlock(x - 1, y, z)->toEarth();
                break;
            case 2:
                if(map->getBlock(x, y + 1, z-1)->isEarth())
                    map->getBlock(x, y + 1, z)->toEarth();
                break;
            case 3:
                if(map->getBlock(x, y - 1, z - 1)->isEarth())
                    map->getBlock(x, y - 1, z)->toEarth();
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
