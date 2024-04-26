#include "painterimage.h"

#include <QDebug>

painterImage::painterImage(Map* map_)
{
    map = map_;

    // сразу инициализируем изображение
    img = new QImage(map->getWidth(), map->getLength(),
                     QImage::Format_RGB32);

    //qDebug() << *img << "img";
}

void painterImage::updateSizeMap()
{
    map->getSize(Wmap, Lmap, Hmap);
    updateSizeImage();
}

void painterImage::updateSizeImage()
{
    *img = img->scaled(Wmap, Lmap); // и самого изображения соответсвенно
    //qDebug() << *img << "img!";
    resized();
}

QImage* painterImage::getImage()
{
    qDebug() << *img << "img!1";
    return img;
}
