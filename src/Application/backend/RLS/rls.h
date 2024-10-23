#ifndef RLS_H
#define RLS_H

#include <QObject>

#include <QPoint>
#include <QPointF>

#include <QVector>
#include <QVector3D>

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

    // Установить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert(int Rmax);

    // включить/выключить РЛС
    void on();
    void off();

public:
    explicit RLS(const QVector3D& position,
                 const QString& nameRLS = nullptr);

    // Получить данные об ДН антены
    void getGraphicData(QVector <double>& X,
                        QVector <double>& Y) const;

    //
    void getRectPosition(int& idX, int& idY, int& W, int& H) const;

    double functionDV(double nL);

    ~RLS();

private:

    // Высота антенны
    const double hSender = 3.1; // м

    // ДН антены
    // построение ДН
    void buildDV();
    void updateDV();

    // Дальность луча антены
    double D = 2000; // метров

    // здец :/
    double Pi = 3.14159265;

    int count_PointsDV = 800;

    double Emin = 0.01;
    double Eo = 0.3;
    double Emax = 0.69;
    double* mE; // массив дискрет углов места

    enum cDV{H, L};
    QVector <double*> l_DV; // приведенная ДН (0..1)
    QVector <double*> DV;
    void set_lDV(); //
};

#endif // RLS_H
