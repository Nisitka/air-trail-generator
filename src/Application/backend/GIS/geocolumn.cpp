#include "geocolumn.h"

int GeoColumn::maxHeight;

GeoColumn::GeoColumn(): height(0)
{
    isUnitZD = new bool[maxHeight];
    removeAllZD();
}

QDataStream &operator<<(QDataStream &out, const GeoColumn &c)
{
    out << c.getHeight();

    int count = GeoColumn::getCountUnit();
    for (int i=0; i<count; i++)
        out << c.isZD(i);

    return out;
}

QDataStream &operator>>(QDataStream &in, GeoColumn &c)
{
    int height;

    in >> height;

    int count = GeoColumn::getCountUnit();
    bool zd;
    for (int i=0; i<count; i++)
    {
        in >> zd;
        if (zd) c.toZD(i);
    }

    c.setHeight(height);

    return in;
}
QDataStream &operator>>(QDataStream &in, GeoColumn* c)
{
    int height;

    in >> height;

    int count = GeoColumn::getCountUnit();
    bool zd;
    for (int i=0; i<count; i++)
    {
        in >> zd;
        if (zd) c->toZD(i);
    }

    c->setHeight(height);

    return in;
}

void GeoColumn::setCountUnit(int count)
{
    maxHeight = count;
}

int GeoColumn::getCountUnit()
{
    return maxHeight;
}

GeoColumn::GeoColumn(int Height): height(Height)
{
    //
    isUnitZD = new bool[maxHeight];
    removeAllZD();
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
