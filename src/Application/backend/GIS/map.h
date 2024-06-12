#ifndef MAP_H
#define MAP_H

#include <QObject>

#include <QVector>

#include "geoblock.h"

#include <QTextStream>

#include <QFile>

class Map
{
public:
    Map();

    // Очистить карту (вернуть в исход. состояние)
    void clear();

    enum coord{x, y};

    //
    void setH(int idX, int idY, int valH);

    // Максимальная высота на карте
    int getMaxH() const; // в метрах

    // Ширина/Длина дискрет (блоков)
    void setLenBlock(int);
    int getLenBlock() const;

    // Высота дискрет (блоков)
    void setHeightBlock(int); // в метрах
    int getHeightBlock() const;

    // Получить размеры карты
    void getSize(int &w, int &l, int &h) const;
    int getWidth(int type = id)          const;
    int getLength(int type = id)         const;
    int getCountLayers()                 const;

    // Изменить разеры
    void resize(int W, int L, int H);

    // Получить блок
    geoBlock* getBlock(int x, int y, int z) const;

    // Высота в координатах X, Y
    enum units{m, id};
    int getHeight(int X, int Y, int type = id) const;

 /*   Узнать кол-во блоков, находящихся в ЗО
  *   на координатах X, Y
  */int countZD(int x, int y) const;

    // Построить скелет карты
    void build(int W, int L, int H);// размер карты в блоках

private:
    // Блоки хранится в слоях
    QVector <geoBlock*> layers;

    //
    void setSize(int w, int l, int h);
    int Height; // размеры карты
    int Width;
    int Length;

    // Размеры куба в метрах
    int lenBlock;
    int heightBlock;
};

#endif // MAP_H
