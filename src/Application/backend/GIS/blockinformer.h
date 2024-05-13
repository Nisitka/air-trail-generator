#ifndef BLOCKINFORMER_H
#define BLOCKINFORMER_H

#include "./geoblock.h"

// Предоставляет информацию об дискретах карты
class BlockInformer
{
public:
    BlockInformer() {}

    //
    virtual const geoBlock& block(int idX, int idY, int idH) const = 0;
};

#endif // BLOCKINFORMER_H
