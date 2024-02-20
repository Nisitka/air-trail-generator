#include "painterdatanetimage.h"

#include "rls.h"

#include <QApplication>

#include <QDebug>

#include <cmath>

double m(double v)
{
    if (v>=0) return v;
    else return -v;
}

painterDataNetImage::painterDataNetImage(Map* map, double* E_) :
    painterImage(map)
{
    E = E_;

    // изначально в углу карты
    setRect(0, 0);
}

void painterDataNetImage::generateInputData(const QString &dirSaveImg)
{
    run(); //
    saveImage(dirSaveImg);
    readyInputData();
}

void painterDataNetImage::saveImage(const QString& dirName)
{
    //img->save(dirName, "JPG", 100);

    createSubImage(QRect(idXo, idYo, 200, 200)).save(dirName, "JPG", 100);
}

QImage painterDataNetImage::createSubImage(const QRect &rect)
{
    size_t offset = rect.x() * img->depth() / 8
                  + rect.y() * img->bytesPerLine();

    return QImage(img->bits() + offset, rect.width(), rect.height(),
                  img->bytesPerLine(), img->format());
}

void painterDataNetImage::updateKrgb(double kG1_, double kG2_,
                                     double kpD1_, double kpD2_,
                                     double kB1_)
{
    kG1 = kG1_;
    kG2 = kG2_;
    kpD1 = kpD1_;
    kpD2 = kpD2_;
    kB1 = kB1_;
}

void painterDataNetImage::setRect(int idXo_, int idYo_)
{
    idXo = idXo_;
    idYo = idYo_;

    readyRect(idXo, idYo);
}

void painterDataNetImage::generateMapImg()
{
    //
    int w = map->getWidth();
    int l = map->getLength();

    *img = img->scaled(w, l);

    for (int x=0; x<w; x++)
    {
        for (int y=0; y<l; y++)
        {
            // красный
            int r = 255 * ( (double) map->getHeight(x, y)/ map->getCountLayers());

            img->setPixelColor(x, y, QColor(r, 0, 0));
        }
    }

    img->save(QApplication::applicationDirPath() + "\\mapImg.png", "PNG", 100);
}

int painterDataNetImage::matchGreen(int x, int y)
{
    // если не в кважрате прогноза
    if ((x < idXo) | (x > idXo + 200) |
        (y < idYo) | (y > idYo + 200)) return 0;

    int lXid = idXo + 100;
    int lYid = idYo + 100;

    double dX = m(lXid - x);
    double dY = m(lYid - y);
    double D = sqrt(pow(dX, 2) + pow(dY, 2)) * map->getLenBlock();

    // определение четверти точки
    int numS;
    if (x <  lXid && y <= lYid) numS = 1;
    if (x >= lXid && y <  lYid) numS = 2;
    if (x <= lXid && y >  lYid) numS = 3; // +
    if (x >  lXid && y >= lYid) numS = 4; // +

    if (*E > 180)
    {
        *E -= 360;
    }
    // угол трактории
    double e;
    //
    double dE;

    switch (numS) {
    case 1:
        e = -90 + Ray::toGrad(atan(dY / dX));

        zX = -1;
        zY = -1;
        break;
    case 2:
        e = 90 - Ray::toGrad(atan(dY / dX));

        zX = 1;
        zY = -1;
        break;
    case 3:
        e = -90 - Ray::toGrad(atan(dY / dX));

        zX = -1;
        zY = 1;
        break;
    case 4:
        e = 90 + Ray::toGrad(atan(dY / dX));

        zX = 1;
        zY = 1;
        break;
    }
    dE = m(*E - e);
    if (dE > 180)
    {
        dE = 360 - dE;
    }
    // приведенная дальность с учетом азимута
    double pD = (double) D * exp(-pow(dE, kpD1) * kpD2);

    return 255 * (1 - exp(-pow(pD, kG1) * kG2));
}

void painterDataNetImage::run()
{
    //
    int w = map->getWidth();
    int l = map->getLength();

    // информируем GUI об начале генерации образа
    startGenerateImg(w);

    *img = img->scaled(w, l);

    for (int x=0; x<w; x++)
    {
        for (int y=0; y<l; y++)
        {
            // зеленый
            int g = matchGreen(x, y);

            // красный
            int r = 255 * ( (double) map->getHeight(x, y)/ map->getCountLayers());

            // синий
            int b = 255 * ( (double) map->countZD(x, y) * kB1);
            if (b > 255) b = 255;

            img->setPixelColor(x, y, QColor(r, g, b));
        }
        readyStringDataNet(x);
    }

    finish();
}
