#include "core.h"

Core::Core()
{

}

void Core::init_map()
{
    readyRunProgress(3);
    map = new Map;
    readyRunProgress(12);
}

void Core::init_allObj()
{
    // БПЛА
    drone = new Drone;

    // все об траектории полета
    trackParametras* tracker = drone->getTracker();

    // генератор рельефа
    mapGenerator = new geoGenerator(map);
    objects.append(mapGenerator);

    // калькулятор цвета рельефа
    mapPainter = new painterMapImage(map);
    QObject::connect(mapGenerator, SIGNAL(readyLayer(int)),
                     mapPainter,   SLOT(run()));
    objects.append(mapPainter);

    readyRunProgress(19);

    // калькулятор Q функции
    calcQFun = new calcQFunction(map, tracker->getE());
    objects.append(calcQFun);

    // инициализация менеджера РЛС
    mRLS = new managerRLS(map);
    // отрисовка
    QObject::connect(mRLS,       SIGNAL(updateVisInfoMap(int,int,int,int)),
                     mapPainter, SLOT(runToRect(int,int,int,int)));
    QObject::connect(mRLS,       SIGNAL(updateVisInfoMap(QRect*, int)),
                     mapPainter, SLOT(runToRects(QRect*, int)));
    objects.append(mRLS);

    //
    painterNetData = new painterDataNetImage(map, tracker->getE());
    objects.append(painterNetData);

    readyRunProgress(27);

    //
    trailBuilder = new builderTrailDrones(tracker->getE());
    QObject::connect(trailBuilder,   SIGNAL(buildInputData(QString)),
                     painterNetData, SLOT(generateInputData(QString)));
    QObject::connect(painterNetData, SIGNAL(readyInputData()),
                     trailBuilder,   SLOT(usedNet()));
    QObject::connect(painterNetData, SIGNAL(readyRect(int, int)),
                     trailBuilder,   SLOT(readySetRect(int, int)));
    objects.append(trailBuilder);

    readyRunProgress(36);

    //
    builderDS = new builderDataSet(map);
    QObject::connect(mapGenerator, SIGNAL(buildFinish()),
                     builderDS,    SLOT(mapReady()));

    QObject::connect(builderDS, SIGNAL(setAngleE(double)),
                     tracker,   SLOT(setE(double)));

    QObject::connect(builderDS,  SIGNAL(generateZD(int,int,int)),
                     mRLS,       SLOT(runRLS(int,int,int)));
    QObject::connect(mRLS,       SIGNAL(finishGenerateZD()),
                     builderDS,  SLOT(readyZD()));

    readyRunProgress(46);

    QObject::connect(builderDS,      SIGNAL(generateNetImage()),
                     painterNetData, SLOT(run()));
    QObject::connect(painterNetData, SIGNAL(finish()),
                     builderDS,      SLOT(readyNetImage()));
    QObject::connect(builderDS,      SIGNAL(saveNetImage(QString)),
                     painterNetData, SLOT(saveImage(QString)));

    QObject::connect(builderDS, SIGNAL(generateQFunData(const QString&,int)),
                     calcQFun,  SLOT(calculate(const QString&,int)));
    QObject::connect(calcQFun,  SIGNAL(finish()),
                     builderDS, SLOT(readyQFunData()));

    neuroTrainer = new trainerNetwork;
    objects.append(neuroTrainer);

    readyRunProgress(54);

    //
    gui = new GUI(mapPainter->getImage(),
                  painterNetData->getImage(),
                  calcQFun->getImage(),
                  map);

    readyRunProgress(65);
}

void Core::init_GUI()
{
    // присоеденяем функционад генератора к GUI
    gui->connectMapGenerator(mapGenerator);
    //
    gui->connectMapPainter(mapPainter);

    readyRunProgress(72);

    //
    gui->connectPainterDataNet(painterNetData);
    //
    gui->connectCalcQFun(calcQFun);

    readyRunProgress(79);

    //
    gui->connectMRLS(mRLS);
    //
    gui->connectBuilderDS(builderDS);

    readyRunProgress(83);

    //
    gui->connectBuilderTrail(trailBuilder);
    //
    gui->connectDrone(drone);
    //
    gui->connectTrainerNet(neuroTrainer);

    readyRunProgress(90);
}

void Core::init_buildThreads()
{
    int dP = (100 - 90) / objects.size();

    // помещаем все объекты в разные потоки
    for (int i=0; i<objects.size(); i++)
    {
        moveNewThread(objects[i]);

        readyRunProgress((dP+1)*i + 90);
    }
}

void Core::moveNewThread(QObject *obj)
{
    QThread* thread = new QThread;
    obj->moveToThread(thread);
    thread->start();
}

void Core::run()
{
    init_map();

    init_allObj();

    init_GUI();

    init_buildThreads();

    // открываем главное окно
    gui->showMainWin();

    ready();
}

Core::~Core()
{
    int countObj = objects.size();
    for (int i=0; i<countObj; i++)
    {
        delete objects[i];
    }
}
