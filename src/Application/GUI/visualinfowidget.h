#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

#include "drawArea/mapareamainwindow.h"
#include "multiplewindow.h"

#include "backend/GIS/gisinformer.h"

class visualInfoWidget: public MultipleWindow
{
    Q_OBJECT
signals:  

    /* ... */

public slots:

    void initOpenGLWindow();

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
};

#endif // VISUALINFOWIDGET_H
