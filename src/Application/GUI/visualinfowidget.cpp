#include "visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

visualInfoWidget::visualInfoWidget(GISInformer* gis):
    gis(gis)
{
    /// Для теста!
    addFunWindow(new QTabWidget, QIcon(":/resurs/a"),"A",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    //
    mapDrawArea = new mapAreaMainWindow(gis);
    setCentralWidget(mapDrawArea);

    // Так как изначально никакой карты не открыто
    mapDrawArea->setEnabled(false);
}

void  visualInfoWidget::initOpenGLWindow()
{
    mapDrawArea->setDefStatus();
}

mapAreaMainWindow* visualInfoWidget::getManDrawArea()
{
    return mapDrawArea;
}

void visualInfoWidget::initProject()
{
    //
    mapDrawArea->setEnabled(true);

    //
    initOpenGLWindow();
}

visualInfoWidget::~visualInfoWidget()
{

}
