#ifndef RLS_H
#define RLS_H

#include <QObject>

#include <QPoint>
#include <QPointF>

#include <QVector>

#include "ray.h"
#include "map.h"

// класс РЛС
class RLS : public QObject
{
    Q_OBJECT
signals:
    // зона обнаружения начала расчитываться
    void startGenerateZD(int countM);

    // вертикальный сегмент готов
    void readyVector(int numVector);

    // зона обевружения сгенерирована
    void finishGenerateZD();

    // отправка графика ДН антены
    void exportGraphicData(double* x, double* y, int count);

    // информируем завершении настройки РЛС
    void readyOptZDvert();
    
public slots:
    // запрос данных для отрисовки графика ДН антены
    void getDataGraphic();

    // установка точки стояния РЛС
    void setPosition(double X, double Y);

    // моделирование локации РЛС
    void run(int x, int y, int H); // позиция и срез высот

    // установить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert(int Rmax); // в метрах

public:
    explicit RLS(Map* map, QObject *parent = 0);

    // Дискретность ЗО
    // по вертикали
    static const int count_PointsDV = 274;
    // по горизонали
    static const int COUNT_VECTORS_vert = 2000;

    double functionDV(double nL);

private:
    const double Pi = 3.1415926;

    // обновить значения ЗО в вертю плоскости
    void updateDV();

    // точка стояния РЛС
    QPointF position;
    double Hpos; // высота(координата Z)

    const double hSender = 3.1; // высота антены

 // ДН антены
    // построение ДН
    void buildDV();

    // дальность луча антены
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

    // построение каркаса ЗО
    void buildZD();

 // Рельеф (карта блоков)
    Map* map;

};

#endif // RLS_H
