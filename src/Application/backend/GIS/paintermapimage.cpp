#include "paintermapimage.h"

#include <QDebug>

painterMapImage::painterMapImage(HeightMeter* Height):
    Height(Height)
{
    dHeight = 200 / colors.size(); /// !!!!! Максимальное кол-во дискрет высоты
                                   /// делится на кол-во цветов
}

void painterMapImage::getMapImage(const QRect &area, QImage &img)
{
    getMapImage(area.x(), area.y(), area.width(), area.height(), img);
}

void painterMapImage::getMapImage(int idXo, int idYo, int W, int H, QImage &img)
{
    img = QImage(W, H, QImage::Format_RGB32);

    // Вычисление rgb каждого пикселя
    QColor color;
    for (int X=0; X<W; X++)
    {
        for (int Y=0; Y<H; Y++)
        {
            // Вычисляется цвет по данным
            color = colorHeight(Height->absolute(idXo+X, idYo+Y, Coords::id));

            //
            img.setPixelColor(X, Y, color);
            //qDebug() << img;
        }
    }
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
