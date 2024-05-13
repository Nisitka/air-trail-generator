#ifndef HEIGHTMETER_H
#define HEIGHTMETER_H

#include "map.h"

class HeightMeter
{
public:
    HeightMeter() {}

    // Обсолютная высота
    virtual int absolute(int idX, int idY,
                         Map::units u = Map::m) const = 0;

    // Максимально возможная высота
    virtual int max(Map::units u = Map::m) const = 0;

};

#endif // HEIGHTMETER_H
