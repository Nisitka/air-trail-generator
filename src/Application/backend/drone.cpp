#include "drone.h"

Drone::Drone(int cHorR, int cVerR, int L):
    countHorRay(cHorR), countVerRay(cVerR), longRay(L)
{

}

void Drone::setOptPredict(int cHorRay, int cVerRay, int L)
{
    countHorRay = cHorRay;
    countVerRay = cVerRay;
    longRay = L;
}
