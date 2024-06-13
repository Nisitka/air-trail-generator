#ifndef GEOCOLUMN_H
#define GEOCOLUMN_H

#include <QDataStream>

// Столб-дискрета пространства
class GeoColumn
{
public:
    GeoColumn(int countUnit, int Height = 0);
    GeoColumn();
    ~GeoColumn();

    friend QDataStream & operator<< (QDataStream& stream, const GeoColumn& c);
    friend QDataStream & operator>> (QDataStream& stream, GeoColumn& c);

    // Работа с высотой дискреты
    void setHeight(int height);
    int getHeight() const;

    //
    void toZD(int idH);
    void removeZD(int idH);
    void removeAllZD();

    //
    bool isZD(int idH) const;
    int countUnitZD() const;

private:

    //
    int height;
    int maxHeight;

    //
    bool* isUnitZD;
};

Q_DECLARE_METATYPE(GeoColumn)

#endif // GEOCOLUMN_H
