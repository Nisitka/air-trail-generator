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

    // очистить карту (вернуть в исход. состояние)
    void clear();

    // сохранить карту
    void save(const QString& dirFile);

    // открыть карту
    void open(const QString& dirFile);


    enum coord{x, y};

    //
    void setH(int idX, int idY, int valH);

    // Поднять высоту в области
    void upEarth(int idXo, int idYo, int R); // центр области, размер кисти

    // Опустить высоту в области
    void downEarth(int idXo, int idYo, int R);

    // Максимальная высота на карте
    float getMaxH(); // в метрах

    void setLenBlock(double);
    double getLenBlock() const;

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
    enum typeH{m, id};
    int getHeight(int X, int Y, int type = id);

 /*   Узнать кол-во блоков, находящихся в ЗО
  *   на координатах X, Y
  */int countZD(int x, int y) const;

    // Построить скелет карты
    void build(int W, int L, int H);// размер карты в блоках

private:
    // блоки хранится в слоях
    QVector <geoBlock*> layers;


    void setSize(int w, int l, int h);
    int Height; // размеры карты
    int Width;
    int Length;

    // размеры куба в метрах
    double lenBlock;

    // посыпать замлей дискрету
    void dropEarth(int idX, int idY, int countLayer);

    // убрать землю с дискреты
    void removeEarth(int idX, int idY, int countLayer);
};

#endif // MAP_H
