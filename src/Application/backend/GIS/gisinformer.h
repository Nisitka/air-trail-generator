#ifndef GISINFORMER_H
#define GISINFORMER_H

#include <QImage>

#include "coords.h"

class GISInformer
{
public:
    GISInformer() {}

    virtual int getH(int idX, int idY, Coords::units = Coords::m) const = 0;
    virtual Coords getCoords(int idX, int idY) const = 0;
};

#endif // GISINFORMER_H
