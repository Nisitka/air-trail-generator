#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "../GIS/mapdata.h"

#include <QString>

class MapCreator
{
public:

    // Создать карту
    virtual void create(const QString& path, MapData data) = 0;

    // Открыть карту
    virtual void open(const QString& path) = 0;
};

#endif // MAPCREATOR_H
