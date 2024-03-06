#ifndef DRONE_H
#define DRONE_H

#include "ray.h"

// класс БПЛА
class Drone
{
public:
    // Установка пар-ов прогноза в области
    void setOptPredict(int cHorRay, int cVerRay,
                       int longRay); // Длина лучей

    Drone(int countHorRay, int countVerRay, int longRay);

private:

    // Кол-во лучей
    int countHorRay; // горизонтали
    int countVerRay; // вертикали

    // Длина лучей
    int longRay;
};

#endif // DRONE_H
