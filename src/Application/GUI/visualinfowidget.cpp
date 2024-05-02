#include "visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

#include "backend/buildertraildrones.h"

visualInfoWidget::visualInfoWidget(GISInformer* gis):
    gis(gis)
{

    /// Для теста!
    addFunWindow(new QTabWidget, QIcon(":/resurs/a"),"A",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    //
    manDrawArea = new mapAreaMainWindow(gis);
    setCentralWidget(manDrawArea);
}

mapAreaMainWindow* visualInfoWidget::getManDrawArea()
{
    return manDrawArea;
}

visualInfoWidget::~visualInfoWidget()
{

}
