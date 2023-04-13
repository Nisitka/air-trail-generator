#include "geoblock.h"

geoBlock::geoBlock()
{
    remove();

    inZD = false;
}

void geoBlock::removeZD()
{
    inZD = false;
}

void geoBlock::remove()
{
    earth = false;
    inZD = false;
    countZD = 0;
}

void geoBlock::toZD()
{
    //countZD++;
    inZD = true;
    //qDebug() << countZD;
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
