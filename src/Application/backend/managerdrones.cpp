#include "managerdrones.h"

managerDrones::managerDrones()
{

}

void managerDrones::createDrone(int cHorRay, int cVerRay, int L)
{
    drones.append(new Drone(cHorRay, cVerRay, L));
}

void managerDrones::removeDrone(int idDrone)
{
    drones.removeAt(idDrone);
}
