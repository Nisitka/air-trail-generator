#include "drone.h"

Drone::Drone()
{
    tracker = new trackParametras;
}

trackParametras* Drone::getTracker()
{
    return tracker;
}
