#include "managerrls.h"

#include <QDebug>

#include <QRect>

#include <memory>

managerRLS::managerRLS(HeightMeter* heightInfo): InformerRLS(),
    heightInfo(heightInfo)
{
    idCurRLS = -1;
}

void managerRLS::addRLS(const QPoint& posRLS, const QString& nameRLS)
{
    int idX = posRLS.x();
    int idY = posRLS.y();
    int idH = heightInfo->absolute(idX, idY, Coords::id);

    RLS* rls = new RLS(QVector3D(idX, idY, idH), nameRLS);
    listRLS.append(rls);

    createReadyRLS();
}

int managerRLS::countRLS() const
{
    return listRLS.size();
}

const LabelRLS* managerRLS::getInfoRLS(int idRLS) const
{
    return (LabelRLS*)listRLS.at(idRLS);
}

void managerRLS::delRLS(int id)
{
    RLS* rls = listRLS.at(id);

    //
    delete rls;
    listRLS.removeAt(id);

    deleteReadyRLS();
}

void managerRLS::setPositionRLS(int idX, int idY)
{
    listRLS[idCurRLS]->setPosition(idX, idY,
                                   heightInfo->absolute(idX, idY, Coords::id));
}

int managerRLS::idCurrentRLS() const
{
    return idCurRLS;
}

const LabelRLS* managerRLS::currentRLS() const
{
    if (countRLS() > 0)
        return (LabelRLS*)listRLS.at(idCurRLS);
    else
        return nullptr;
}

void managerRLS::setCurrentRLS(int id)
{
    if (id >= 0 &&
        id <  countRLS())
    {
        idCurRLS = id;

        // Сообщаем об этом всем, кому нужно
        changeCurrentRLS();
    }
}

void managerRLS::offRLS()
{
    listRLS[idCurRLS]->off();

    changeDataRLS(idCurRLS);
}

void managerRLS::runRLS()
{
    listRLS[idCurRLS]->on();

    changeDataRLS(idCurRLS);
}
