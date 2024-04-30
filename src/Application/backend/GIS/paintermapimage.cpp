#include "paintermapimage.h"

#include <QDebug>

painterMapImage::painterMapImage(Map* map_, int W, int H):
    map(map_)
{
    // Сразу инициализируем изображение
    img = new QImage(W, H, QImage::Format_RGB32);

    //
    numW = W;
    numL = H;

    // По умолчанию
    idXo = 0;
    idYo = 0;
}

void painterMapImage::setPosArea(int idXo_, int idYo_)
{
    // id левого верхнего угла
    idXo = idXo_;
    idYo = idYo_;

    // id нижнего правого угла
    idXlast = idXo + numW;
    idYlast = idYo + numL;
}

QImage* painterMapImage::getImage()
{
    return img;
}

void painterMapImage::updateFull()
{
    Hmap = map->getCountLayers();
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

void painterMapImage::runToRect(int idX, int idY, int w, int h)
{
    // Если не попадает в область, то ничего не делаем
    if (idX > idXlast | idY > idYlast) return;

    QColor color;
    int cZD;

    int r;
    int g;
    int b;
    double k;

    // Вычисляем начальные и конечные индексы области расчета
    int W, H;
    W = idX + w;
    if (W > idXlast) W = idXlast;
    H = idY + h;
    if (H > idYlast) H = idYlast;

    if (idX < idXo) idX = idXo;
    if (idY < idYo) idY = idYo;

    // Вычисление rgb каждого пикселя
    for (int i=idX; i<W; i++)
    {
        for (int j=idY; j<H; j++)
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

            //
            img->setPixelColor(i - idXo, j - idYo,
                               color);
        }
    }
}

void painterMapImage::run()
{
    //
    runToRect(idXo, idYo, numW, numL);
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
