#include "ray.h"

#include <cmath>

#include <QDebug>

Ray::Ray(double D_, double angleB_, double angleE_)
{
    D = D_;
    angleB = angleB_; //toRad(angleB_);
    angleE = angleE_; //toRad(angleE_);

    deltaL = mSIZE * 0.9;

    // сразу считаем дискретные значения полета луча
    toEmit();
}

// разделение луча на дискреты
void Ray::toEmit() // в градусах
{
    double currentL = 0.0;
    int* coord;

    double dLxy;
    while (currentL < D)
    {
        coord = new int[3];

        dLxy = currentL * cos(angleB);
        coord[X] =   dLxy * sin(angleE) / mSIZE;
        coord[Y] = -(dLxy * cos(angleE) / mSIZE);
        coord[Z] =   currentL * sin(angleB) / mH;

        Way.append(coord);

        currentL += deltaL; // текущая длина луча
    }
}

const QVector <int*>& Ray::getWay()
{
    return Way;
}

double Ray::toGrad(double angleRad)
{
    return (angleRad * 180) / Pi;
}
double Ray::toRad(double angleGrad)
{
    return (angleGrad * Pi) / 180;
}

Ray::~Ray()
{
    // очищаем память от дискрет пути луча
    for (int i=0; i<Way.size(); i++) delete [] Way[i];
}
