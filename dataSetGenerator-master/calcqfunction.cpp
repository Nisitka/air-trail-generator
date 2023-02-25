#include "calcqfunction.h"

#include "ray.h"
#include <cmath>

#include <QDebug>

double m(double v)
{
    if (v>=0) return v;
    else return -v;
}

calcQFunction::calcQFunction(Map* map_):
    painterImage(map_)
{
    colorMin = new QColor(81, 0, 0);
    colorMax = new QColor(192, 254, 63);
}

void calcQFunction::run()
{
    updateSizeImage();

    // информируем о начале обсчета
    calcStart(Wmap);

    Xo = Wmap / 2;
    Yo = Lmap / 2;

    for (int x=0; x<Wmap; x++)
    {
        for (int y=0; y<Lmap; y++)
        {
            img->setPixelColor(x, y, scoreToColor(Q(x, y, angleE)));
        }
        readySigment(x);
    }

    // численное значение также сделать!!!
    img->setPixelColor(Xo, Yo, *colorMin);

    // информируем об завершении обсчета
    finish();
}

void calcQFunction::calculate(double angleE_)
{
    angleE = angleE_;

    run();
}

int calcQFunction::Q(int idX, int idY, double E)
{
    //int lenBlock = ;

    double dX = m(Xo - idX);
    double dY = m(Yo - idY);
    double D = sqrt(pow(dX, 2) + pow(dY, 2)) * map->getLenBlock();

    // определение четверти точки
    int numS;
    if (idX < Xo && idY <= Yo) numS = 1;
    if (idX >= Xo && idY < Yo) numS = 2;
    if (idX <= Xo && idY > Yo) numS = 3; // +
    if (idX > Xo && idY >= Yo) numS = 4; // +

    if (E > 180)
    {
        E -= 360;
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
    dE = m(E - e);
    if (dE > 180)
    {
        dE = 360 - dE;
    }
    double pD = (double) D * (1 - (double)dE/180); // дальность с учетом азимута

    // кол-во высот находящихся в ЗО по пути в точку
    int countZD = 0;

    // соедняя высота по пути в точку
    double mH = 0;
    int countB = 0;

    double L = 0;
    double dL = Ray::mSIZE;
    int x;
    int y;

    double a = atan(dY / dX);
    while (L < D)
    {
        x = (double) zX * (L * cos(a)) / Ray::mSIZE;
        y = (double) zY * (L * sin(a)) / Ray::mSIZE;

        mH += map->getHeight(Xo + x, Yo + y) * Ray::mH;
        countB++;

        countZD += map->countZD(Xo + x, Yo + y);

        L += dL;
    }
    //qDebug() << mH;
    mH = (double) mH / countB;
    //qDebug() << mH;

    //qDebug() << countZD;
    double qF = 0;
    qF += pD*kD;
    qF -= countZD*kZD;
    qF -= mH*kH;

    if (qF < 0) return 0;
    else
    {
        return qF;
    }
}

QColor calcQFunction::scoreToColor(int score)
{
    double k = 1 - exp(-score * 0.01);

    int r, g, b;
    r = colorMin->red();
    g = colorMin->green();
    b = colorMin->blue();

    r += (colorMax->red() - r) * k;
    g += (colorMax->green() - g) * k;
    b += (colorMax->blue() - b) * k;

    return QColor(r, g, b);
}
