#include "calcqfunction.h"

#include "ray.h"
#include <cmath>

#include <QDebug>

double calcQFunction::m(double v)
{
    if (v>=0) return v;
    else return -v;
}

calcQFunction::calcQFunction(Map* map_, double* E):
    painterImage(map_)
{
    colorMin = new QColor(81, 0, 0);
    colorMax = new QColor(192, 254, 63);

    file = new QFile; // чтобы можно было очистить память
    outData = new QTextStream(file);

    angleE = E;

    // изначально левый верхний угол
    setRect(0, 0);
}

void calcQFunction::setRect(int idXo_, int idYo_)
{
    idXo = idXo_;
    idYo = idYo_;
}

void calcQFunction::run()
{
    updateSizeImage();

    maxScore = maxD + maxH;

    // информируем о начале обсчета
    calcStart(200);

    Xo = idXo + 100;
    Yo = idYo + 100;

    // сначала красим все в черный
    for (int y=0; y<Lmap; y++)
    {
        for (int x=0; x<Wmap; x++)
        {
            img->setPixelColor(x, y, Qt::black);
        }
    }

    // обсчитываем значения ЦФ в обсласти
    int score;
    for (int y=idYo; y<idYo+200; y++)
    {
        for (int x=idXo; x<idXo+200; x++)
        {
            if (x == Xo & y == Yo)
            {
                score = 0;
            }
            else
            {
                score = Q(x, y, *angleE);
            }

            // добвляем значение ЦФ в файл
            *outData << score << " ";

            // красим пиксель
            img->setPixelColor(x, y, scoreToColor(score));
        }
        *outData << "\n";

        readySigment(y - idYo);
    }

    // информируем об завершении обсчета
    finish();
}

void calcQFunction::calculate()
{
    run();
}

void calcQFunction::calculate(const QString &dir, int numFile)
{
    delete file;
    file = new QFile(dir + "/valQFun_" + QString::number(numFile) + ".txt");
    file->open(QIODevice::WriteOnly | QIODevice::Text);

    delete outData;
    outData = new QTextStream(file);

    run();
}

int calcQFunction::Q(int idX, int idY, double E)
{
    double dX = m(Xo - idX);
    double dY = m(Yo - idY);
    double D = sqrt(pow(dX, 2) + pow(dY, 2)); // * map->getLenBlock();

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

    // кол-во высот находящихся в ЗО по пути в точку
    int countZD = 0;

    // средняя высота по пути в точку
    double mH = 0;
    int countB = 1;

    double L = 0;
    double dL = Ray::mSIZE;
    int x;
    int y;

    double a = atan(dY / dX);
    double rD = D * map->getLenBlock();
    while (L < rD)
    {
        x = (double) zX * (L * cos(a)) / Ray::mSIZE;
        y = (double) zY * (L * sin(a)) / Ray::mSIZE;

        mH += map->getHeight(Xo + x, Yo + y); // * Ray::mH;
        countB++;

        countZD += map->countZD(Xo + x, Yo + y);

        L += dL;
    }
    //qDebug() << mH;
    mH = (double) mH / countB;
    double mZD = (double) countZD / countB;
    //qDebug() << mH;

    //qDebug() << countZD;
    double qF = 0;
    qF += F_D(D, dE)*maxD;
    qF -= F_ZD(mZD)*maxZD;
    qF += F_H(mH)*maxH;

    if (qF < 0) return 0;
    return qF;
}

double calcQFunction::F_D(int D, double dE)
{
    double kD = ((double) 1 / (1 + exp((double)-D/40)) - 0.5) * 2;
    double pD = (double) D * kD * exp(-pow(dE + 3, kpD1) * kpD2);

    return (1 - exp(-pow(pD, kG1) * kG2));
}

double calcQFunction::F_ZD(double mZD)
{
    return 1 - exp(-mZD*0.3);
}

double calcQFunction::F_H(int mH)
{
    return exp(-mH*0.05);
}

QColor calcQFunction::scoreToColor(int score)
{
    if (score == 0) return *colorMin; // для быстроты расчета

    double e = exp(-((double)score * 12 / maxScore - 5));
    double k = (double) 1 / (1 + e);

    int r, g, b;
    r = colorMin->red();
    g = colorMin->green();
    b = colorMin->blue();

    r += (colorMax->red() - r) * k;
    g += (colorMax->green() - g) * k;
    b += (colorMax->blue() - b) * k;

    return QColor(r, g, b);
}
