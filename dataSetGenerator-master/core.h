#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QThread>

#include <QImage>

#include "gui.h"
#include "map.h"
#include "geogenerator.h"
#include "paintermapimage.h"
#include "calcqfunction.h"
//#include "rls.h"
#include "managerrls.h"
#include "painterdatanetimage.h"
#include "builderdataset.h"
#include "trackparametras.h"
#include "buildertraildrones.h"
#include "drone.h"
#include "trainernetwork.h"

// ядро приложения
class Core : public QObject
{
    Q_OBJECT
signals:
    // готовность приложения к работе с пользователем
    void readyRunProgress(int p); // проценты

    // готово к работе
    void ready();

public slots:

public:
    Core();

    void run();

    static void moveNewThread(QObject*);

private:
    void init_map();

    void init_allObj();

    void init_GUI();

    void init_buildThreads();

    // объекты приложения
    QVector <QObject*> objects;

    // интерфейс приложения
    GUI* gui;

    // карта (рельеф)
    Map* map;

    // генератор рельефа
    geoGenerator* mapGenerator;

    //
    painterMapImage* mapPainter;

    //
    calcQFunction* calcQFun;

    // менеджер РЛС
    managerRLS* mRLS;

    //
    painterDataNetImage* painterNetData;

    //
    builderDataSet* builderDS;

    //
    builderTrailDrones* trailBuilder;

    // ПБЛА
    Drone* drone;

    //
    trainerNetwork* neuroTrainer;
};

#endif // CORE_H
