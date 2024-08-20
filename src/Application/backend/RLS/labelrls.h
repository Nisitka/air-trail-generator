#ifndef LABELRLS_H
#define LABELRLS_H

#include <QVector3D>
#include <QString>

//
class LabelRLS
{
public:
    LabelRLS();

    // Позиция РЛС в пространстве
    void getPosition(QVector3D& Point3D) const;

    // Узнать, работает ли РЛС
    bool isWorking() const;

    // Узнать позывной
    QString getName() const;

protected:

    // Включена ли РЛС
    bool working;

    // Точка стояния РЛС
    QVector3D pos;

    // Позывной
    QString name;
};

#endif // LABELRLS_H
