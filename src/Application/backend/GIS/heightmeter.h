#ifndef HEIGHTMETER_H
#define HEIGHTMETER_H

#include "coords.h"

class HeightMeter
{
public:
    HeightMeter() {}

    // Обсолютная высота
    virtual int absolute(int idX, int idY,
                         Coords::units u = Coords::m) const = 0;

    // Максимально возможная высота
    virtual int max(Coords::units u = Coords::m) const = 0;


    virtual int lenghtBlock() const = 0;
    virtual int heightBlock() const = 0;

};

#endif // HEIGHTMETER_H
