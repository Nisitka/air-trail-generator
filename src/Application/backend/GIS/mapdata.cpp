#include "mapdata.h"

MapData::MapData()
{

}

QDataStream &operator<<(QDataStream &out, const MapData &data)
{
    out << data.W << data.L << data.H << data.lUnit << data.hUnit;

    return out;
}

QDataStream &operator>>(QDataStream &in, MapData &data)
{
    in >> data.W >> data.L >> data.H >> data.lUnit >> data.hUnit;

    return in;
}
