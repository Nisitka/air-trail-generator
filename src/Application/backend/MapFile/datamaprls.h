#ifndef DATAMAPRLS_H
#define DATAMAPRLS_H

#include <QStringList>

class DataMapRLS
{
public:
    DataMapRLS() {/* ... */}

    // Получить директории для загрузки РЛС
    virtual void getPathAllRLS(QStringList& listPath) const = 0;
};


#endif // DATAMAPRLS_H
