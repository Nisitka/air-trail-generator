#include "managerrls.h"

#include <QDebug>

#include <QRect>

#include <memory>

managerRLS::managerRLS(Map* map_)
{
    map = map_;

    idCurRLS = -1;

    pointsInterZD = nullptr;
    posRLS = nullptr;
}

void managerRLS::addRLS(QPoint* posRLS_, const QString& nameRLS)
{
    RLS* rls = new RLS(posRLS_, nameRLS);
    listRLS.append(rls);

    // завершение генерации вертикального сегмента
    connect(rls,  SIGNAL(readyVector(int)), // номер сегмента
            this, SLOT(readyVecRLS()));

    // запрос данных ЗО графика
    connect(rls,  SIGNAL(exportGraphicData(double*, double*, int)),
            this, SIGNAL(exportGraphicData(double*, double*, int)));

    // настройка пар-ов моделирования сигнала
    connect(rls,  SIGNAL(startSetOpt(int)),
            this, SIGNAL(startSetOpt(int)));
    connect(rls,  SIGNAL(readySetRay(int)),
            this, SIGNAL(readySetRay(int)));
    connect(rls,  SIGNAL(readyOptZDvert()),
            this, SIGNAL(readyOptZDvert()));

    createReadyRLS();

   // qDebug() << "create RLS!";
}

void managerRLS::updateVisInfoRLS()
{
    /* В дальнейшем сделать чтоб в зависимости от причины апдейта по
       разному готовила данные (типа не удалять все и поновой отпр.) */

    delete pointsInterZD;
    delete posRLS;

    pointsInterZD = new QVector<QVector<QVector<QVector3D>>>;
    posRLS = new QList <QVector3D>;

    if (listRLS.size() > 0)
    {
        RLS* rls;
        QVector3D pos;
        for (int i=0; i<listRLS.size(); i++)
        {
            rls = listRLS.at(i);

            rls->getPosition(pos);
            posRLS->append(pos);

            if (rls->isWorking())
            {
                rls->emitSignal(*map);
                pointsInterZD->push_back(rls->getPointsInterZD());
            }
        }

    }
    else
    {

    }

    sendPointsInterZD(pointsInterZD, posRLS);
}

void managerRLS::delRLS(int id)
{
    RLS* rls = listRLS.at(id);

    int idX, idY, w, h;
    rls->getRectPosition(idX, idY, w, h);

    // завершение генерации вертикального сегмента
    disconnect(rls,  SIGNAL(readyVector(int)), // номер сегмента
               this, SLOT(readyVecRLS()));

    // запрос данных ЗО графика
    disconnect(rls,  SIGNAL(exportGraphicData(double*, double*, int)),
               this, SIGNAL(exportGraphicData(double*, double*, int)));

    // настройка пар-ов моделирования сигнала
    disconnect(rls,  SIGNAL(startSetOpt(int)),
               this, SIGNAL(startSetOpt(int)));
    disconnect(rls,  SIGNAL(readySetRay(int)),
               this, SIGNAL(readySetRay(int)));
    disconnect(rls,  SIGNAL(readyOptZDvert()),
               this, SIGNAL(readyOptZDvert()));

    delete rls;
    listRLS.removeAt(id);

    emitSignalAllRLS();
    updateVisInfoMap(idX, idY, w, h);
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

void managerRLS::setRLS(int id)
{
    if (id >= 0)
    {
        idCurRLS = id;

        // обновляем график
        listRLS.at(idCurRLS)->getDataGraphic();

        // обновляем остальные данные об РЛС
        int Rmax, Xpos, Ypos, Hzd;
        bool working;
        listRLS.at(idCurRLS)->getOpt(Rmax, Xpos, Ypos, Hzd, working);
        updateOptGui(Rmax, Xpos, Ypos, Hzd, working);
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
    for (int i=0; i<listRLS.size(); i++)
    {
        RLS* rls = listRLS[i];
        if (rls->isWorking())
        {
            rls->off();
            rls->on();
            rls->emitSignal(*map);

            // обновляем визуальную информацию на карте
            int idX, idY, w, h;
            rls->getRectPosition(idX, idY, w, h);
            updateVisInfoMap(idX, idY, w, h);
        }
    }

    updateVisInfoRLS();
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

    startGenerateZD(sizeLoading);
    curVecReady = 0;

    //
    updateVisInfoRLS();

    finishGenerateZD();
}

void managerRLS::runRLS(int idX, int idY)
{
    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
        sizeLoading += listRLS.at(i)->getCountHorVectors();

    startGenerateZD(sizeLoading);
    curVecReady = 0;

    listRLS.at(idCurRLS)->on();
    listRLS.at(idCurRLS)->setPosition(idX, idY);
    for (int i=0; i<listRLS.size(); i++)
    {
        listRLS.at(i)->emitSignal(*map);
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
    int sizeLoading = 0;
    for (int i=0; i<listRLS.size(); i++)
        sizeLoading += listRLS.at(i)->getCountHorVectors();

    startGenerateZD(sizeLoading);
    curVecReady = 0;

    listRLS.at(idCurRLS)->on();
    for (int i=0; i<listRLS.size(); i++)
    {
        listRLS.at(i)->emitSignal(*map);
    }

    // обновляем визуальную информацию на карте
    int idX, idY, w, h;
    listRLS.at(idCurRLS)->getRectPosition(idX, idY, w, h);
    updateVisInfoMap(idX, idY, w, h);
    finishGenerateZD();

    updateVisInfoRLS();
}

void managerRLS::readyVecRLS()
{
    curVecReady++;
    readyVector(curVecReady);
}

void managerRLS::getDataGraphic()
{
    listRLS.at(idCurRLS)->getDataGraphic();
}

void managerRLS::setOptZDvert(int Rmax, int countVertVectors, int countPointsDV)
{
    listRLS.at(idCurRLS)->setOptZDvert(Rmax, countVertVectors, countPointsDV);
}
