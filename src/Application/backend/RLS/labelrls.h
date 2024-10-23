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

    // Получить данные об ДН антены
    virtual void getGraphicData(QVector <double>& X,
                        QVector <double>& Y) const = 0;

protected:

    // Включена ли РЛС
    bool working;

    // Точка стояния РЛС
    QVector3D pos;

    // Позывной
    QString name;
};

#endif // LABELRLS_H
