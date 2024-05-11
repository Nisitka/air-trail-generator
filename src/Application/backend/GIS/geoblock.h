#ifndef GEOBLOCK_H
#define GEOBLOCK_H

#include <QDataStream>

// Дискрета пространства
class geoBlock
{
public:
    geoBlock();

    friend QDataStream & operator<< (QDataStream& stream, const geoBlock& b);
    friend QDataStream & operator>> (QDataStream& stream, geoBlock& b);

    void setValues(const geoBlock& b);

    void remove();

    bool isZD()    const;
    bool isEarth() const;

    void toZD();
    void removeZD();

    void toEarth();
    void toVoid();

    void setEarth(bool);
    void setZD(bool);

private:
    bool earth;
    bool inZD;

};

Q_DECLARE_METATYPE(geoBlock)

#endif // GEOBLOCK_H
