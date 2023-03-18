#include <QApplication>
#include "core.h"

#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Core* dataGenMaster = new Core;
    dataGenMaster->run();

    return a.exec();
}
