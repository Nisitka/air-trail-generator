#ifndef MAP_H
#define MAP_H

#include <QObject>

#include <QVector>

#include "geoblock.h"

#include <QTextStream>

#include <QFile>

class Map : public QObject
{
    Q_OBJECT
signals:
    // обновить отоброжение карты
    void updateVisual();

public slots:
    // очистить карту (вернуть в исход. состояние)
    void clear();

    // сохранить карту
    void save(const QString& dirFile);

    // открыть карту
    void open(const QString& dirFile);

public:
    Map();

    enum coord{x, y};

    // поднять высоту в области
    void upEarth(int idXo, int idYo, int R); // центр области, размер кисти

    // опустить высоту в области
    void downEarth(int idXo, int idYo, int R);

    // максимальная высота на карте
    float getMaxH(); // в метрах

    void setLenBlock(double);
    double getLenBlock();

    // получить размеры карты
    void getSize(int &w, int &l, int &h);
    int getWidth(int type = id);
    int getLength(int type = id);
    int getCountLayers();

    // изменить разеры
    void resize(int W, int L, int H);

    // получить блок
    geoBlock* getBlock(int x, int y, int z);

    // высота в координатах X, Y
    enum typeH{m, id};
    int getHeight(int X, int Y, int type = id);

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

    // посыпать замлей дискрету
    void dropEarth(int idX, int idY, int countLayer);

    // убрать землю с дискреты
    void removeEarth(int idX, int idY, int countLayer);

    QFile* file;
};

#endif // MAP_H
