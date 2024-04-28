#ifndef RLS_H
#define RLS_H

#include <QObject>

#include <QPoint>
#include <QPointF>

#include <QVector>
#include <QVector3D>

#include "ray.h"
#include "gis/map.h"

// класс РЛС
class RLS: public QObject
{
    Q_OBJECT
signals:
    // завершение очистки карты от ЗО
    void readyClearZD();

    // начата установка настроек РЛС
    void startSetOpt(int countRay);

    //
    void readySetRay(int numRay); // номер луча

    // зона обнаружения начала расчитываться
    void startGenerateZD(int countM);

    // вертикальный сегмент готов
    void readyVector(int numVector);

    // зона обнаружения сгенерирована
    void finishGenerateZD();

    // отправка графика ДН антены
    void exportGraphicData(double* x, double* y, int count);

    // информируем завершении настройки РЛС
    void readyOptZDvert();
    
public slots:
    // запрос данных для отрисовки графика ДН антены
    void getDataGraphic();

    // установка точки стояния РЛС
    void setPosition(int idX, int idY);

    // моделирование локации РЛС
    void emitSignal(int H); // срез высот (и запускаем РЛС)
    void emitSignal(); // перемоделировать по предыдущим значениям (если РЛС вкл.)

    // установить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert(int Rmax,  // в метрах
                      int countVertVectors, int countPointsDV);

    // включить/выключить РЛС
    void on();
    void off();

public:
    explicit RLS(Map* map, QPoint* position, const QString& nameRLS = nullptr);

    //
    void getPosition(QVector3D& point);

    // получить точки пересечения сигнала с рельефом
    const QVector <QVector <QVector3D>>& getPointsInterZD();

    // узнать максимальное кол-во дискрет ЗО, которое может дать эта РЛС
    int getCountMaxBlocksZD();

    //
    int getCurrentBlocksZD(int idX, int idY, int idMaxH);

    // узнать, работает ли РЛС
    bool isWorking();

    void getRectPosition(int& idX, int& idY, int& W, int& H);

    double functionDV(double nL);

    void getOpt(int& Rmax, int& Xpos, int& Ypos, int& Hzd, bool& working);

    int getCountHorVectors();

    // очистка карты от сигнала данной РЛС
    void clearZD();

    ~RLS();

private:
    // точки соприкосновения ЗО с рельефом
    QVector <QVector <QVector3D>> interPointsZD;

    // включена ли РЛС
    bool working;

    // Дискретность ЗО
    // по вертикали
    int count_PointsDV = 120; //275
    // по горизонали
    int COUNT_VECTORS_vert = 1080;//2000;

    QString name;

    const double Pi = 3.1415926;

    void removeZD();

    // обновить значения ЗО в вертю плоскости
    void updateDV();

    // точка стояния РЛС
    QPoint* position;
    double Hpos; // высота(координата Z) метры

    const double hSender = 3.1; // высота антены

 // ДН антены
    // построение ДН
    void buildDV();

    // срез ЗО
    int maxHzd; // в индексах высоты
    int minHzd;

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

    // блоки, которые находятся в ЗО данной РЛС
    QVector <geoBlock*> blocksZD;

    // для отображения прогресса
    int sizeZD;
};

#endif // RLS_H
