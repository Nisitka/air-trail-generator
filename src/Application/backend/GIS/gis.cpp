#include "gis.h"

#include <QDebug>

GIS::GIS():
    // По умолчанию находимся в левом верхнем углу
    idXpos(0), idYpos(0)
{


    // Отвечает за работу с рельефом карты
    geoBuilder = new geoGenerator(currentW, currentH);
    connect(geoBuilder, SIGNAL(buildFinish(int,int,int)),
            this,       SLOT(setMapSize(int,int,int)));
    connect(geoBuilder, SIGNAL(buildFinish(int,int,int)),
            this,       SIGNAL(finishBuildMap(int,int,int)));

    HeightMeter* heigtMeter = this->getHeightMeter();
    RZInformer*  RZ         = geoBuilder;

    // Отвечает за отрисовку подложки
    backPainter = new painterMapImage(heigtMeter, RZ, currentW, currentH);
    connect(geoBuilder,  SIGNAL(buildFinish(int,int,int)),
            backPainter, SLOT(run()));
    connect(geoBuilder, SIGNAL(buildFinish(int,int,int)),
            this,       SLOT(initMap(int,int,int)));

    /// !!!!!!
    //geoBuilder->initMap(1000, 1000, 256);
}

RZInformer* GIS::getRZInformer() const
{
    return geoBuilder;
}

void GIS::setMapSize(int W, int L, int H)
{
    Wmap = W;
    Lmap = L;
    Hmap = H;

    qDebug() << "setMapSize: " << Wmap << Lmap << Hmap;
}

HeightMeter* GIS::getHeightMeter() const
{
    return geoBuilder;
}

RZCreator* GIS::getRZCreator() const
{
    return geoBuilder;
}

GISInformer* GIS::Informer() /* const */
{
    return this;
}

void GIS::getIdActionArea(int &idXo, int &idYo) const
{
    idXo = idXpos;
    idYo = idYpos;
}

int GIS::getH(int idX, int idY, Coords::units u) const
{
    return geoBuilder->absolute(idX, idY, u);
}

Coords GIS::getCoords(int idX, int idY) const
{
    return geoBuilder->getCoords(idX, idY);
}

const QImage& GIS::getGeoImage() const
{
    return *backPainter->getImage();
}

void GIS::setPosActionArea(int idXmap, int idYmap)
{
    int posX, posY;

    posX = idXmap - (currentW / 2);
    posY = idYmap - (currentH / 2);

    // Адоптируем все компоненты под новую область
    initActionArea(posX, posY);
}

void GIS::movePosActionArea(int dX, int dY)
{
    int posX, posY;

    posX = idXpos + dX;
    posY = idYpos + dY;

    // Адоптируем все компоненты под новую область
    initActionArea(posX, posY);
}

void GIS::initActionArea(int posX, int posY)
{
    qDebug() << "Start set pos action area: " << posX << posY;

    // Крайние положения
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX + currentW > Wmap) posX = Wmap - currentW;
    if (posY + currentH > Lmap) posY = Lmap - currentH;

    idXpos = posX;
    idYpos = posY;

    //
    geoBuilder->setPosActionArea(idXpos, idYpos);

    //
    backPainter->setPosArea(idXpos, idYpos);
    backPainter->updateFull();

    // Сигнализируем об готовности новой области
    changedActionArea(idXpos, idYpos);
}

void GIS::openMap(const QString &dirNameFile)
{
    geoBuilder->openMap(dirNameFile);
}

void GIS::initMap(int W, int L, int H)
{
    setMapSize(W, L, H);

    // Сдвигаем область активных действий в крайнее левое верхнее положение
    setPosActionArea(0,0);
}

void GIS::loadTerrain(const QString &dirNameFile)
{
    geoBuilder->loadTerrain(dirNameFile);
    initActionArea(0, 0);
}

void GIS::setDefaultMap()
{
    geoBuilder->buildFlatMap(currentW, currentH);
    initActionArea(0, 0);
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
    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    geoBuilder->editEarth(idXo, idYo, R, R, 1);

    backPainter->runToRect(QRect(idXo, idYo, R, R));

    changedMap(idXo, idYo, R, R);
}

void GIS::downEarth(int idX, int idY, int R)
{
    int idXo = idX - (R / 2);
    int idYo = idY - (R / 2);
    geoBuilder->editEarth(idXo, idYo, R, R, 3, geoGenerator::down);

    backPainter->runToRect(QRect(idXo, idYo, R, R));

    changedMap(idXo, idYo, R, R);
}
