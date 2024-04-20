#include "visualinfowidget.h"
#include "ui_visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

#include "backend/buildertraildrones.h"

visualInfoWidget::visualInfoWidget(QImage* geoMap,
                                   Map* map_,
                                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visualInfoWidget)
{
    ui->setupUi(this);

    //
    manDrawArea = new mapAreaMainWindow(geoMap, map_);
    ui->areaDrawLayout->addWidget(manDrawArea);

    //
    ui->objectVisualComboBox->addItems(strTypeVisual);
    connect(ui->objectVisualComboBox, SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(switchVisual(int)));

    //
    Designer::setGroupBox(ui->typeVisObjGroupBox);
    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
    Designer::setTabWidget(ui->addInfoTabWidget);

    isPredictTrail = false;
}

mapAreaMainWindow* visualInfoWidget::getManDrawArea()
{
    return manDrawArea;
}

//void visualInfoWidget::setCurRLS(int idRLS)
//{
//    manDrawArea->getDrawArea()->setCurRLS(idRLS);
//}

//void visualInfoWidget::addRLS(QPoint* posRLS, const QString& nameNewRLS)
//{
//    manDrawArea->getDrawArea()->addRLS(posRLS, nameNewRLS);
//}

//void visualInfoWidget::delRLS(int indexRLS)
//{
//    manDrawArea->getDrawArea()->delRLS(indexRLS);
//}

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
    manDrawArea->getDrawArea()->repaint();
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
