#include "mapfile.h"

#include <QDebug>

MapFile::MapFile()
{
    //
    GeoColumn::setCountUnit(200);
    sizeColumn = GeoColumn::getDataSize();

    // Размеры дискретпространства
    lUnit = 20;
    hUnit = 20;

    //
    file = nullptr;

    // Сразу узнаем размер служебной информации карты в байт
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

void MapFile::init(const QString &dirNameFile,
                   int W, int L, int H)
{
    delete file;
    QFile::remove(dirNameFile);
    Wmap = W; Lmap = L; Hmap = H;
    int countColumns = Wmap * Lmap;

    GeoColumn::setCountUnit(Hmap);

    // Размер дискреты в байт
    sizeColumn = GeoColumn::getDataSize();

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
    mapData.W = Wmap; mapData.H = Hmap; mapData.L = Lmap;
    dStream << mapData;
    //qDebug() << optData.size();
    file->write(optData);

    // Записываем дискреты
    GeoColumn column;
    int countParts = parts.size();
    for (int nP=0; nP<countParts; nP++)
    {
        QByteArray data;
        QDataStream ds(&data, QIODevice::ReadWrite);

        for (int i=0; i<parts[nP]; i++)
        {
            ds << column;
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

    //
    GeoColumn::setCountUnit(Hmap);
    sizeColumn = GeoColumn::getDataSize();
}

void MapFile::getColumn(GeoColumn* column,
                        int idX, int idY) const
{
    //
    QDataStream inData(file);

    file->seek(idColumnToNumByte(idX, idY));

    inData >> column;
}

bool MapFile::isZD(int idX, int idY, int idH) const
{
    bool statZD;

    file->seek(idColumnToNumByte(idX, idY) + 4 + idH);
    QDataStream data(file->read(sizeof(bool)));
    data >> statZD;

    return statZD;
}

void MapFile::setZD(int idX, int idY, int idH, bool statZD)
{
    file->seek(idColumnToNumByte(idX, idY) + 4 + idH);
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << statZD;
    file->write(data);
}

int MapFile::getHeight(int idX, int idY) const
{
    int h;

    file->seek(idColumnToNumByte(idX, idY));
    QDataStream data(file->read(4));
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
