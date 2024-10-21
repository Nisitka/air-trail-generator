#include "paintermapimage.h"

#include <QDebug>

painterMapImage::painterMapImage(HeightMeter* Height,
                                 int W, int H):
    Height(Height),
    numW(W), numL(H)
{
    // Сразу инициализируем изображение
    img = new QImage(numW, numL, QImage::Format_RGB32);

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
    Hmap = Height->max(Coords::id);
    dHeight = Hmap / colors.size();

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
    ///qDebug() << "Painter run to rect!";

    // Если не попадает в область, то ничего не делаем
    if (idX > idXlast || idY > idYlast) return;

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
    for (int X=idX; X<W; X++)
    {
        for (int Y=idY; Y<H; Y++)
        {
            // Вычисляется цвет по данным
            color = colorHeight(Height->absolute(X, Y, Coords::id));

            //
            img->setPixelColor(X - idXo, Y - idYo,
                               color);
        }
    }
}

void painterMapImage::run()
{
    qDebug() << "RUN map-Painter ";

    //
    runToRect(idXo, idYo, numW, numL);
}

QColor painterMapImage::colorHeight(int value)
{
    int r, g, b;

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
