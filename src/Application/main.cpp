#include <QApplication>
#include "core.h"

#include "GUI/runwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_ForceRasterWidgets, false);

    //
    qRegisterMetaTypeStreamOperators<MapData>("MapData");

    runWindow startWin(&a, ":/resurs/backgDemo3");

    Core* luckyWay = new Core;

    QObject::connect(luckyWay,  SIGNAL(readyRunProgress(int, const QString&)),
                     &startWin, SLOT(updateProgress(int, const QString&)));

    QObject::connect(luckyWay,  SIGNAL(ready()),
                     &startWin, SLOT(close()));

    luckyWay->run();

    return a.exec();
}
