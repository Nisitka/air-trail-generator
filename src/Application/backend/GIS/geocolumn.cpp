#include "geocolumn.h"

GeoColumn::GeoColumn(): maxHeight(200), height(0){ /* ... */}

QDataStream &operator<<(QDataStream &out, const GeoColumn &c)
{
    out << c.getHeight();

    return out;
}

QDataStream &operator>>(QDataStream &in, GeoColumn &c)
{
    int height;

    in >> height;

    c.setHeight(height);

    return in;
}

GeoColumn::GeoColumn(int countUnit, int Height): height(Height)
{
    //
    isUnitZD = new bool[countUnit];

    maxHeight = countUnit;
}

void GeoColumn::removeAllZD()
{
    for (int i=0; i<maxHeight; i++)
        isUnitZD[i] = false;
}

void GeoColumn::removeZD(int idH)
{
    isUnitZD[idH] = false;
}

int GeoColumn::countUnitZD() const
{
    int count = 0;

    for (int i=0; i<maxHeight; i++)
        if (isUnitZD[i]) count++;

    return count;
}

void GeoColumn::toZD(int id)
{
    isUnitZD[id] = true;
}

bool GeoColumn::isZD(int id) const
{
    return isUnitZD[id];
}

void GeoColumn::setHeight(int h)
{
    height = h;
}

int GeoColumn::getHeight() const
{
    return height;
}

GeoColumn::~GeoColumn()
{
    delete [] isUnitZD;
}
