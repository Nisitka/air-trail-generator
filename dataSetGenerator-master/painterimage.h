#ifndef PAINTERIMAGE_H
#define PAINTERIMAGE_H

#include <QObject>
#include <QImage>

#include "map.h"

class painterImage : public QObject
{
    Q_OBJECT
signals:
    void finish();

public slots:
    // запуск отрисовки изображения
    virtual void run() = 0;

public:
    painterImage(Map* map);

    //
    QImage* getImage();

protected:
    void updateSizeImage();

    QImage* img;
    Map* map;

    int Wmap;
    int Lmap;
    int Hmap;

    void updateSizeMap();
};

#endif // PAINTERIMAGE_H
