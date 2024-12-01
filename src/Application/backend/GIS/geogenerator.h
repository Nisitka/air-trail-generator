#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <QObject>

#include <QFile>

#include "heightmeter.h"

#include "../MapFile/mapmanager.h"

#include "coords.h"
#include "mapdata.h"

//
#include "../MapFile/mapfile.h"

class GeoArea;

class geoGenerator: public QObject,
        public HeightMeter
{
    Q_OBJECT
signals:

public:
    geoGenerator(mapManager* manMap);

    // HeightMeter
    int absolute(int idX, int idY, Coords::units u) const override final;
    int max(Coords::units u) const override final;
    int heightBlock() const override final;
    int lenghtBlock() const override final;

    // В индексах всей карты
    Coords getCoords(int idX, int idY) const;

    // Загрузить рельеф
    void loadTerrain(const QString& dirNameFile);

    // Отредакутировать рельеф
    void editEarth(int idXo, int idYo,  // Левый верхний угол обл.
                   int w, int l,        // Ширина, длина области
                   int dH, int t = up); // Дельта изм., поднять/опустить
    enum editH{up, down};

    //
    void initMap(const MapData DataMap,
                 const QString& dirName);

    //
    void getSizeMap(int& W, int& L, int& H) const;

private:

    // Ширина/Длина блоков в столбцах
    void setLenBlock(int);
    int getLenBlock() const;

    // Высота блоков в столбцах
    void setHeightBlock(int); // в метрах
    int getHeightBlock() const;

    // mutex
     mutable  bool isLocked;

    //
    mapManager* manMap;
};

#endif // GEOGENERATOR_H
