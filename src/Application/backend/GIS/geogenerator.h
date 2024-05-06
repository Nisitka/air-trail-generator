#ifndef GEOGENERATOR_H
#define GEOGENERATOR_H

#include <QObject>

#include "paintermapimage.h"

#include "heightmeter.h"

#include "coords.h"

class geoGenerator: public QObject, public HeightMeter
{
    Q_OBJECT
signals:

    //
    void buildStart();
    void changedProcessBuild(int countPercent); // в %
    void buildFinish(int W, int L, int H);

public:
    geoGenerator(int wArea, int lArea);

    //
    int absolute(int idX, int idY, Map::units u) const override final;

    /// !!!! пока так, надо убрать
    Map* getMap() const;

    // В дискретах текущей активной зоны
    int getH(int idX, int idY, int units = Map::m) const;
    Coords getCoords(int idX, int idY) const;

    // Запуск генерации рельефа
    void buildRandomMap(double setBlockP, int countEpochs,
                        int W, int L, int H,
                        double lenBlock);

    // Создать плоский (пустой) рельеф
    void buildFlatMap(int W = 400, int L = 400, int H = 256);

    // Открыть рельеф
    void openMap(const QString& dirMapFile);

    // Установить область активных действий
    void setPosActionArea(int idXo, int idYo);

    // Обновить данные по высотам в области
    void updateHeights(int idX, int idY, // Левый верхний угол
                       int W, int L);    // Ширина, длина

    // Отредакутировать рельеф
    void editEarth(int idXo, int idYo,       // Левый верхний угол обл.
                   int w, int l,             // Ширина, длина области
                   int dH, int t = Map::up); // Дельта изм., поднять/опустить

private:
    // Карта
    Map* map;

    // Матрица высот
    QVector<QVector<int>> heights;

    // Активная зона
    int idXo;  // Угол
    int idYo;
    int wArea; // Размеры
    int lArea;

    // Действия с блоками около указанного
    int  sumEarth(int x, int y, int z); // кол-во с землей
    void builtRandBlock(int x, int y, int z);  // сделать землей случ-й блок
    void removeRandBlock(int x, int y, int z); // удалить случ-й блок

    // Вернуть значение true c указанной вероятностью
    bool P(double p = 0.5);
};

#endif // GEOGENERATOR_H
