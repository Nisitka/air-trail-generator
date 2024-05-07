#include <QApplication>
#include "core.h"

#include "GUI/runwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_ForceRasterWidgets, false);

    qRegisterMetaTypeStreamOperators<geoBlock>("geoBlock");

    runWindow startWin(&a, ":/resurs/backgDemo3");

    ///-----------------------------
    /// Инициализация блока для записи
/*    geoBlock b1;
    b1.toEarth();
    b1.toZD();*/

    //data.reserve(data_size_in_bytes);

    /// Записываем блок в файл
/*    QByteArray data;
    QDataStream ds(&data, QIODevice::ReadWrite);
    ds << b1;

    //
    QSaveFile file(QApplication::applicationDirPath() + "\\blocks\\2.b");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    //
    file.commit();*/

    /// Считывание блока из файла
/*    QFile file(QApplication::applicationDirPath() + "\\blocks\\2.b");
    file.open(QIODevice::ReadOnly);
    QDataStream inData(&file);

    geoBlock b2;
    inData >> b2;
    qDebug() << b2.isEarth() << b2.isZD();*/
    ///-----------------------------

    Core* luckyWay = new Core;

    QObject::connect(luckyWay,  SIGNAL(readyRunProgress(int, const QString&)),
                     &startWin, SLOT(updateProgress(int, const QString&)));

    QObject::connect(luckyWay,  SIGNAL(ready()),
                     &startWin, SLOT(close()));

    luckyWay->run();

    return a.exec();
}
