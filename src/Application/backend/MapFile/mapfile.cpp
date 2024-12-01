#include "mapfile.h"

#include <QDebug>

MapFile::MapFile():
    file(nullptr)
{
    setSizeByteData();
}

MapFile::MapFile(const QString &dirNameFile, MapData data):
    file(nullptr)
{
    setSizeByteData();

    init(dirNameFile, data);
}

MapFile::MapFile(const QString &dirNameFile):
    file(nullptr)
{
    setSizeByteData();

    open(dirNameFile);
}

void MapFile::setSizeByteData()
{
    // Размер дискреты в байт
    sizeColumn = 4;

    // Узнаем размер служебной информации карты в байт
    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    ds << mapData;
    sizeOptData = data.size();
    data.clear();
}

void MapFile::getSize(int &W, int &L, int &H) const
{
    W = Wmap;
    L = Lmap;
    H = Hmap;
}

int MapFile::getMaxHeight(Coords::units u) const
{
    int h = -1;

    h = Hmap;
    switch (u) {
    case Coords::m:
        h *= hUnit;
        break;
    case Coords::id:
        /* ... */
        break;
    }

    return h;
}

void MapFile::init(const QString &dirNameFile, MapData data)
{
    delete file;
    QFile::remove(dirNameFile);
    mapData.W = data.W;
    mapData.L = data.L;
    mapData.H = data.H;
    int countColumns = Wmap * Lmap;

    // Размер дискрет
    mapData.lUnit = data.lUnit;
    mapData.hUnit = data.hUnit;

    file = new QFile(dirNameFile);

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

    file->open(QIODevice::ReadWrite);

    // Записываем служебную информацию
    QByteArray optData;
    QDataStream dStream(&optData, QIODevice::ReadWrite);
    dStream << mapData;
    //qDebug() << optData.size();
    file->write(optData);

    // Записываем дискреты
    int countParts = parts.size();
    for (int nP=0; nP<countParts; nP++)
    {
        QByteArray data;
        QDataStream ds(&data, QIODevice::ReadWrite);

        for (int i=0; i<parts[nP]; i++)
        {
            ds << 0;
        }
        file->write(data);
    }
}

void MapFile::open(const QString &dirMapFile)
{
    if (file != nullptr) file->close();
    delete file;

    //
    file = new QFile(dirMapFile);
    file->open(QIODevice::ReadWrite);

    //
    file->seek(0); // Служеб. инф-я находится вначале
    QDataStream data(file->read(sizeOptData));
    data >> mapData;
    Wmap = mapData.W; Lmap = mapData.L; Hmap = mapData.H;
    qDebug() << "MapData: " << Wmap << Lmap << Hmap;
}

int MapFile::getHeight(int idX, int idY) const
{
    int h;

    file->seek(idColumnToNumByte(idX, idY));
    QDataStream data(file->read(sizeColumn));
    data >> h;

    return h;
}

void MapFile::setHeight(int idX, int idY,
                        int height)
{
    file->seek(idColumnToNumByte(idX, idY));
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << height;
    file->write(data);
}

void MapFile::editHeightMatrix(int idXo, int idYo,
                               int w, int l,
                               int dH)
{
    //
    int lastX = idXo + w;
    int lastY = idYo + l;

    //
    if (idXo < 0) idXo = 0;
    if (idYo < 0) idYo = 0;
    if (lastX >= Wmap) lastX = Wmap - 1;
    if (lastY >= Lmap) lastY = Lmap - 1;

    // Изменяем высоту по дискретам-столбикам
    for (int x = idXo; x < lastX; x++)
    {
        for (int y = idYo; y < lastY; y++)
        {
            changeHeight(x, y, dH);
        }
    }

    //
    file->flush();
}

void MapFile::changeHeight(int idX, int idY, int dH)
{
    int h = this->getHeight(idX, idY);

    h += dH;

    if (h < 0)      h = 0;
    if (h > Hmap-1) h = Hmap-1;

    setHeight(idX, idY, h);
}

int MapFile::idColumnToNumByte(int idX, int idY) const
{
    return sizeOptData + (idColumn(idX, idY)*sizeColumn);
}

int MapFile::idColumn(int idX, int idY) const
{
    return Lmap*idX + idY;
}

int MapFile::lenghtUnit() const
{
    return lUnit;
}

int MapFile::heightUnit() const
{
    return hUnit;
}

MapFile::~MapFile()
{
    if (file != nullptr) file->close();
    delete file;
}
