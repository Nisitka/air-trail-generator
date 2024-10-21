#ifndef RAY_H
#define RAY_H

#include <QVector3D>

const float Pi = 3.1415926;

class Ray
{
public:

    // Через угол места и азимут
    Ray(double angleB, double angleE); // рад, рад

    // Через вектор направления
    Ray(const QVector3D& tVector);

    // Через две точки
    Ray(const QVector3D& posPoint, const QVector3D& interPoint);

    ~Ray();

private:

};

#endif // RAY_H
