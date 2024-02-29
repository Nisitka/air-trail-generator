#include "map.h"

#include <QDebug>

#include <QDateTime>

Map::Map()
{
    file = new QFile;

    this->build(400, 400, 200);

    // длина ребра блока по умолчанию
    lenBlock = 20;
}

void Map::upEarth(int idXo, int idYo, int R)
{
    int Xo = idXo - (R / 2);
    int Yo = idYo - (R / 2);

    int idX;
    int idY;
    for (int x=0; x<R; x++)
    {
        for (int y=0; y<R; y++)
        {
            idX = Xo+x;
            idY = Yo+y;

            //
            if (idX >= 0 && idX < Width &&
                idY >= 0 && idY < Length)
            {
                dropEarth(idX, idY, 1);
            }
        }
    }
}

void Map::downEarth(int idXo, int idYo, int R)
{
    int Xo = idXo - (R / 2);
    int Yo = idYo - (R / 2);

    int idX;
    int idY;
    for (int x=0; x<R; x++)
    {
        for (int y=0; y<R; y++)
        {
            idX = Xo+x;
            idY = Yo+y;

            //
            if (idX >= 0 && idX < Width &&
                idY >= 0 && idY < Length)
            {
                removeEarth(idX, idY, 1);
            }
        }
    }
}

void Map::dropEarth(int idX, int idY, int countLayer)
{
    int idH = getHeight(idX, idY);

    int maxH = layers.size();

    int id;
    for (int h = 1; h <= countLayer; h++)
    {
        id = idH + h;
        if (id < maxH) getBlock(idX, idY, id)->toEarth();
        else break;
    }
}

void Map::removeEarth(int idX, int idY, int countLayer)
{
    int idH = getHeight(idX, idY);

    int id;
    for (int h = 0; h < countLayer; h++)
    {
        id = idH - h;

        if (id > 0) getBlock(idX, idY, id)->remove();
        else break;
    }
}

void Map::save(const QString& dirFile)
{
    delete file;

    file = new QFile(dirFile);
    if (file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // системные данные
        QTextStream stream(file);
        stream << "Имя: карта№" + QString::number(rand()%1000) << endl
                << "Размеры(x,y,h): " +
                            QString::number(Width)  + " " +
                            QString::number(Length) + " " +
                            QString::number(Height) + " " << endl <<
                   "Дата: " + QDateTime::currentDateTime().toString() << endl;

        // данные карты
        for (int y=0; y<Length; y++)
        {
            for (int x=0; x<Width; x++)
            {
                stream << getHeight(x, y) << " ";
            }
            stream << "\n";
        }

        qDebug() << "Save map";
    }
    else
    {
        qDebug() << "ошибка создания файла";
    }
}

float Map::getMaxH()
{
    return getCountLayers() * lenBlock;
}

void Map::open(const QString &dirFile)
{
    delete file;

    file = new QFile(dirFile);
    if (file->open(QIODevice::ReadOnly))
    {
        QByteArray data;
        data = file->readAll();

        QStringList lines = QString(data).split("\n", QString::SkipEmptyParts);

        int W = lines[3].split(" ", QString::SkipEmptyParts).size() - 1;
        int L = lines.size() - 3;
        int H = 200; // пока что так!!!
        qDebug() << W << L;
        // изменяем конфигурацию карты
        resize(W, L, H);

        int h;
        for (int y=0; y<L; y++)
        {
            QStringList strValues = lines[y + 3].split(" ", QString::SkipEmptyParts);
            for (int x=0; x<W; x++)
            {
                h = strValues[x].toInt(); // макс. высота в этой координате
                for (int i=0; i<h; i++)
                {
                    this->getBlock(x, y, i)->toEarth(); // засыпаем землей
                }
            }
        }

        qDebug() << "Map ready!";

        updateVisual();
    }
    else
    {
        qDebug() << "ошибка открытия файла";
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

int Map::getCountLayers()
{
    return layers.size();
}

void Map::getSize(int &w, int &l, int &h)
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

int Map::countZD(int x, int y)
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

geoBlock* Map::getBlock(int x, int y, int z)
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

double Map::getLenBlock()
{
    return lenBlock;
}

int Map::getWidth(int type)
{
    switch (type)
    {
        case id: return Width;
        case m: return Width * lenBlock;
    }
}

int Map::getLength(int type)
{
    switch (type)
    {
        case id: return Length;
        case m: return Length * lenBlock;
    }
}

int Map::getHeight(int X, int Y, int type)
{
    int h = Height - 1;
    // спускаемся сверху пока не встретим землю
    while (!getBlock(X, Y, h)->isEarth()) h--;

    switch (type) {
    case m:
        return h * lenBlock;

    case id:
        return h;
    }
}
