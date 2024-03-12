#ifndef TRAIL_H
#define TRAIL_H

#include <QVector3D>
#include <QList>

// Маршрут пролета БпЛА
class Trail
{
public:
    Trail();

    void addPoint(float X, float Y, float Z);

private:
    //
    QList <QVector3D> points;
};

#endif // TRAIL_H
