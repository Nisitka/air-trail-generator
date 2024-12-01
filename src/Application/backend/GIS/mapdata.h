#ifndef MAPDATA_H
#define MAPDATA_H

#include <QDataStream>

class MapData
{
public:
    MapData();

    friend QDataStream & operator<< (QDataStream& stream, const MapData& b);
    friend QDataStream & operator>> (QDataStream& stream, MapData& b);

    int W;
    int L;
    int H;

    // Размеры дискретпространства
    int lUnit = 20;
    int hUnit = 20;
};

#endif // MAPDATA_H
