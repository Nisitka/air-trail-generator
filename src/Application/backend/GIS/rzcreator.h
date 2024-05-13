#ifndef RZCREATOR_H
#define RZCREATOR_H

#include <QVector3D>

// Позволяет изменять значения РЛ сигнала в дискретах
class RZCreator
{
public:
    RZCreator() {}

    virtual void toZD(const QVector3D& idBlock) const = 0;
    virtual void clearZD(const QVector3D& idBlock) const = 0;
};

#endif // RZCREATOR_H
