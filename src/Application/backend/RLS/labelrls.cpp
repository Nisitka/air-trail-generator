#include "labelrls.h"

LabelRLS::LabelRLS(const QVector3D& position,
                   const QString& nameRLS,
                   bool run):
    name(nameRLS), working(run), pos(position)
{
    /* ... */
}

LabelRLS::LabelRLS(const LabelRLS &infoRLS)
{
    //
    infoRLS.getPosition(pos);

    //
    working = infoRLS.isWorking();

    //
    name = infoRLS.getName();
}

void LabelRLS::getGraphicData(
        QVector<double> &X,
        QVector<double> &Y) const
{
    // Защита от дурака
    X.clear();
    Y.clear();

    //
    int countPoint = DV.size();
    X.resize(countPoint);
    Y.resize(countPoint);

    for (int i=0; i<countPoint; i++)
    {
        X[i] = DV[i].x();
        Y[i] = DV[i].y();
    }
}

void LabelRLS::getPosition(QVector3D &Point3D) const
{
    // В индексах
    Point3D = pos;
}

bool LabelRLS::isWorking() const
{
    return working;
}

QString LabelRLS::getName() const
{
    return name;
}
