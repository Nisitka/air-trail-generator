#include "paintermapimage.h"

#include <QDebug>

#include <QApplication>

#include <QMatrix>

painterMapImage::painterMapImage(Map* map_):
    map(map_)
{
    // Сразу инициализируем изображение
    img = new QImage(3, 3, QImage::Format_RGB32);

    // По умолчанию на всю карту
    idXo = 0;
    idYo = 0;
}

QImage* painterMapImage::getImage()
{
    return img;
}

void painterMapImage::updateSize()
{
    map->getSize(Wmap, Lmap, Hmap);
    *img = img->scaled(Wmap, Lmap); // и самого изображения соответсвенно
}

void painterMapImage::updateFull()
{
    updateSize();

    run();
}

void painterMapImage::runToRects(QRect* rects, int count)
{
    for (int i=0; i<count; i++)
    {
        runToRect(rects[i]);

    }

    delete [] rects;  // сразу же очищаем память от QRect
}

void painterMapImage::runToRect(const QRect &rect)
{
    runToRect(rect.x(), rect.y(), rect.width(), rect.height());
}

//QImage* painterMapImage::buildImageEarth(const QRect &rect)
//{
//    // инициализация изображения текстуры
//    int W = rect.width();
//    int L = rect.height();

//    QImage* texture = new QImage(W, L, img->format());

//    QColor color;
//    for (int x=0; x<W; x++)
//    {
//        for (int y=0; y<L; y++)
//        {
//            // вычисляется цвет по данным
//            color = colorHeight(map->getHeight(idXo + x, idYo + y));

//            texture->setPixelColor(x, y, color);
//        }
//    }

//    return texture;
//}

void painterMapImage::runToRect(int idX, int idY, int w, int h)
{
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

    // Вычисление rgb каждого пикселя
    for (int i=idXo; i<W; i++)
    {
        for (int j=idYo; j<H; j++)
        {
            // Вычисляется цвет по данным
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
}

void painterMapImage::run()
{
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
}

QColor painterMapImage::colorHeight(int value)
{
    int r, g, b;

    dHeight = Hmap / colors.size();

    int id = value / dHeight;
    // если предельный цвет
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
