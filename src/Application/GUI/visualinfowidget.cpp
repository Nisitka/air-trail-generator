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

    // Устанавливаем карту
    map = map_;

    //
    drawArea = new areaDrawWidget(geoMap, map);

    // Устанавливаем область для отрисовки и взаимодейстмия
    ui->areaDrawLayout->addWidget(drawArea);

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

areaDrawWidget* visualInfoWidget::getDrawArea()
{
    return drawArea;
}

void visualInfoWidget::setCurRLS(int idRLS)
{
    drawArea->setCurRLS(idRLS);
}

void visualInfoWidget::addRLS(QPoint* posRLS, const QString& nameNewRLS)
{
    drawArea->addRLS(posRLS, nameNewRLS);
}

void visualInfoWidget::delRLS(int indexRLS)
{
    drawArea->delRLS(indexRLS);
}

void visualInfoWidget::switchVisual(int idType)
{
    switch (idType)
    {
    case areaDrawWidget::geoMap :
        drawArea->drawGeoMap();
        break;
    case areaDrawWidget::netData :
        drawArea->drawDataNet();
        break;
    case areaDrawWidget::QFunction :
        drawArea->drawQFunction();
        break;
    }
}

void visualInfoWidget::updateImage()
{
    drawArea->repaint();
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
