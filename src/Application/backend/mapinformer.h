#ifndef MAPINFORMER_H
#define MAPINFORMER_H

#include "./MapFile/mapfile.h"

// Класс интерфейс по общей инф. об картах
class MapInformer
{
public:
    MapInformer() {}

    virtual int count() const = 0;
};

#endif // MAPINFORMER_H
