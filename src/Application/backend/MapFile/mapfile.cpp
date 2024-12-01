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

void MapFile::getPathAllRLS(QStringList &listPath) const
{
    listPath.clear();

}

void MapFile::getSize(int &W, int &L, int &H) const
{
    W = mapData.W;
    L = mapData.L;
    H = mapData.H;
}

int MapFile::getMaxHeight(Coords::units u) const
{
    int h = -1;

    h = mapData.H;
    switch (u) {
    case Coords::m:
        h *= mapData.hUnit;
        break;
    case Coords::id:
        /* ... */
        break;
    }

    return h;
}

void MapFile::init(const QString &dirNameFile, MapData data)
{
    if (file != nullptr) file->close();
    delete file;

    QFile::remove(dirNameFile);
    mapData.W = data.W;
    mapData.L = data.L;
    mapData.H = data.H;
    int countColumns = mapData.W * mapData.L;

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
        file->flush();
    }
}

void MapFile::close()
{
    file->flush();
    file->close();
}

void MapFile::reopen()
{
    //
    if (!file->open(QIODevice::ReadWrite))
        qDebug() << "ERROR!!!!!!!!!!!!";
}

void MapFile::open(const QString &dirMapFile)
{
    if (file != nullptr) file->close();
    delete file;

    //
    file = new QFile(dirMapFile);
    if (!file->open(QIODevice::ReadWrite))
        qDebug() << "ERROR!!!!!!!!!!!!";

    //
    file->seek(0); // Служеб. инф-я находится вначале
    QDataStream data(file->read(sizeOptData));
    data >> mapData;
    qDebug() << "MapData: "
             << mapData.W
             << mapData.L
             << mapData.H;
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
    int Wmap = mapData.W;
    int Lmap = mapData.L;

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
    if (h > mapData.H - 1) h = mapData.H-1;

    setHeight(idX, idY, h);
}

int MapFile::idColumnToNumByte(int idX, int idY) const
{
    return sizeOptData + (idColumn(idX, idY)*sizeColumn);
}

int MapFile::idColumn(int idX, int idY) const
{
    return (mapData.L*idX) + idY;
}

int MapFile::lenghtUnit() const
{
    return mapData.lUnit;
}

int MapFile::heightUnit() const
{
    return mapData.hUnit;
}

MapFile::~MapFile()
{
    if (file != nullptr) file->close();
    delete file;
}
