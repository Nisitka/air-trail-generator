#include "visualinfowidget.h"
#include "ui_visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

#include "backend/buildertraildrones.h"

visualInfoWidget::visualInfoWidget(QImage* geoMap,
                                   Map* map_) :
    ui(new Ui::visualInfoWidget)
{
    ui->setupUi(this);

    /// Для теста!
    addFunWindow(new QTabWidget, QIcon(":/resurs/a"),"A",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    //
    manDrawArea = new mapAreaMainWindow(geoMap, map_);
    setCentralWidget(manDrawArea);
}

mapAreaMainWindow* visualInfoWidget::getManDrawArea()
{
    return manDrawArea;
}

void visualInfoWidget::switchVisual(int idType)
{
    switch (idType)
    {
    case areaDrawWidget::geoMap :
        manDrawArea->getDrawArea()->drawGeoMap();
        break;
    case areaDrawWidget::netData :
        manDrawArea->getDrawArea()->drawDataNet();
        break;
    case areaDrawWidget::QFunction :
        manDrawArea->getDrawArea()->drawQFunction();
        break;
    }
}

void visualInfoWidget::updateImage()
{
    manDrawArea->getDrawArea()->updateMapImage();
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
