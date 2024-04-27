#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

#include "drawArea/mapareamainwindow.h"
//#include "backend/map.h"
#include "multiplewindow.h"

class visualInfoWidget: public MultipleWindow
{
    Q_OBJECT
signals:  

    /* ... */

public slots:

    /* ... */

public:
    explicit visualInfoWidget(QImage* geoMap,
                              Map* map);
    ~visualInfoWidget();

    mapAreaMainWindow* getManDrawArea();

private slots:

    /* ... */

private:
    //
    mapAreaMainWindow* manDrawArea;
};

#endif // VISUALINFOWIDGET_H
