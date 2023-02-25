#ifndef RAY_H
#define RAY_H

#include <QVector>

const float Pi = 3.1415926;

class Ray
{
public:
    Ray(double D, double angleB, double angleE); // м, град, град

    enum coords_{X, Y, Z};
    // испустить луч сигнала
    void toEmit();
    QVector <int*>* getWay();

    // множетель масштаба
    static const int mSIZE = 20; // в одной клетке mSIZE метров
    static const int mH = 20; // дисритезация высот

    static double toGrad(double angleRad);
    static double toRad(double angleGrad);

    ~Ray();

private:
    // частота дискритезации распрастронения
    double deltaL; // (метры)

    double D;  // max длина (метры)
    double angleB; // угол места (радианы)
    double angleE; // азимут

    QVector <int*> Way;
};

#endif // RAY_H
