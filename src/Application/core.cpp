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
    // Менеджер БПЛА
    mDrones = new managerDrones;

    // генератор рельефа
    mapGenerator = new geoGenerator(map);
    objects.append(mapGenerator);

    // калькулятор цвета рельефа
    mapPainter = new painterMapImage(map);
    QObject::connect(mapGenerator, SIGNAL(readyLayer(int)),
                     mapPainter,   SLOT(run()));
    objects.append(mapPainter);

    readyRunProgress(19);

    // инициализация менеджера РЛС
    mRLS = new managerRLS(map);
    // отрисовка
    QObject::connect(mRLS,       SIGNAL(updateVisInfoMap(int,int,int,int)),
                     mapPainter, SLOT(runToRect(int,int,int,int)));
    QObject::connect(mRLS,       SIGNAL(updateVisInfoMap(QRect*, int)),
                     mapPainter, SLOT(runToRects(QRect*, int)));
    objects.append(mRLS);

    readyRunProgress(27);

    //
    trailBuilder = new builderTrailDrones(map);
    objects.append(trailBuilder);

    readyRunProgress(36);


    readyRunProgress(46);


    readyRunProgress(54);

    //
    gui = new GUI(mapPainter->getImage(),
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

    readyRunProgress(79);

    //
    gui->connectMRLS(mRLS);

    readyRunProgress(83);

    //
    gui->connectBuilderTrail(trailBuilder);
    //
    gui->connectMDrones(mDrones);

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
