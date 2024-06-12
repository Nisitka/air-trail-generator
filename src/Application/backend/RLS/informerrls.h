#ifndef INFORMERRLS_H
#define INFORMERRLS_H

#include <QVector3D>

class InformerRLS
{
public:
    InformerRLS();

    // Позиция РЛС в пространстве
    void getPosition(QVector3D& Point3D) const;

    // Узнать, работает ли РЛС
    bool isWorking() const;

protected:

    // Включена ли РЛС
    bool working;

    // Точка стояния РЛС
    QVector3D pos;
};

#endif // INFORMERRLS_H
