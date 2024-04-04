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

    // Установка пар-ов моделирования
    void startSetOptPredict();
    void procSetOptPred(int percent);    // на сколько настройки уже применены
    void finishSetOptPredict();

    // Уведомление об прогнозе очередной точки
    void nextPointTrail(int idX, int idY, int idH);

    //
    void finishPredOnlyRect(int idXpred, int idYpred, int idZpred);

public slots:

    // Запустить прогноз только в области
    void runPredictRect(int idXa, int idYa, int idZa,
                        int idXb, int idYb, int idZb);

    // Начать прогноз траектории от точки до точки
    void startPredictTrail(int idXa, int idYa,  // Нач. точка
                           int idXb, int idYb); // Кон. точка

    // Изменить радиус прогноза
    void setRpredict(int countDiscretes);

public:
    builderTrailDrones(Map* map);

    // Типы точек траектории
    enum typePoint{mainP, midP}; // опорные, промежуточные

private slots:


private:

    void setOptPredict();

    //
    bool estimRay();

    // Прогноз в одной области
    void predictFromRect(int idXa, int idYa, int idZa,
                         int idXb, int idYb, int idZb,
                         int& idXres, int& idYres, int& idZres);

    // Лучи прогноза (по вертикальным долькам)
    QVector <QVector <Ray*>*> ZD; // скелет из лучей

    void buildZD();
    bool isEditOptPred;
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
