#ifndef MAP_H
#define MAP_H

#include <QObject>

#include <QVector>

#include "geoblock.h"

class Map : public QObject
{
    Q_OBJECT
public slots:
    // очистить карту (вернуть в исход. состояние)
    void clear();

public:
    Map();

    void setLenBlock(double);
    double getLenBlock();

    // получить размеры карты
    void getSize(int &w, int &l, int &h);
    int getWidth();
    int getLength();
    int getCountLayers();

    // изменить разеры
    void resize(int W, int L, int H);

    // получить блок
    geoBlock* getBlock(int x, int y, int z);

    // высота в координатах X, Y
    int getHeight(int X, int Y);

 /*   узнать кол-во блоков, находящихся в ЗО
  *   на координатах X, Y
  */int countZD(int x, int y);

private:
    // блоки хранится в слоях
    QVector <geoBlock*> layers;

    // построить скелет карты
    void build(int W, int L, int H);// размер карты в блоках
    void setSize(int w, int l, int h);
    int Height; // размеры карты
    int Width;
    int Length;

    // размеры куба в метрах
    double lenBlock;
};

#endif // MAP_H
