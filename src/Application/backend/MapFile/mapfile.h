#ifndef MAPFILE_H
#define MAPFILE_H

#include <QStringList>
#include <QFile>

/// Интерфейсы
#include "./datamapgis.h"
#include "./datamaprls.h"

#include "../GIS/coords.h"
#include "../GIS/mapdata.h"

// Класс по работе с файлом-картой
class MapFile:              // Инткрфейсы:
        public DataMapGIS,  //  Для работы с пространством
        public DataMapRLS   //  Для работы с РЛС
{
public:

    MapFile();
    MapFile(const QString &dirNameFile, MapData data); // Создаем новый файл
    MapFile(const QString &dirNameFile); // Открываем существующий файл
    ~MapFile();

    // Узнать размеры карты
    void getSize(int& W, int& L, int& H) const override final;
    int getMaxHeight(Coords::units u) const;

    //
    void init(const QString &dirNameFile, MapData data);

    //
    void open(const QString &dirMapFile);

    //
    int lenghtUnit() const override final; // В метрах
    int heightUnit() const override final; // В метрах

    //
    int getHeight(int idX, int idY) const override final;
    void setHeight(int idX, int idY,
                   int height) override final;

    // Отредакутировать рельеф
    void editHeightMatrix(
                   int idXo, int idYo,  // Левый верхний угол обл.
                   int w, int l,        // Ширина, длина области
                   int dH); // Дельта изм.

    // Посыпать землей дискрету (id относительно Action Area)
    void dropEarth(int idX, int idY, int countLayer);
    // Убрать землю с дискреты
    void removeEarth(int idX, int idY, int countLayer);

    void changeHeight(int idX, int idY, int dH);

private:

    // Расчет размеров полей файла
    void setSizeByteData();

    // Список РЛС, поставленных на карту
    QStringList namesRLS;

    // Кол-во байтов до столбца
    int idColumnToNumByte(int idX, int idY) const;

    // Порядковый номер дискреты-столбца в файле
    int idColumn(int idX, int idY) const;

    //
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
