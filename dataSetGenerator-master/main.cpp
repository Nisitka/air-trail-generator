#include <QApplication>
#include "core.h"

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile* file = new QFile;
    file->setFileName(QApplication::applicationDirPath() + "/file.txt");
    file->isOpen();

    Core* dataGenMaster = new Core;
    dataGenMaster->run();

    return a.exec();
}
