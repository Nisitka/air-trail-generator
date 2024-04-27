#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <QObject>

#include "map.h"
#include "paintermapimage.h"

class geoGenerator : public QObject
{
    Q_OBJECT
signals:

    //
    void buildStart();
    void changedProcessBuild(int countPercent); // в %
    void buildFinish(int W, int L, int H);

public:
    geoGenerator(Map* map);

    // Запуск генерации рельефа
    void buildRandomMap(double setBlockP, int countEpochs,
                        int W, int L, int H,
                        double lenBlock);

    //
    void buildFlatMap(int W = 400, int L = 400, int H = 256);

    void openMap(const QString& dirMapFile);

private:
    // Карта
    Map* map;

    //
    int Wmap;
    int Lmap;
    int Hmap;

    // Действия с блоками около указанного
    int  sumEarth(int x, int y, int z); // кол-во с землей
    void builtRandBlock(int x, int y, int z);  // сделать землей случ-й блок
    void removeRandBlock(int x, int y, int z); // удалить случ-й блок

    // Вернуть значение true c указанной вероятностью
    bool P(double p = 0.5);
};

#endif // GEOGENERATOR_H
