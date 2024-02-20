#include "trackparametras.h"

#include <QDebug>

trackParametras::trackParametras()
{
    E = 0.0;
}

void trackParametras::setE(double E_)
{
    E = E_;
}

double* trackParametras::getE()
{
    return &E;
}
