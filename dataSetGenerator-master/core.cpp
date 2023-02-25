#include "core.h"

Core::Core()
{
    map = new Map;

    // временно запишим объекты приложения
    QVector <QObject*> objects;

    // генератор рельефа
    mapGenerator = new geoGenerator(map);
    //connect()
    objects.append(mapGenerator);

    // калькулятор цвета рельефа
    mapPainter = new painterMapImage(map);
    QObject::connect(mapGenerator, SIGNAL(readyLayer(int)),
                     mapPainter,   SLOT(run()));
    objects.append(mapPainter);

    // калькулятор Q функции
    calcQFun = new calcQFunction(map);
    objects.append(calcQFun);

    // инициализация РЛС
    rls = new RLS(map);
    // при завершении обсчета ЗО - отрисовать изменения
    QObject::connect(rls,        SIGNAL(finishGenerateZD()),
                     mapPainter, SLOT(run()));
    objects.append(rls);

    //
    painterNetData = new painterDataNetImage(map);
    objects.append(painterNetData);

    //
    gui = new GUI(mapPainter->getImage(),
                  painterNetData->getImage(),
                  calcQFun->getImage(),
                  map);

    // присоеденяем функционад генератора к GUI
    gui->connectMapGenerator(mapGenerator);
    //
    gui->connectMapPainter(mapPainter);
    //
    gui->connectCalcQFun(calcQFun);
    //
    gui->connectRLS(rls);
    //
    gui->connectPainterDataNet(painterNetData);

    // помещаем все объекты в разные потоки
    for (int i=0; i<objects.size(); i++)
    {
        QThread* thread = new QThread;
        objects[i]->moveToThread(thread);
        thread->start();
    }
}

void Core::run()
{
    // открываем главное окно
    gui->showMainWin();
}
