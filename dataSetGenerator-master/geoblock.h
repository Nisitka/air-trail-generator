#ifndef GEOBLOCK_H
#define GEOBLOCK_H

// дискрета пространства
class geoBlock
{
public:
    geoBlock();

    void remove();

    bool isZD();
    bool isEarth();

    void toZD();
    void removeZD();

    void toEarth();
    void toVoid();

private:
    bool earth;
    bool inZD;

    int countZD;
};

#endif // GEOBLOCK_H
