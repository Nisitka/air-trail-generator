#include "painterimage.h"

#include <QDebug>

painterImage::painterImage(Map* map_)
{
    map = map_;

    // сразу инициализируем изображение
    img = new QImage(map->getWidth(), map->getLength(),
                     QImage::Format_RGB32);
}

void painterImage::updateSizeMap()
{
    map->getSize(Wmap, Lmap, Hmap);
}

void painterImage::updateSizeImage()
{
    updateSizeMap(); // обновляем размеры карты
    *img = img->scaled(Wmap, Lmap); // и самого изображения соответсвенно
}

QImage* painterImage::getImage()
{
    return img;
}
