#include "labelrls.h"

LabelRLS::LabelRLS()
{
    /* ... */
}

void LabelRLS::getPosition(QVector3D &Point3D) const
{
    // В индексах
    Point3D = pos;
}

bool LabelRLS::isWorking() const
{
    return working;
}

QString LabelRLS::getName() const
{
    return name;
}
