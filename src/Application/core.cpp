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
    gisInformer = gis->Informer();

    readyRunProgress(12);  
}

void Core::init_allObj()
{
    readyRunProgress(3, "Инициализация менеджера ЛА...");

    readyRunProgress(19, "Загрузка модуля по работе с рельефом...");

    /* ... */

    readyRunProgress(36, "Загрузка менеджера РЛС...");

    //
    RZInformer*  RZInfo    = gis->getRZInformer();
    RZCreator*   RZEditor  = gis->getRZCreator();
    HeightMeter* HeightMap = gis->getHeightMeter();


    // Испускатель лучей
    RayTracer = new TracerLight(HeightMap,
                                RZInfo);

    // Инициализация менеджера РЛС
    mRLS = new managerRLS(RayTracer, RZEditor, HeightMap);
    // Отрисовка
    QObject::connect(mRLS, SIGNAL(updateVisInfoMap(int,int,int,int)),
                     gis,  SLOT(updateFromRect(int,int,int,int)));
    QObject::connect(mRLS, SIGNAL(updateVisInfoMap(QRect*, int)),
                     gis,  SLOT(updateFromRects(QRect*,int)));
    objects.append(mRLS);
    readyRunProgress(46, "Загрузка строителя маршрутов...");

    //
    trailBuilder = new builderTrailDrones(RayTracer); //
    objects.append(trailBuilder);
    readyRunProgress(54, "Инициализация интерфейса...");

    //
    InformerRLS* infoRLS = mRLS;
    gui = new GUI(gis, infoRLS);
    createProjectWindow* CreateProjWin = gui->WindowCreateProject();
    connect(CreateProjWin, SIGNAL(sendDataNewProject(MapData,QString)),
            gis,           SLOT(initMap(MapData,QString)));
    connect(gis,           SIGNAL(finishBuildMap(int,int,int)),
            CreateProjWin, SLOT(hide()));

    readyRunProgress(65, "Инициализация интерфейса...");
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

    readyRunProgress(90);
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
