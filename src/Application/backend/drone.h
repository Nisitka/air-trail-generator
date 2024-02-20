#ifndef DRONE_H
#define DRONE_H

#include <QObject>

#include "trackparametras.h"

// класс БПЛА
class Drone
{
public:
    Drone();

    trackParametras* getTracker();

private:
    // параметры траектории полета
    trackParametras* tracker;
};

#endif // DRONE_H
