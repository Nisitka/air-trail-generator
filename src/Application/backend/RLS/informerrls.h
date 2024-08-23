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

    // Узнать индекс выбранной РЛС
    virtual int idCurrentRLS() const = 0;

    // Получить интерфейс выбранной РЛС
    virtual const LabelRLS* currentRLS() const = 0;
};

#endif // INFORMERRLS_H
