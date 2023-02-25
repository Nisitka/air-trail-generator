#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <QObject>

#include "map.h"

class geoGenerator : public QObject
{
    Q_OBJECT
signals:
    // информирование GUI
    void buildStart(int countLayers); // кол-во слоев
    void readyLayer(int idLayer); // номер слоя
    void buildFinish();

public slots:
    // запуск генерации рельефа
    void run(double setBlockP, int countEpochs,
             int W, int L, int H,
             double lenBlock);

public:
    geoGenerator(Map* map);

private:
    // карта
    Map* map;

    int Wmap;
    int Lmap;
    int Hmap;

    // дейсвия с блоками около указанного
    int sumEarth(int x, int y, int z); // кол-во с землей
    void builtRandBlock(int x, int y, int z);  // сделать землей случ-й блок
    void removeRandBlock(int x, int y, int z); // удалить случ-й блок

    // вернуть значение true c указанной вероятностью
    bool P(double p = 0.5);
};

#endif // GEOGENERATOR_H
