#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <QObject>

#include <QFile>

#include "heightmeter.h"
#include "rzinformer.h"

#include "rzcreator.h"

#include "coords.h"
#include "mapdata.h"

//
#include "../MapFile/mapfile.h"

class GeoArea;

class geoGenerator: public QObject,
        public HeightMeter, public RZInformer, public RZCreator
{
    Q_OBJECT
signals:

    //
    void buildStart();
    void changedProcessBuild(int countPercent); // в %
    void buildFinish(int W, int L, int H);

public:
    geoGenerator();

    // Редактирование дискрет на наличие РЛ сигнала (RZCreator)
    void toZD(const QVector3D &idBlock) const override final;
    void clearZD(const QVector3D &idBlock) const override final;

    // HeightMeter
    int absolute(int idX, int idY, Coords::units u) const override final;
    int max(Coords::units u) const override final;
    int heightBlock() const override final;
    int lenghtBlock() const override final;

    // RZInformer
    int countVertZD(int idX, int idY) const override final;
    bool isZD(int idX, int idY, int idH) const override final;

    // В индексах всей карты
    Coords getCoords(int idX, int idY) const;

    // Открыть карту
    void openMap(const QString& dirMapFile);

    // Загрузить рельеф
    void loadTerrain(const QString& dirNameFile);

    // Обновить данные по высотам в области
    void updateHeights(int idX, int idY, // Левый верхний угол
                       int W, int L);    // Ширина, длина

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

    ///
    MapFile* mapFile;
    int Hmap;
    int Wmap;
    int Lmap;
};

#endif // GEOGENERATOR_H
