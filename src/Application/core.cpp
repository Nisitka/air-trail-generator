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
    HeightMeter* HeightMap = gis->getHeightMeter();


    // Испускатель лучей
    RayTracer = new TracerLight(HeightMap);

    //
    projectFils = new ProjectFile();

    // Инициализация менеджера РЛС
    mRLS = new managerRLS(HeightMap);
    objects.append(mRLS);
    readyRunProgress(46, "Загрузка строителя маршрутов...");

    //
    InformerRLS* infoRLS = mRLS;
    gui = new GUI(gis, infoRLS);
    readyRunProgress(54, "Инициализация интерфейса...");

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
