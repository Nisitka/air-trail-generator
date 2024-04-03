#include "map3dwindow.h"
#include "ui_map3dwindow.h"

#include "GUI/designer.h"

#include <QDebug>

map3DWindow::map3DWindow(Map* map_, QImage* imgTex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map3DWindow)
{
    map = map_;

    ui->setupUi(this);

    visMap = new mapOpenGLWidget(map,
                                 imgTex,
                                 ui->frameOXLabel, ui->frameOYLabel, ui->frameXYLabel);

    //ui->horizontalLayout_3->addWidget(visMap);
    ui->visTerGroupBox->layout()->addWidget(visMap);

    connect(ui->updateButton, SIGNAL(clicked()),
            this,             SIGNAL(generateMap3D()));
    Designer::setButton(ui->updateButton);
    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->framesGroupBox, Designer::gray);

    Designer::setGroupBox(ui->aZDGroupBox, Designer::gray);
    Designer::setGroupBox(ui->settingGroupBox, Designer::gray);
    Designer::setGroupBox(ui->visTerGroupBox, Designer::gray);

    ui->frameOXSlider->setRange(0, maxValueSliders);
    ui->frameOXSlider->setValue(maxValueSliders/2);
    connect(ui->frameOXSlider, SIGNAL(sliderMoved(int)),
            this,              SLOT(moveFrameOX(int)));

    ui->frameOYSlider->setRange(0, maxValueSliders);
    ui->frameOYSlider->setValue(maxValueSliders/2);
    connect(ui->frameOYSlider, SIGNAL(sliderMoved(int)),
            this,              SLOT(moveFrameOY(int)));

    ui->frameXYSlider->setRange(0, maxValueSliders);
    ui->frameXYSlider->setValue(maxValueSliders/2);
    connect(ui->frameXYSlider, SIGNAL(sliderMoved(int)),
            this,              SLOT(moveFrameXY(int)));

    connect(ui->frameOXDoubleSpinBox, SIGNAL(valueChanged(double)),
            this,                     SLOT(clickFrameOX(double)));
    connect(ui->frameOYDoubleSpinBox, SIGNAL(valueChanged(double)),
            this,                     SLOT(clickFrameOY(double)));
    connect(ui->frameXYDoubleSpinBox, SIGNAL(valueChanged(double)),
            this,                     SLOT(clickFrameXY(double)));

    visMap->show();
}

mapOpenGLWidget* map3DWindow::getGraphicsWidget()
{
    return visMap;
}

void map3DWindow::updateMap3D(int idXo, int idYo, int size)
{
    visMap->updateTerrain(idXo, idYo, size);
}
void map3DWindow::updateMap3D()
{
    visMap->updateTerrain();

    //qDebug() << "ASAS";
}

void map3DWindow::updatePointsInterZD(QVector<QVector<QVector<QVector3D> > >* points,
                                      QList <QVector3D>* posRLS)
{
    visMap->updatePosRLS(posRLS);
    visMap->updateZD(points);
}

void map3DWindow::moveFrameOX(int pos)
{
    float value = (float)pos / maxValueSliders;

    ui->frameOXDoubleSpinBox->setValue(value);
    visMap->setFrameOX(value);
}

void map3DWindow::moveFrameOY(int pos)
{
    float value = (float)pos / maxValueSliders;

    ui->frameOYDoubleSpinBox->setValue(value);
    visMap->setFrameOY(value);
}

void map3DWindow::moveFrameXY(int pos)
{
    float value = (float)pos / maxValueSliders;

    ui->frameXYDoubleSpinBox->setValue(value);
    visMap->setFrameXY(value);
}

void map3DWindow::clickFrameOX(double part)
{
    ui->frameOXSlider->setValue(part*maxValueSliders);

    visMap->setFrameOX(part);
}

void map3DWindow::clickFrameOY(double part)
{
    ui->frameOYSlider->setValue(part*maxValueSliders);

    visMap->setFrameOY(part);
}

void map3DWindow::clickFrameXY(double part)
{
    ui->frameXYSlider->setValue(part*maxValueSliders);

    visMap->setFrameXY(part);
}

void map3DWindow::finishBuildMap(int idXo, int idYo, int numW, int numL)
{
    setMap(idXo, idYo, numW, numL);
}

void map3DWindow::setMap(int idXo, int idYo, int numW, int numL)
{
    setAreaZD(idXo, idYo, numW, numL);
}

void map3DWindow::setAreaZD(int idXo, int idYo, int numW, int numL)
{

    visMap->initializeTerrain(idXo, idYo, numW, numL);
}

map3DWindow::~map3DWindow()
{
    delete ui;
}
