#include "buildertraildrones.h"


#include <QDebug>

#include <cmath>
#include "ray.h"

builderTrailDrones::builderTrailDrones(Map* map): map(map)
{ 

}

void builderTrailDrones::startPredictTrail(Drone* drone,
                                           int idXa, int idYa, int idXb_, int idYb_)
{
    curDrone = drone;


}
