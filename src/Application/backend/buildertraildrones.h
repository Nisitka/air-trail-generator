#ifndef BUILDERTRAILDRONES_H
#define BUILDERTRAILDRONES_H

#include <QObject>

#include <QPoint>
#include <QVector>

#include "ray.h"
#include "trail.h"
#include "map.h"

// генерирует скртный маршрут
class builderTrailDrones : public QObject
{
    Q_OBJECT
signals:  
    // Начало установок пар-ов моделирования
    void startSetOptPredict(int countIter);

    // Начало прогноза в областри
    void startPredictArea(int countIter); // кол-во итераций

public slots:
    // начать прогноз траектории от точки до точки
    void startPredictTrail(int idXa, int idYa,
                           int idXb, int idYb);

public:
    builderTrailDrones(Map* map);

    // Типы точек траектории
    enum typePoint{mainP, midP}; // опорные, промежуточные

private slots:


private:
    //
    bool estimRay();

    //
    void predictFromRect();

    // Лучи прогноза (по вертикальным долькам)
    QVector <QVector <Ray*>*> ZD; // скелет из лучей

    void buildZD();
    double Pi = 3.14159265;

    int Wmap;
    int Lmap;
    int Hmap;

    int curX;
    int curY;
    int curZ;

    int Xb, Yb;

    Trail* trail;

    double getDistance(int Xa, int Ya, int Xb, int Yb);

    // Кол-во
    int countHorPart; // долек
    int countVerRay;  // лучей в них

    // Длина лучей
    double longRay;
    //
    Map* map;
};

#endif // BUILDERTRAILDRONES_H
