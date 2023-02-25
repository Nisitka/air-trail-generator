#include "painterdatanetimage.h"

#include "rls.h"

painterDataNetImage::painterDataNetImage(Map* map) :
    painterImage(map)
{

}

void painterDataNetImage::run()
{
    int w = map->getWidth();
    int l = map->getLength();

    *img = img->scaled(w, l);

    for (int x=0; x<w; x++)
    {
        for (int y=0; y<l; y++)
        {
            int r = 0;
            int g = 0;
            int b = 0;

            r = 255 * ( (double) map->getHeight(x, y)/ map->getCountLayers());
            b = 255 * ( (double) map->countZD(x, y) / Kblue);
            if (b > 255) b = 255;

            img->setPixelColor(x, y, QColor(r, g, b));
        }
    }

    finish();
}
