#ifndef GISINFORMER_H
#define GISINFORMER_H

#include <QImage>

#include "map.h"
#include "coords.h"

class GISInformer
{
public:
    GISInformer();

    virtual int getH(int idX, int idY, int units = Map::m) const = 0;
    virtual Coords getCoords(int idX, int idY) const = 0;
    virtual const QImage& getGeoImage() const = 0;
    virtual void getIdActionArea(int& idXo, int& idYo) const = 0;
};

#endif // GISINFORMER_H
