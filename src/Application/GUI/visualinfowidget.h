#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

#include "drawArea/mapareamainwindow.h"
#include "multiplewindow.h"

#include "backend/GIS/gisinformer.h"

#include "./managermapswindow.h"

// Окно по работе с визуальными данными
class visualInfoWidget:
        public MultipleWindow
{
    Q_OBJECT
signals:  

    /* ... */

public slots:

    // Подготовиться к работе с проектом
    void initProject();

public:
    explicit visualInfoWidget(GISInformer* gis);
    ~visualInfoWidget();

    mapAreaMainWindow* getManDrawArea();

private slots:

    /* ... */

private:

    //
    GISInformer* gis;

    //
    mapAreaMainWindow* mapDrawArea;

    //
    ManagerMapsWindow* manMapsWin;
};

#endif // VISUALINFOWIDGET_H
