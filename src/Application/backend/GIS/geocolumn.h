#ifndef GEOCOLUMN_H
#define GEOCOLUMN_H

#include <QDataStream>

//class geoGenerator;

// Столб-дискрета пространства
class GeoColumn
{
    friend class geoGenerator;
public:
    GeoColumn(int Height);
    GeoColumn();
    ~GeoColumn();

    static int getCountUnit();

    // Размер объекта класса в байтах
    static int getDataSize();

    friend QDataStream & operator<< (QDataStream& stream, const GeoColumn& c);
    friend QDataStream & operator>> (QDataStream& stream, GeoColumn& c);
    friend QDataStream & operator>> (QDataStream& stream, GeoColumn* c);

    // Работа с высотой дискреты
    void setHeight(int height);
    int getHeight() const;

    //
    void toZD(int idH);
    void removeZD(int idH);
    void removeAllZD();

    //
    bool isZD(int idH) const;
    int  countUnitZD() const;

    //
    static void setCountUnit(int);

private:

    //
    int height;
    static int maxHeight;

    //
    bool* isUnitZD;
};

Q_DECLARE_METATYPE(GeoColumn)

#endif // GEOCOLUMN_H
