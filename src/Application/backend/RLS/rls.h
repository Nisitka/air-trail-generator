#ifndef RLS_H
#define RLS_H

#include <QObject>

#include "../ray.h"
#include "../GIS/heightmeter.h"
#include "../tracerlight.h"

#include "labelrls.h"

// класс РЛС
class RLS: public QObject,
           public LabelRLS // Интерфейс для получения данных об РЛС
{
    Q_OBJECT
signals:

    // Уведомление об статусе завершения внут. процесса
    void changeStatProcessing(int percent);

    // Зона обнаружения начала расчитываться
    void startEmitSignal();

    // Начата установка настроек РЛС
    void startSetOpt();

    // Информируем завершении настройки РЛС
    void readyOptZDvert();
    
public slots:

    // Установка точки стояния РЛС
    void setPosition(int idX, int idY, int idH);
    void setPosition(const QVector3D& position);

    // включить/выключить РЛС
    void on();
    void off();

public:
    explicit RLS(LabelRLS dataRLS);

    //
    void getRectPosition(int& idX, int& idY, int& W, int& H) const;

    double functionDV(double nL);

    ~RLS();

private:

    // Высота антенны
    const double hSender = 3.1; // м

    // Построение ДН
    void buildDV();

    // здец :/
    double Pi = 3.14159265;

    //
    int count_PointsDV = 800;

    //
    double Emin = 0.01;
    double Eo = 0.3;
    double Emax = 0.69;

    // Массив дискрет углов места
    double* mE;

    // Посчитать диаграмму направленности
    void setDV(); //
};

#endif // RLS_H
