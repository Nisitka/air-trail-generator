#ifndef LABELRLS_H
#define LABELRLS_H

#include <QVector3D>
#include <QVector>
#include <QPointF>
#include <QString>

//
class LabelRLS
{
public:
    LabelRLS(const QVector3D& position,
             const QString& nameRLS = nullptr,
             bool run = false);

    LabelRLS(const LabelRLS& dataRLS);

    // Позиция РЛС в пространстве
    void getPosition(QVector3D& Point3D) const;

    // Узнать, работает ли РЛС
    bool isWorking() const;

    // Узнать позывной
    QString getName() const;

    // Получить данные об ДН антены
    void getGraphicData(QVector <double>& X,
                        QVector <double>& Y) const;

protected:

    // Включена ли РЛС
    bool working;

    // Точка стояния РЛС
    QVector3D pos;

    // Позывной
    QString name;

    // Диаграмма направленности
    QVector <QPointF> DV;
};

#endif // LABELRLS_H
