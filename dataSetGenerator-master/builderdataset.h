#ifndef BUILDERDATASET_H
#define BUILDERDATASET_H

#include <QObject>

#include "map.h"

class builderDataSet : public QObject
{
    Q_OBJECT
signals:
    // генерировать рельеф
    void buildNewMap();

    // изменить азимут конечной точки
    void setAngleE(double E); // градусы

    // установить коодинаты квадрата прогноза
    void setCoordRect(int idX, int idY);

    // смоделировать работу РЛС
    void generateZD(int Xpos, int Ypos, int Hsrez);

    // сгенерировать образ для нейронной сети
    void generateNetImage();

    // сгенерировать и сохранить занченяи Q функции
    void generateQFunData(const QString& dir, // путь к папке хранения
                          int numFile); // номер файла

    // сохранить образ для нейронной сети
    void saveNetImage(const QString& dirNameNetImage);

    // завершение генерации одной обучающей пары
    void readyData();

    // завершение генерации всей обучающего сета
    void finish();

public slots:
    // запуск генерации обучающей выборки
    void run(int countData,
             const QString& dirNetImages,
             const QString& dirQFunData,
             int countRect = 1);

    // завершение работы генератора карты
    void mapReady();

    // завершение генерации образа для сети
    void readyNetImage();

    // завершение генерации ЗО
    void readyZD();

    // завершениие генерации знач. Q-функции
    void readyQFunData();


public:
    builderDataSet(Map* map);

private:
    QString dirNetImages;
    QString dirQFunData;

    //
    Map* map;
    int w;
    int l;

    //
    bool ON;

    // номер текующнй обуча-й пары
    int numCurrentData;

    // сколько сгенерировать всего
    int countBuildData;

    // кол-во квадратов прогноза на одной обстановкеЫ
    int countRect;
    int currentRect;
};

#endif // BUILDERDATASET_H
