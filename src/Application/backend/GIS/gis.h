#ifndef GIS_H
#define GIS_H

#include <QObject>

#include <QImage>
#include <QVector>

#include "map.h"
#include "paintermapimage.h"
#include "geogenerator.h"

// Геоинформационная система
class GIS: public QObject
{
    Q_OBJECT
signals:

    // Земля отредактирована:
    //  в области
    void changedMap(int idXo, int idYo, // Левый верхний угол области
                    int dX, int dY);    // Размеры области
    //  полностью
    void changedMap();

    // Процесс про инициализации рельефа
    void startBuildMap();                           // Начался
    void changedProgressBuildMap(int countPercent); // в %
    void finishBuildMap(int W, int L, int H);       // Завершился

public slots:

    // Актуализировать данные в
    void updateFromRect(int idX, int idY, int w, int h); // Прямоугольнике
    void updateFromRect(const QRect& rect);
    void updateFromRects(QRect* rects, int countS);      // Прямоугольниках

    // Редактирование рельефа
    void upEarth(int idX, int idY, int R);   // Поднять землю
    void downEarth(int idX, int idY, int R); // Опустить землю

public:
    ///!!!! ВРЕМЕННО !!!!!!
    Map* getMap();

    // При инициализации ГИС системы
    GIS();

    //
    QImage* getBackgroundImg();

    //
    void setDefaultMap();

private:
    //
    QImage* backgroundImg;

    //
    QVector<QVector<int> *>* Hmatrix;

    // Карта в виде блоков
    Map* map;

    //
    geoGenerator* geoBuilder;

    //
    painterMapImage* backPainter;
};

#endif // GIS_H
