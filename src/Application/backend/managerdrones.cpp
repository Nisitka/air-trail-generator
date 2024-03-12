#include "managerdrones.h"

managerDrones::managerDrones()
{

}

void managerDrones::createDrone()
{
    drones.append(new Drone);
}

void managerDrones::removeDrone(int idDrone)
{
    drones.removeAt(idDrone);
}
