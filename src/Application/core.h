#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QThread>

#include <QImage>


#include "GUI/gui.h"

#include "GUI/paintermapimage.h"

#include "backend/map.h"
#include "backend/geogenerator.h"
#include "backend/managerrls.h"
#include "backend/buildertraildrones.h"
#include "backend/managerdrones.h"

// ядро приложения
class Core : public QObject
{
    Q_OBJECT
signals:
    // готовность приложения к работе с пользователем
    void readyRunProgress(int p, const QString& textData = ""); // проценты

    // готово к работе
    void ready();

public slots:

public:
    Core();
    ~Core();

    void run();

    static void moveNewThread(QObject*);

private:
    void init_map();

    void init_allObj();

    void init_GUI();

    void init_buildThreads();

    // объекты приложения
    QVector <QObject*> objects;

    // интерфейс приложения
    GUI* gui;

    // карта (рельеф)
    Map* map;

    // генератор рельефа
    geoGenerator* mapGenerator;

    //
    painterMapImage* mapPainter;

    // менеджер РЛС
    managerRLS* mRLS;

    //
    builderTrailDrones* trailBuilder;

    // ПБЛА
    managerDrones* mDrones;

};

#endif // CORE_H
