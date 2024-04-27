#include "gis.h"

GIS::GIS()
{
    //
    map = new Map;

    //
    backPainter = new painterMapImage(map);
    backgroundImg = backPainter->getImage();

    //
    geoBuilder = new geoGenerator(map);
}

void GIS::setDefaultMap()
{
    geoBuilder->buildFlatMap();
    backPainter->updateFull();

    int W, L, H;
    map->getSize(W, L, H);

    finishBuildMap(W, L, H);
}

QImage* GIS::getBackgroundImg()
{
    return backgroundImg;
}

//////////
Map* GIS::getMap()
{
    return map;
}

void GIS::updateFromRect(const QRect &rect)
{
    backPainter->runToRect(rect);
}

void GIS::updateFromRect(int idX, int idY, int w, int h)
{
    backPainter->runToRect(idX, idY, w, h);
}

void GIS::updateFromRects(QRect *rects, int countS)
{
    backPainter->runToRects(rects, countS);
}

void GIS::upEarth(int idX, int idY, int R)
{
    map->upEarth(idX, idY, R);

    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    backPainter->runToRect(QRect(idXo, idYo, R, R));

    changedMap(idXo, idYo, R, R);
}

void GIS::downEarth(int idX, int idY, int R)
{
    map->downEarth(idX, idY, R);

    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    backPainter->runToRect(QRect(idXo, idYo, R, R));

    changedMap(idXo, idYo, R, R);
}
