#ifndef BUILDERTRAILDRONES_H
#define BUILDERTRAILDRONES_H

#include <QObject>

#include <QPoint>
#include <QVector>

#include "drone.h"
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
    void startPredictTrail(Drone* drone,
                           int idXa, int idYa,
                           int idXb, int idYb);

public:
    builderTrailDrones(Map* map);

    // Типы точек траектории
    enum typePoint{mainP, midP}; // опорные, промежуточные

private slots:


private:
    //
    bool estimRay();

    // Лучи прогноза (по вертикальным долькам)
    QVector <QVector <Ray*>*> ZD; // скелет из лучей

    //
    Map* map;

    // БПЛА, для которого осуще-ся прогноз
    Drone* curDrone;

};

#endif // BUILDERTRAILDRONES_H
