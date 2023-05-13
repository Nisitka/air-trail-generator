#include <QApplication>
#include "core.h"

#include "runwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    runWindow startWin(&a, ":/resurs/startWindow");

    Core* luckyWay = new Core;

    QObject::connect(luckyWay,  SIGNAL(readyRunProgress(int)),
                     &startWin, SLOT(updateProgress(int)));

    QObject::connect(luckyWay,  SIGNAL(ready()),
                     &startWin, SLOT(close()));

    luckyWay->run();

    return a.exec();
}


