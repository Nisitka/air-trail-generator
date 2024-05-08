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
    /// Инициализация блоков для записи
//    geoBlock b1, b2, b3;
//    b2.toEarth();
//    b2.toZD();

//    /// Записываем блоки в файл
//    QByteArray data;
//    QDataStream ds(&data, QIODevice::ReadWrite);
//    ds << b1 << b2 << b3;

//    //
//    QSaveFile file(QApplication::applicationDirPath() + "\\blocks\\blocks.b");
//    file.open(QIODevice::WriteOnly);
//    file.write(data);

//    // Размер файла в битах
//    qDebug() << file.size() << data.size() << "SIZE";
//    //
//    file.commit();

    /// Замена блока в файле
//    QByteArray data;
//    QDataStream ds(&data, QIODevice::ReadWrite);
//    geoBlock b;
//    ds << b;

//    QFile file(QApplication::applicationDirPath() + "\\blocks\\blocks.b");
//    file.open(QIODevice::WriteOnly);
//    file.seek(2);
//    file.write(data, 2);

    /// Считывание блока из файла
//    QFile file(QApplication::applicationDirPath() + "\\blocks\\blocks.b");

//    if (file.open(QIODevice::ReadOnly))
//    {
//        // Размер одного блока в памяти
//        int count = 3;
//        int s = file.size() / count;
//        int id = 1; // индекс блока, который ищем

//        //
//        file.seek(s*id);
//        QDataStream inData(file.read(s));

//        geoBlock newBlock;
//        inData >> newBlock;
//        qDebug() << newBlock.isEarth() << newBlock.isZD();
//    }
    ///-----------------------------

    Core* luckyWay = new Core;

    QObject::connect(luckyWay,  SIGNAL(readyRunProgress(int, const QString&)),
                     &startWin, SLOT(updateProgress(int, const QString&)));

    QObject::connect(luckyWay,  SIGNAL(ready()),
                     &startWin, SLOT(close()));

    luckyWay->run();

    return a.exec();
}
