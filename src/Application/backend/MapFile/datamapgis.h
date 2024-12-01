#ifndef DATAMAPGIS_H
#define DATAMAPGIS_H

#endif // DATAMAPGIS_H

class DataMapGIS
{
public:

    //
    virtual void getSize(int& W, int& L, int& H) const = 0;

    //
    virtual int lenghtUnit() const = 0;
    virtual int heightUnit() const = 0;

    //
    virtual int getHeight(int idX, int idY) const = 0;
};
