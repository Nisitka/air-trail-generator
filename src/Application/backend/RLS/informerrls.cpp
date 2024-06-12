#include "informerrls.h"

InformerRLS::InformerRLS(){ /* ... */ }

void InformerRLS::getPosition(QVector3D &Point3D) const
{
    // В индексах
    Point3D = pos;
}

bool InformerRLS::isWorking() const
{
    return working;
}
