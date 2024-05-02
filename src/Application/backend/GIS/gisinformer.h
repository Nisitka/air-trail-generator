#ifndef GISINFORMER_H
#define GISINFORMER_H

#include <QImage>

#include "coords.h"

class GISInformer
{
public:
    GISInformer();

    // Единицы измерения
    enum units {id, m}; // Дискреты карты, метры

    virtual int getH(int idX, int idY) const = 0;
    virtual Coords* getCoords(int idX, int idY) const = 0;
    virtual const QImage& getGeoImage() const = 0;
};

#endif // GISINFORMER_H
