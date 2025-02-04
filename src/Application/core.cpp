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
    readyRunProgress(3, "Инициализация менеджера ЛА...");

    readyRunProgress(19, "Загрузка модуля по работе с рельефом...");

    /* ... */

    readyRunProgress(36, "Загрузка менеджера РЛС...");

    // Информатор высоты
    HeightMeter* HeightMap = gis->getHeightMeter();

    // Испускатель лучей
    RayTracer = new TracerLight(HeightMap);

    // Класс по работе с файлом проекта
    projectFils = new ProjectFile;
    /// Для теста
    if (!projectFils->create(QApplication::applicationDirPath() + "//bd.txt"))
    {
        QString error;
        projectFils->lastError(error);
        qDebug() << error;
    }
    else
    {
        if(!projectFils->addData(ProjectFile::plane, "drone1"))
        {
            QString error;
            projectFils->lastError(error);
            qDebug() << error;
        }

        if(!projectFils->addData(ProjectFile::RLS,  "rls1"))
        {
            QString error;
            projectFils->lastError(error);
            qDebug() << error;
        }

        if(!projectFils->addData(ProjectFile::plane, "drone2"))
        {
            QString error;
            projectFils->lastError(error);
            qDebug() << error;
        }
    }
    /// -------------------------------------------------------------------------

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
            mapsManager,   SLOT(createMap(MapData,QString)));
    connect(mapsManager,   SIGNAL(finishCreateMap()),
            CreateProjWin, SLOT(hide()));

    readyRunProgress(65, "Инициализация интерфейса...");
}

void Core::init_GUI()
{
    //
    gui->connectGIS(gis);
    readyRunProgress(72);

    //
    gui->connectMapsManager(mapsManager);
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
