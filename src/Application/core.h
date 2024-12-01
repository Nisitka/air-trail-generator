#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QThread>

#include <QImage>


#include "GUI/gui.h"

#include "backend/GIS/paintermapimage.h"

#include "backend/GIS/gis.h"
#include "backend/RLS/managerrls.h"

#include "backend/GIS/gisinformer.h"
#include "backend/tracerlight.h"

#include "backend/projectfile.h"

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
    void init_GIS();

    void init_allObj();

    void init_GUI();

    void init_buildThreads();

    // Объекты приложения
    QVector <QObject*> objects;

    // Интерфейс приложения
    GUI* gui;
    QImage* backgroundMapImage;
    QVector <QVector<int>*>* Hmatrix;

    //
    GIS* gis;
    GISInformer* gisInformer;

    //
    TracerLight* RayTracer;

    //
    ProjectFile* projectFils;

    // Менеджер РЛС
    managerRLS* mRLS;

};

#endif // CORE_H
