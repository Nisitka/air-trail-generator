#include "gis.h"

#include <QDebug>

GIS::GIS()
{
    //
    map = new Map;

    // По умолчанию находимся в левом верхнем углу
    idXpos = 0; idYpos = 0;

    //
    backPainter = new painterMapImage(map, currentW, currentH);
    backPainter->setPosArea(idXpos, idYpos);
    backgroundImg = backPainter->getImage();

    //
    geoBuilder = new geoGenerator(map);
}

void GIS::setPosActionArea(int idXmap, int idYmap)
{
    int posX, posY;

    posX = idXmap - (currentW / 2);
    posY = idYmap - (currentH / 2);

    // Крайние положения
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX + currentW > Wmap) posX = Wmap - currentW;
    if (posY + currentH > Lmap) posY = Lmap - currentH;

    idXpos = posX;
    idYpos = posY;

    // Адоптируем все компоненты под новую область
    initActionArea();

    // Сигнализируем об готовности новой области
    changedActionArea(idXpos, idYpos);
}

void GIS::movePosActionArea(int dX, int dY)
{
    int posX, posY;

    posX = idXpos + dX;
    posY = idYpos + dY;

    // Крайние положения
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX + currentW > Wmap) posX = Wmap - currentW;
    if (posY + currentH > Lmap) posY = Lmap - currentH;

    idXpos = posX;
    idYpos = posY;

    // Адоптируем все компоненты под новую область
    initActionArea();

    // Сигнализируем об готовности новой области
    changedActionArea(idXpos, idYpos);
}

void GIS::initActionArea()
{
    qDebug() << idXpos << idYpos;

    backPainter->setPosArea(idXpos, idYpos);
    backPainter->updateFull();
}

void GIS::buildHmatrix()
{
    Hmatrix = new QVector<QVector<int>*>;
    for (int i=0; i<currentH; i++)
    {
        Hmatrix->append(new QVector<int>);
        for (int j=0; j<currentW; j++)
        {
            Hmatrix->last()->append(0);
        }
    }
}

QVector<QVector<int> *>* GIS::getHmatrix()
{
    return Hmatrix;
}

void GIS::setDefaultMap()
{
    geoBuilder->buildFlatMap();
    backPainter->updateFull();

    int H;
    map->getSize(Wmap, Lmap, H);

    finishBuildMap(Wmap, Lmap, H);
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

    changedMap(rect.x(),     rect.y(),
               rect.width(), rect.height());
}

void GIS::updateFromRect(int idX, int idY, int w, int h)
{
    backPainter->runToRect(idX, idY, w, h);

    changedMap(idX, idY, w, h);
}

void GIS::updateFromRects(QRect *rects, int countS)
{
    backPainter->runToRects(rects, countS);

    changedMap();
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
