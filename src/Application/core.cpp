#include "core.h"

#include <QApplication>

Core::Core()
{
    //Здесь был ФАРА!
    //Здесь была Александра
    //Здесь был Никита
}

void Core::init_map()
{
    readyRunProgress(3);
    map = new Map;
    readyRunProgress(12);
}

void Core::init_allObj()
{
    readyRunProgress(3, "Инициализация менеджера ЛА...");

    // Менеджер БПЛА
    mDrones = new managerDrones;

    readyRunProgress(19, "Загрузка модуля по работе с рельефом...");

    // Генератор рельефа
    mapGenerator = new geoGenerator(map);
    objects.append(mapGenerator);
    readyRunProgress(27, "Загрузка модуля карты...");

    // калькулятор цвета рельефа
    mapPainter = new painterMapImage(map);
    QObject::connect(mapGenerator, SIGNAL(readyLayer(int)),
                     mapPainter,   SLOT(run()));
    objects.append(mapPainter);

    //
    QObject::connect(mapGenerator, SIGNAL(editSizeMap()),
                     mapPainter,   SLOT(updateSizeMap()));

    readyRunProgress(36, "Загрузка менеджера РЛС...");

    // Инициализация менеджера РЛС
    mRLS = new managerRLS(map);
    // Отрисовка
    QObject::connect(mRLS,       SIGNAL(updateVisInfoMap(int,int,int,int)),
                     mapPainter, SLOT(runToRect(int,int,int,int)));
    QObject::connect(mRLS,       SIGNAL(updateVisInfoMap(QRect*, int)),
                     mapPainter, SLOT(runToRects(QRect*, int)));
    objects.append(mRLS);
    readyRunProgress(46, "Загрузка строителя маршрутов...");

    //
    trailBuilder = new builderTrailDrones(map);
    objects.append(trailBuilder);
    readyRunProgress(54, "Инициализация интерфейса...");
    //
    gui = new GUI(mapPainter->getImage(),
                  map);

    readyRunProgress(65, "Инициализация интерфейса...");

    database = new DAO;
    objects.append(database);
}

void Core::init_GUI()
{
    // присоеденяем функционад генератора к GUI
    gui->connectMapGenerator(mapGenerator);   
    readyRunProgress(72);

    //
    gui->connectMapPainter(mapPainter);
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
    mapGenerator->buildFlatMap();
    ///!!!!
//    mapGenerator->openMap(
//                QApplication::applicationDirPath() + "/maps/img4");

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
