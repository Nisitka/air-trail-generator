#ifndef MAPFILE_H
#define MAPFILE_H

#include <QString>
#include <QFile>

/// Интерфейсы
#include "./datamapgis.h"
#include "./datamaprls.h"

#include "../GIS/coords.h"
#include "../GIS/mapdata.h"

// Класс по работе с файлом-картой
class MapFile:             // Инткрфейсы:
        public DataMapGIS, //   Для работы с пространством
        public DataMapRLS  //   Для работы с РЛС
{
public:
    MapFile();

    // Узнать размеры карты
    void getSize(int& W, int& L, int& H) const override final;
    int getMaxHeight(Coords::units u) const;

    //
    void init(const QString& dirNameFile,
              int W, int L, int H);

    //
    void open(const QString &dirMapFile);

    //
    int lenghtUnit() const override final; // В метрах
    int heightUnit() const override final; // В метрах

    //
    void getColumn(GeoColumn* column,
                   int idX, int idY) const override final;

    //
    bool isZD(int idX, int idY, int idH) const override final;
    void setZD(int idX, int idY, int idH,
               bool statZD) override final;

    //
    int getHeight(int idX, int idY) const override final;
    void setHeight(int idX, int idY,
                   int height) override final;

private:

    // Кол-во байтов до столбца
    int idColumnToNumByte(int idX, int idY) const;

    // Порядковый номер дискреты-столбца в файле
    int idColumn(int idX, int idY) const;

    //
    int Wmap, Lmap, Hmap;
    QFile* file;

    // Размеры блоков в метрах
    int lUnit;
    int hUnit;

    // Кол-во байт в файле карты на:
    qint64 sizeColumn;  // Одну дискрету
    qint64 sizeOptData; // Другие данные

    //
    MapData mapData;

};

#endif // MAPFILE_H
