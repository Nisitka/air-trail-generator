#ifndef INFORMERRLS_H
#define INFORMERRLS_H

#include <QList>

#include "labelrls.h"

class InformerRLS
{
public:

    // Узнать общее кол-во РЛС
    virtual int countRLS() const = 0;

    // Получить интерфейс РЛС по id
    virtual const LabelRLS* getInfoRLS(int idRLS) const = 0;
};

#endif // INFORMERRLS_H
