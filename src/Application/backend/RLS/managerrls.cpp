#include "managerrls.h"

#include <QDebug>

#include <QRect>

#include <memory>

managerRLS::managerRLS(TracerLight* RayTracer,
                       RZCreator* RZEditor,
                       HeightMeter* Height):
    RayTracer(RayTracer), RZEditor(RZEditor), Height(Height)
{
    idCurRLS = -1;

    pointsInterZD = nullptr;
    posRLS = nullptr;
}

void managerRLS::addRLS(QPoint* posRLS_, const QString& nameRLS)
{
    RLS* rls = new RLS(RayTracer, RZEditor, Height,
                       posRLS_, nameRLS);
    listRLS.append(rls);

    // Настройка пар-ов моделирования сигнала
    connect(rls,  SIGNAL(startSetOpt()),
            this, SIGNAL(startSetOpt()));
    connect(rls,  SIGNAL(changeStatProcessing(int)),
            this, SIGNAL(changeStatProcessing(int)));
    connect(rls,  SIGNAL(readyOptZDvert()),
            this, SIGNAL(readyOptZDvert()));
    connect(rls,  SIGNAL(readyClearZD()),
            this, SIGNAL(clearZD()));

    connect(rls,  SIGNAL(startClearZD()),
            this, SIGNAL(startClearZD()));

    //
    connect(rls,  SIGNAL(startEmitSignal()),
            this, SIGNAL(startEmitSignal()));
    connect(rls,  SIGNAL(finishGenerateZD()),
            this, SIGNAL(finishGenerateZD()));

    createReadyRLS();

    qDebug() << "create RLS!";
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

    int idX, idY, w, h;
    rls->getRectPosition(idX, idY, w, h);

    //
    rls->clearZD();

    //
    delete rls;
    listRLS.removeAt(id);

    emitSignalAllRLS();
    updateVisInfoMap(idX, idY, w, h);

    deleteReadyRLS();
}

void managerRLS::setPositionRLS(int idX, int idY)
{
    RLS* rls = listRLS.at(idCurRLS);
    rls->clearZD();

    QRect* rects = new QRect[2]; // области, которые надо будет перерисовать
    int idXo, idYo, w, h;
    rls->getRectPosition(idXo, idYo, w, h);
    rects[0].setRect(idXo, idYo, w, h);

    rls->setPosition(idX, idY);
    emitSignalAllRLS(); // перемодулируем сигнал всех РЛС

    rls->getRectPosition(idXo, idYo, w, h);
    rects[1].setRect(idXo, idYo, w, h);
    updateVisInfoMap(rects, 2); // обновляем визуальную информацию на карте
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
    RLS* rls = listRLS.at(idCurRLS);

    rls->off();
    emitSignalAllRLS();

    // обновляем визуальную информацию на карте
    int idX, idY, w, h;
    rls->getRectPosition(idX, idY, w, h);
    updateVisInfoMap(idX, idY, w, h);
}

void managerRLS::updateSignals()
{
    qDebug() << "Run all RLS";

    for (int i=0; i<listRLS.size(); i++)
    {
        RLS* rls = listRLS[i];
        if (rls->isWorking())
        {
            rls->off();
            rls->on();
            rls->emitSignal();

            // обновляем визуальную информацию на карте
            int idX, idY, w, h;
            rls->getRectPosition(idX, idY, w, h);
            updateVisInfoMap(idX, idY, w, h);
        }
    }
}

void managerRLS::emitSignalAllRLS()
{
    int sizeLoading = 0;
    RLS* rls;
    for (int i=0; i<listRLS.size(); i++)
    {
        rls = listRLS.at(i);
        if (rls->isWorking())
        {
            sizeLoading += rls->getCountHorVectors();
        }

    }

    startEmitSignal();
    curVecReady = 0;

    finishGenerateZD();
}

void managerRLS::runRLS(int idX, int idY)
{
    qDebug() << "Run one RLS (coords)";

    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
        sizeLoading += listRLS.at(i)->getCountHorVectors();

    startEmitSignal();
    curVecReady = 0;

    listRLS.at(idCurRLS)->on();
    listRLS.at(idCurRLS)->setPosition(idX, idY);
    for (int i=0; i<listRLS.size(); i++)
    {
        listRLS.at(i)->emitSignal();
    }

    // обновляем визуальную информацию на карте
    int idXo, idYo, w, h;
    listRLS.at(idCurRLS)->getRectPosition(idXo, idYo, w, h);
    updateVisInfoMap(idXo, idYo, w, h);
    finishGenerateZD();

    //updateVisInfoRLS();
}

void managerRLS::runRLS()
{
    qDebug() << "Run one RLS";

    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
        sizeLoading += listRLS.at(i)->getCountHorVectors();

    startEmitSignal();
    curVecReady = 0;

    listRLS.at(idCurRLS)->on();
    for (int i=0; i<listRLS.size(); i++)
    {
        listRLS.at(i)->emitSignal();
    }

    // обновляем визуальную информацию на карте
    int idX, idY, w, h;
    listRLS.at(idCurRLS)->getRectPosition(idX, idY, w, h);
    updateVisInfoMap(idX, idY, w, h);
    finishGenerateZD();
}

void managerRLS::setOptZDvert(int Rmax, int countVertVectors, int countPointsDV)
{
    listRLS.at(idCurRLS)->setOptZDvert(Rmax, countVertVectors, countPointsDV);
}
