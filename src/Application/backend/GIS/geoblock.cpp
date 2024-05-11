#include "geoblock.h"

#include <QDebug>

geoBlock::geoBlock()
{
    remove();
}

void geoBlock::setValues(const geoBlock &b)
{
    earth = b.isEarth();
    inZD  = b.isZD();
}

QDataStream &operator<<(QDataStream &out, const geoBlock &a)
{
    out << a.isEarth() << a.isZD();

    return out;
}

QDataStream &operator>>(QDataStream &in, geoBlock &a)
{
    bool earth;
    bool ZD;

    in >> earth >> ZD;

    a.setEarth(earth);
    a.setZD(ZD);

    return in;
}

void geoBlock::setEarth(bool v)
{
    earth = v;
}
void geoBlock::setZD(bool v)
{
    inZD = v;
}

void geoBlock::removeZD()
{
    inZD = false;
}

void geoBlock::remove()
{
    earth = false;
    inZD = false;
}

void geoBlock::toZD()
{
    inZD = true;
}

void geoBlock::toEarth()
{
    earth = true;
}

void geoBlock::toVoid()
{
    earth = false;
}

bool geoBlock::isEarth() const
{
    return earth;
}

bool geoBlock::isZD() const
{
    return inZD;
}
