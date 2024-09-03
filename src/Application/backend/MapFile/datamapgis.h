#ifndef DATAMAPGIS_H
#define DATAMAPGIS_H

#endif // DATAMAPGIS_H

///
#include "../GIS/geoarea.h"

class DataMapGIS
{
public:

    //
    virtual void getSize(int& W, int& L, int& H) const = 0;

    //
    virtual int lenghtUnit() const = 0;
    virtual int heightUnit() const = 0;

    //
    virtual void getColumn(GeoColumn* column,
                           int idX, int idY) const = 0;

    //
    virtual int getHeight(int idX, int idY) const = 0;
    virtual void setHeight(int idX, int idY,
                           int height) = 0;

    //
    virtual bool isZD(int idX, int idY, int idH) const = 0;
    virtual void setZD(int idX, int idY, int idH,
                       bool statZD) = 0;
};
