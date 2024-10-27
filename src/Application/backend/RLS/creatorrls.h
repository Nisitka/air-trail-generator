#ifndef CREATORRLS_H
#define CREATORRLS_H

#include "rls.h"

class CreatorRLS
{
public:
    CreatorRLS();

    // создать новую РЛС
    virtual void addRLS(LabelRLS) = 0;
};

#endif // CREATORRLS_H
