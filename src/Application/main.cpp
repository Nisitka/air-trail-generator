#include <QApplication>
#include "core.h"

#include "GUI/runwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_ForceRasterWidgets, false);

    runWindow startWin(&a, ":/resurs/startWindow");

    Core* luckyWay = new Core;

    QObject::connect(luckyWay,  SIGNAL(readyRunProgress(int, const QString&)),
                     &startWin, SLOT(updateProgress(int, const QString&)));

    QObject::connect(luckyWay,  SIGNAL(ready()),
                     &startWin, SLOT(close()));

    luckyWay->run();

    return a.exec();
}
