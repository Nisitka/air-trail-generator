#ifndef RLS_H
#define RLS_H

#include <QObject>

#include <QPoint>
#include <QPointF>

#include <QVector>
#include <QVector3D>

#include "../ray.h"
#include "../GIS/rzcreator.h"
#include "../GIS/heightmeter.h"
#include "../tracerlight.h"

#include "informerrls.h"

// класс РЛС
class RLS: public QObject, public InformerRLS
{
    Q_OBJECT
signals:

    // Уведомление об статусе завершения внут. процесса
    void changeStatProcessing(int percent);

    // Запущена очистка пространства РЛ сигнала
    void startClearZD();

    // Завершение очистки карты от ЗО
    void readyClearZD();

    // Зона обнаружения начала расчитываться
    void startEmitSignal();

    // Зона обнаружения сгенерирована
    void finishGenerateZD();

    // Отправка графика ДН антены
    void exportGraphicData(double* x, double* y, int count);

    // Начата установка настроек РЛС
    void startSetOpt();

    // Информируем завершении настройки РЛС
    void readyOptZDvert();
    
public slots:
    // Запрос данных для отрисовки графика ДН антены
    void getDataGraphic();

    // Установка точки стояния РЛС
    void setPosition(int idX, int idY);
    void setPosition(const QPoint& pos);

    // Моделирование локации РЛС
    void emitSignal(); // перемоделировать по предыдущим значениям (если РЛС вкл.)

    // Установить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert(int Rmax,  // в метрах
                      int countVertVectors, int countPointsDV);

    // включить/выключить РЛС
    void on();
    void off();

public:
    explicit RLS(TracerLight* RayTracer, RZCreator* RZEditor, HeightMeter* Height,
                 QPoint* position, const QString& nameRLS = nullptr);

    // Получить точки пересечения сигнала с рельефом
    const QVector <QVector <QVector3D>>& getPointsInterZD();


    void getRectPosition(int& idX, int& idY, int& W, int& H) const;

    double functionDV(double nL);

    void getOpt(int& Rmax, int& Xpos, int& Ypos, int& Hzd, bool& working) const;

    int getCountHorVectors() const;

    // очистка карты от сигнала данной РЛС
    void clearZD();

    ~RLS();

private:

    //
    TracerLight* RayTracer;
    RZCreator* RZEditor;
    HeightMeter* Height;

    // Точки соприкосновения ЗО с рельефом
    QVector <QVector <QVector3D>> interPointsZD;



    // Дискретность ЗО
    // по вертикали
    int count_PointsDV = 120; //275
    // по горизонали
    int COUNT_VECTORS_vert = 1080;//2000;

    QString name;

    const double Pi = 3.1415926;

    void removeZD();

    // Обновить значения ЗО в вертю плоскости
    void updateDV();

    double Hpos; // высота(координата Z) метры

    const double hSender = 3.1; // высота антены

    // ДН антены
    // построение ДН
    void buildDV();

    // Дальность луча антены
    double D = 2000; // метров

    double Emin = 0.01;
    double Eo = 0.3;
    double Emax = 0.69;
    double* mE; // массив дискрет углов места

    enum cDV{H, L};
    QVector <double*> l_DV; // приведенная ДН (0..1)
    QVector <double*> DV;
    void set_lDV(); //

    // ЗО (по вертикальным долькам)
    QVector <QVector <Ray*>*> ZD; // скелет из лучей

    // Построение каркаса ЗО
    void buildZD();

    // id блоков, которые находятся в ЗО данной РЛС
    QVector <QVector3D> blocksZD;

    // Для отображения прогресса
    int sizeZD;
};

#endif // RLS_H
