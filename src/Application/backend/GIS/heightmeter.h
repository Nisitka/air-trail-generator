#ifndef HEIGHTMETER_H
#define HEIGHTMETER_H

#include "map.h"

class HeightMeter
{
public:
    HeightMeter();

    //
    virtual int absolute(int idX, int idY,
                         Map::units u = Map::m) const = 0;

};

#endif // HEIGHTMETER_H
