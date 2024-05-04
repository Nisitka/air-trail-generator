#include "core.h"

#include <QApplication>

Core::Core()
{
    //Здесь был ФАРА!
    //Здесь была Александра
    //Здесь был Никита
}

void Core::init_GIS()
{
    readyRunProgress(3);

    gis = new GIS;
    objects.append(gis);
    backgroundMapImage = gis->getBackgroundImg();
    map = gis->getMap();
    gisInformer = gis->Informer();

    readyRunProgress(12);  
}

void Core::init_allObj()
{
    readyRunProgress(3, "Инициализация менеджера ЛА...");

    // Менеджер БПЛА
    mDrones = new managerDrones;

    readyRunProgress(19, "Загрузка модуля по работе с рельефом...");

    /* ... */

    readyRunProgress(36, "Загрузка менеджера РЛС...");

    // Инициализация менеджера РЛС
    mRLS = new managerRLS(map);
    // Отрисовка
    QObject::connect(mRLS, SIGNAL(updateVisInfoMap(int,int,int,int)),
                     gis,  SLOT(updateFromRect(int,int,int,int)));
    QObject::connect(mRLS, SIGNAL(updateVisInfoMap(QRect*, int)),
                     gis,  SLOT(updateFromRects(QRect*,int)));
    objects.append(mRLS);
    readyRunProgress(46, "Загрузка строителя маршрутов...");

    //
    trailBuilder = new builderTrailDrones(map);
    objects.append(trailBuilder);
    readyRunProgress(54, "Инициализация интерфейса...");
    //
    gui = new GUI(backgroundMapImage, ///ВРЕМЕННО!
                  gis);

    readyRunProgress(65, "Инициализация интерфейса...");

    database = new DAO;
    objects.append(database);
}

void Core::init_GUI()
{
    //
    gui->connectGIS(gis);
    readyRunProgress(72);

    //

    readyRunProgress(79);

    //
    gui->connectMRLS(mRLS);
    readyRunProgress(83);

    //
    gui->connectBuilderTrail(trailBuilder);
    //
    gui->connectMDrones(mDrones);

    readyRunProgress(90);

    gui->connectDataBase(database);
}

void Core::init_buildThreads()
{
    // Помещаем все объекты в разные потоки
    for (int i=0; i<objects.size(); i++)
    {
        moveNewThread(objects.at(i));
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
    init_GIS();

    init_allObj();

    init_GUI();

    init_buildThreads();
    //gis->setDefaultMap();
    gis->openMap(QApplication::applicationDirPath() + "\\maps\\img2.png");

    ready();

    // Открываем главное окно
    gui->showMainWin(); 
}

Core::~Core()
{
    int countObj = objects.size();
    for (int i=0; i<countObj; i++)
    {
        delete objects[i];
    }
}
