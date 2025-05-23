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

    mapsManager = new mapManager;
    //objects.append(mapsManager);

    gis = new GIS(mapsManager);
    objects.append(gis);
    gisInformer = gis->Informer();

    readyRunProgress(12);  
}

void Core::init_allObj()
{
    // Класс по работе с файлом проекта
    readyRunProgress(3, "Инициализация менеджера проектов");
    proManager = new ProjectManager(mapsManager, gis);

    readyRunProgress(19, "Загрузка модуля по работе с рельефом...");

    /* ... */

    readyRunProgress(36, "Загрузка менеджера РЛС...");

    // Информатор высоты
    HeightMeter* HeightMap = gis->getHeightMeter();

    //
    mapImgGenerator = new painterMapImage(HeightMap);

    // Испускатель лучей
    RayTracer = new TracerLight(HeightMap);

    // Инициализация менеджера РЛС
    mRLS = new managerRLS(HeightMap);
    objects.append(mRLS);
    readyRunProgress(46, "Загрузка строителя маршрутов...");

    //
    InformerRLS* infoRLS = mRLS;
    gui = new GUI(gis, mapImgGenerator, infoRLS);
    readyRunProgress(54, "Инициализация интерфейса...");


    readyRunProgress(65, "Инициализация интерфейса...");
}

void Core::init_GUI()
{
    //
    gui->connectGIS(gis);
    readyRunProgress(72);

    //
    gui->connectProjectManager(proManager);
    readyRunProgress(79);

    //
    gui->connectMapsManager(proManager->EventsMaps(),
                            proManager->InfoMaps(),
                            proManager->CreatorMaps());

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
