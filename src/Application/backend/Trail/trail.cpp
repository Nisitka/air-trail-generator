#include "trail.h"

Trail::Trail()
{

}

void Trail::addPoint(float X, float Y, float Z)
{
    points.append(QVector3D(X, Y, Z));
}
