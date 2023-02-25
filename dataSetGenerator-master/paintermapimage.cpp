#include "paintermapimage.h"

painterMapImage::painterMapImage(Map* map) :
    painterImage(map)
{
    run(); // чтобы отобразить карту в исходном состоянии
}

void painterMapImage::run()
{
    updateSizeImage();

    for (int i=0; i<Wmap; i++)
    {
        for (int j=0; j<Lmap; j++)
        {
            // вычисляется цвет по данным
            if (map->countZD(i, j) == 0)
            {
                img->setPixelColor(i, j, colorHeight(map->getHeight(i, j)));
            }
            else
            {
                img->setPixelColor(i, j, QColor(17, 85, 242));
            }
        }
    }

    finish();
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
