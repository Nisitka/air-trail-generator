#include "visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

visualInfoWidget::visualInfoWidget(GISInformer* gis, painterMapImage* mapImgGenerator):
    gis(gis)
{
    /// Для теста!
    manMapsWin = new ManagerMapsWindow;
    addFunWindow(manMapsWin, QIcon(":/resurs/mapIcon"),"Менеджер карт",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    //
    mapDrawArea = new mapAreaMainWindow(gis, mapImgGenerator);
    setCentralWidget(mapDrawArea);

    // Так как изначально никакой карты не открыто
    mapDrawArea->setLockStatus();
}

mapAreaMainWindow* visualInfoWidget::getManDrawArea()
{
    return mapDrawArea;
}

void visualInfoWidget::initProject()
{
    mapDrawArea->setDefStatus();
}

visualInfoWidget::~visualInfoWidget()
{

}
