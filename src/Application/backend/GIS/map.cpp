#include "map.h"

#include <QDebug>

#include <QDateTime>

Map::Map()
{
    // Длина ребра блока по умолчанию
    lenBlock = 20;
}

void Map::editEarth(int idXo, int idYo, int w, int l, int dH, int t)
{
    //
    int lastX = idXo + w;
    int lastY = idYo + l;

    //
    if (idXo < 0) idXo = 0;
    if (idYo < 0) idYo = 0;
    if (lastX >= Width)  lastX = Width -1;
    if (lastY >= Length) lastY = Length-1;

    //
    void (Map::*f)(int, int, int);
    switch (t) {
    case up:
        f = &Map::dropEarth;
        break;
    case down:
        f = &Map::removeEarth;
        break;
    }

    //
    for (int x = idXo; x < lastX; x++)
    {
        for (int y = idYo; y < lastY; y++)
        {
            (this->*f)(x, y, dH);
        }
    }
}

void Map::dropEarth(int idX, int idY, int countLayer)
{
    int idH = getHeight(idX, idY);

    int maxH = Height;

    int idLast = idH + countLayer;
    if (idLast > maxH-1) idLast = maxH-1;
    for (int id = idH; id <= idLast; id++)
    {
        getBlock(idX, idY, id)->toEarth();
    }
}

void Map::removeEarth(int idX, int idY, int countLayer)
{
    int idH = getHeight(idX, idY);

    int idLast = idH - countLayer;
    if (idLast <= 0) idLast = 1;
    for (int id = idH; id > idLast; id--)
    {
        getBlock(idX, idY, id)->remove();
    }
}

float Map::getMaxH()
{
    return getCountLayers() * lenBlock;
}

void Map::setH(int idX, int idY, int valH)
{
    for (int h=1; h<valH; h++)
    {
        getBlock(idX, idY, h)->toEarth();
    }
}

void Map::setLenBlock(double len)
{
    lenBlock = len;
}

void Map::resize(int W, int L, int H)
{
    for (int i=0; i<Height; i++)
    {   // очищаем память от предыдущих слоев
        delete [] layers.at(i);
    }
    layers.clear();

    build(W, L, H);
}

int Map::getCountLayers() const
{
    return layers.size();
}

void Map::getSize(int &w, int &l, int &h) const
{
    w = Width;
    l = Length;
    h = Height;
}

void Map::build(int W, int L, int H)
{   // инициализация размеров карты
    setSize(W, L, H);

    // добавление слоев
    for (int i=0; i<Height; i++)
    {
        layers.append(new geoBlock[Width*Length]);
    }

    // покрываем первый слой землей
    geoBlock* pLayer = layers.at(0);
    for (int j=0; j<Width*Length; j++)
    {
        pLayer[j].toEarth();
    }
}

int Map::countZD(int x, int y) const
{
    int countZD = 0;
    for (int h=0; h<Height; h++)
    {
        if (getBlock(x, y, h)->isZD())
        {
            countZD++;
        }
    }

    return countZD;
}

geoBlock* Map::getBlock(int x, int y, int z) const
{
    return layers.at(z) + Width*y + x;
}

void Map::clear()
{
    for (int i=0; i<Width; i++)
    {
        for (int j=0; j<Length; j++)
        {
            for (int h=1; h<Height; h++)
            {
                getBlock(i, j, h)->remove();
            }
        }
    }
}

void Map::setSize(int w, int l, int h)
{
    Width = w; Length = l; Height = h;
}

double Map::getLenBlock() const
{
    return lenBlock;
}

int Map::getWidth(int type) const
{
    int w = 0;

    switch (type)
    {
        case id:

            w = Width;
            break;
        case m:

            w = Width * lenBlock;
            break;
    }

    return w;
}

int Map::getLength(int type) const
{
    int l = 0;

    switch (type)
    {
        case id:

            l = Length;
            break;

        case m:

            l = Length * lenBlock;
            break;
    }

    return l;
}

int Map::getHeight(int X, int Y, int type)
{
    // Cпускаемся сверху пока не встретим землю
    int h = Height-1;
    while (!getBlock(X, Y, h)->isEarth()) h--;

    switch (type) {
    case m:
        h *= lenBlock;
        break;

    case id:

        break;
    }

    return h;
}
