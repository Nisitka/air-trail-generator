#include "paintermapimage.h"

#include <QDebug>

painterMapImage::painterMapImage(Map* map) :
    painterImage(map)
{
    connect(map,  SIGNAL(updateVisual()),
            this, SLOT(run()));
    run(); // чтобы отобразить карту в исходном состоянии
}

void painterMapImage::runToRects(QRect* rects, int count)
{
    for (int i=0; i<count; i++)
    {
        runToRect(rects[i]);
        delete (rects + i);  // сразу же очищаем память от QRect
    }
}

void painterMapImage::runToRect(const QRect &rect)
{
    runToRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void painterMapImage::runToRect(int idX, int idY, int w, int h)
{
    updateSizeImage();

    QColor color;
    int cZD;

    int r;
    int g;
    int b;
    double k;

    int idXo, idYo;

    // вычисляем начальные и конечные индексы области расчета
    int W, H;
    W = idX + w;
    if (W > Wmap) W = Wmap - 1;
    H = idY + h;
    if (H > Lmap) H = Lmap - 1;

    if (idX < 0) idXo = 0;
    else idXo = idX;
    if (idY < 0) idYo = 0;
    else idYo = idY;

    // вычисление rgb каждого пикселя
    for (int i=idXo; i<W; i++)
    {
        for (int j=idYo; j<H; j++)
        {
            // вычисляется цвет по данным
            cZD = map->countZD(i, j);
            color = colorHeight(map->getHeight(i, j));
            r = color.red();
            g = color.green();
            k = 1 - ((double)cZD / 50);
            if (k < 0) k = 0;
            r *= k;
            g *= k;

            b = color.blue();
            b += 255 * ( (double) cZD / 50);
            if (b > 255) b = 255;
            color.setRed(r);
            color.setGreen(g);
            color.setBlue(b);
            img->setPixelColor(i, j, color);
        }
    }

    finish();
}

void painterMapImage::run()
{
    updateSizeImage();

    QColor color;
    int cZD;

    int r;
    int g;
    double k;

    int b;
    for (int i=0; i<Wmap; i++)
    {
        for (int j=0; j<Lmap; j++)
        {
            // вычисляется цвет по данным
            cZD = map->countZD(i, j);
            color = colorHeight(map->getHeight(i, j));
            r = color.red();
            g = color.green();
            k = 1 - ((double)cZD / 50);
            if (k < 0) k = 0;
            r *= k;
            g *= k;

            b = color.blue();
            b += 255 * ( (double) cZD / 50);
            if (b > 255) b = 255;
            color.setRed(r);
            color.setGreen(g);
            color.setBlue(b);
            img->setPixelColor(i, j, color);
        }
    }

    finish();
}

void painterMapImage::heightToColor(QColor* setColor, int height)
{
    *setColor = colorHeight(height);
}

QColor painterMapImage::colorHeight(int value)
{
    int r, g, b;

    dHeight = Hmap / colors.size();

    int id = value / dHeight;
    // если не предельный цвет
    if (id >= colors.size() - 1)
    {
        return colors[colors.size() - 1];
    }
    else
    {
        QColor currentColor = colors[id];
        QColor nextColor = colors[id + 1];

        double part = double(value%dHeight) / dHeight;

        r = currentColor.red();
        g = currentColor.green();
        b = currentColor.blue();

        r += (nextColor.red() - currentColor.red()) * part;
        g += (nextColor.green() - currentColor.green()) * part;
        b += (nextColor.blue() - currentColor.blue()) * part;

        return QColor(r, g, b);
    }
}
