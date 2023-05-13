#include "geoblock.h"

#include <QDebug>

geoBlock::geoBlock()
{
    remove();
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

bool geoBlock::isEarth()
{
    return earth;
}

bool geoBlock::isZD()
{
    return inZD;
}
