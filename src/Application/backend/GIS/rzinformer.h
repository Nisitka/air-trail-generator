#ifndef RZINFORMER_H
#define RZINFORMER_H

class RZInformer
{
public:
    RZInformer() {}

    // Кол-во дискрет с ЗО в вертикальном сегменте
    virtual int countVertZD(int idX, int idY) const = 0;
};

#endif // RZINFORMER_H
