#include "visualinfowidget.h"
#include "ui_visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

#include "backend/buildertraildrones.h"

visualInfoWidget::visualInfoWidget(QImage* geoMap,
                                   QImage* dataNet,
                                   QImage* QFun,
                                   Map* map_,
                                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visualInfoWidget)
{
    ui->setupUi(this);

    // устанавливаем карту
    map = map_;

    // устанавливаем изображения для отрисовки
    drawArea = new areaDrawWidget(geoMap, dataNet, QFun);
    connect(drawArea, SIGNAL(updateCoord(double,double)),
            this,     SLOT(showInfoCoord(double,double)));
    //
    connect(drawArea, SIGNAL(setCoordRLS(int,int)),
            this,     SIGNAL(updateCoordRLS(int,int)));
    //
    connect(drawArea, SIGNAL(predictMoveDroneRect(int,int,int)),
            this,     SLOT(setIdCoordsRectPredict(int,int,int)));
    //
    connect(drawArea, SIGNAL(setPointsTrail(QPoint,QPoint)),
            this,     SIGNAL(setPointsTrail(QPoint,QPoint)));
    // добавляем виджет в интерфейс задачи
    ui->areaDrawLayout->addWidget(drawArea);

    //
    ui->objectVisualComboBox->addItems(strTypeVisual);
    connect(ui->objectVisualComboBox, SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(switchVisual(int)));

    //
    ui->typeSaveImglComboBox->addItems(typeSaveImg);

    // выбор инструмента по нажатию на кнопку
    connect(ui->setRLStoolButton, SIGNAL(clicked()),
            this,                 SLOT(setToolRLS()));
    connect(ui->moveMapToolButton, SIGNAL(clicked()),
            this,                  SLOT(setToolMoveImg()));
    connect(ui->zoomMapToolButton, SIGNAL(clicked()),
            this,                  SLOT(setToolZoom()));
    connect(ui->predictRectToolButton, SIGNAL(clicked()),
            this,                      SLOT(setToolPredictRect()));
    connect(ui->predictTrailToolButton, SIGNAL(clicked()),
            this,                       SLOT(setToolPredictTrail()));
    connect(ui->map3DToolButton, SIGNAL(clicked()),
            this,                SLOT(setTool3D()));
    connect(ui->editEarthToolButton, SIGNAL(clicked()),
            this,                    SLOT(setToolEditEarth()));

    // настройка визула
    setDesine();

    // сохранение изображения
    connect(ui->setDirSaveImgButton, SIGNAL(clicked()),
            this,                    SLOT(setDirNameImg()));
    connect(ui->saveImgButton, SIGNAL(clicked()),
            this,              SLOT(saveImage()));

    // сохранение рельефа (карты)
    connect(ui->setDirSaveMapButton, SIGNAL(clicked()),
            this,                    SLOT(setDirNameMap()));
    connect(ui->saveMapButton, SIGNAL(clicked()),
            this,              SLOT(saveMap()));

    isPredictTrail = false;

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);

    ui->optToolsGroupBox->hide();
    ui->optToolsButton->setIcon(QIcon(":/resurs/leftVector"));
    isShowOptTools = false;

    connect(ui->optToolsButton, SIGNAL(clicked()),
            this,               SLOT(hideShowOptTools()));

    ui->sizeEditEarthSlider->setMinimum(1);
    connect(ui->sizeEditEarthSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(moveSliderSizeToolEarth(int)));
}

void visualInfoWidget::moveSliderSizeToolEarth(int range)
{
    ui->sizeEditEarthSpinBox->setValue(range);
    drawArea->setRangeToolEditEarth(range);
}

void visualInfoWidget::hideShowOptTools()
{
    if (isShowOptTools)
    {
        ui->optToolsGroupBox->hide();
        ui->optToolsButton->setIcon(QIcon(":/resurs/leftVector"));
        isShowOptTools = false;
    }
    else
    {
        ui->optToolsGroupBox->show();
        ui->optToolsButton->setIcon(QIcon(":/resurs/rightVector"));
        isShowOptTools = true;
    }
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

void visualInfoWidget::setDirNameMap()
{
    // путь и имя сохраняемого файла
    QString file = QFileDialog::getSaveFileName(0,
                                           tr("Сохранить рельеф"),
                                           "Рельеф",
                                           "*.txt ;;",
                                           &mapFormat);
    ui->dirSaveMapLineEdit->setText(file);

    // и сразу сохраняем
    saveMap();
}

void visualInfoWidget::setResultPredictRect(int idX, int idY)
{
    drawArea->drawResultPredictRect(idX, idY);
}

void visualInfoWidget::setIdCoordsRectPredict(int idX, int idY, int typeP)
{
    int Wmap = map->getWidth();
    int Lmap = map->getLength();

    if (idX + 100 > Wmap) idX = Wmap - 100;
    if (idY + 100 > Lmap) idY = Lmap - 100;

    if (idX - 100 < 0) idX = 100;
    if (idY - 100 < 0) idY = 100;

    setRectPredict(idX - 100, idY - 100);

    // если прогнозируем траекторию, то добавить точку для её отрисовки
    if (isPredictTrail)
    {
        switch (typeP) {
        case builderTrailDrones::mainP:
            drawArea->addPointTrail(idX, idY);
            break;
        case builderTrailDrones::midP:

            break;
        }
    }

    drawArea->setPredictRect(idX - 100, idY - 100);
    drawArea->repaint();
}

void visualInfoWidget::saveMap()
{
    saveMap_signal(ui->dirSaveMapLineEdit->text());
}

void visualInfoWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{

}

void visualInfoWidget::saveImage()
{
    // определяем формат изображения
    areaDrawWidget::formatImg format;
    if (formatsImg.contains("jpg")) format = areaDrawWidget::jpg;
    if (formatsImg.contains("png")) format = areaDrawWidget::png;
    if (formatsImg.contains("bmp")) format = areaDrawWidget::bmp;

    areaDrawWidget::typeSaveImg tSave;
    switch (ui->typeSaveImglComboBox->currentIndex()) {
    case screen:
        tSave = areaDrawWidget::screen;
        break;
    case full:
        tSave = areaDrawWidget::full;
        break;
    case curRect:
        tSave = areaDrawWidget::rect;
        break;
    }
    // текущее изображение
    drawArea->saveImage(ui->dirSaveImgLineEdit->text(), format, tSave);
}

void visualInfoWidget::setDirNameImg()
{
    // путь и имя сохраняемого файла
    QString file = QFileDialog::getSaveFileName(0,
                                           tr("Сохранить изображение"),
                                           ui->objectVisualComboBox->currentText(),
                                           formatsImg,
                                           &curFormat);
    ui->dirSaveImgLineEdit->setText(file);

    // и сразу сохраняем
    saveImage();
}

void visualInfoWidget::readyPredictTrail()
{
    isPredictTrail = false;

    // разблокируем некоторые инструменты

    drawArea->finishPredictTrail();
}

void visualInfoWidget::startPredictTrail()
{
    isPredictTrail = true;
    numCurPoint = 0;

    // блокируем некоторые инструменты

    // отображаем начало просчета траектории
    drawArea->startPredictTrail();
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

void visualInfoWidget::setToolMoveImg()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::moveImg);

    Designer::setButton(ui->moveMapToolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::moveImg)
        drawArea->setTool(areaDrawWidget::def);
    else
        drawArea->setTool(areaDrawWidget::moveImg);

    lastButtonTool = ui->moveMapToolButton;
}

void visualInfoWidget::setToolRLS()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::setRLS);

    Designer::setButton(ui->setRLStoolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::setRLS)
        drawArea->setTool(areaDrawWidget::def);
    else
        drawArea->setTool(areaDrawWidget::setRLS);

    lastButtonTool = ui->setRLStoolButton;
}

void visualInfoWidget::setToolZoom()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::zoomImg);

    Designer::setButton(ui->zoomMapToolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::zoomImg)
        drawArea->setTool(areaDrawWidget::def);
    else
        drawArea->setTool(areaDrawWidget::zoomImg);

    lastButtonTool = ui->zoomMapToolButton;
}

void visualInfoWidget::setToolPredictRect()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::predictRect);

    Designer::setButton(ui->predictRectToolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::predictRect)
    {
        drawArea->setTool(areaDrawWidget::def);
    }
    else
    {
        drawArea->setTool(areaDrawWidget::predictRect);
    }

    lastButtonTool = ui->predictRectToolButton;
}

void visualInfoWidget::setToolPredictTrail()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::predictTrail);

    Designer::setButton(ui->predictTrailToolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::predictTrail)
        drawArea->setTool(areaDrawWidget::def);
    else
        drawArea->setTool(areaDrawWidget::predictTrail);

    lastButtonTool = ui->predictTrailToolButton;
}

void visualInfoWidget::setTool3D()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::mapVis);

    Designer::setButton(ui->map3DToolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::mapVis)
        drawArea->setTool(areaDrawWidget::def);
    else
        drawArea->setTool(areaDrawWidget::mapVis);

    lastButtonTool = ui->map3DToolButton;
}

void visualInfoWidget::setToolEditEarth()
{
    ui->optToolsStackedWidget->setCurrentIndex(areaDrawWidget::editEarth);

    Designer::setButton(ui->editEarthToolButton, Designer::toolON);
    if (drawArea->curTool() != areaDrawWidget::def)
        Designer::setButton(lastButtonTool, Designer::toolOFF);

    if (drawArea->curTool() == areaDrawWidget::editEarth)
        drawArea->setTool(areaDrawWidget::def);
    else
        drawArea->setTool(areaDrawWidget::editEarth);

    lastButtonTool = ui->editEarthToolButton;
}

void visualInfoWidget::showInfoCoord(double x, double y)
{
    int l = map->getLenBlock();

    ui->xValueLabel->setText(QString::number(x * l) + "м");
    ui->yValueLabel->setText(QString::number(y * l) + "м ");
    ui->hValueLabel->setText(QString::number(map->getHeight(x, y) * l) + "м");
}

void visualInfoWidget::updateImage()
{
    drawArea->repaint();
}

void visualInfoWidget::setDesine()
{
    // иконки кнопок-инструментов
    ui->setRLStoolButton->setIcon(QIcon(":/resurs/radarBlue"));
    ui->moveMapToolButton->setIcon(QIcon(":/resurs/hand"));
    ui->zoomMapToolButton->setIcon(QIcon(":/resurs/zoom"));
    ui->predictRectToolButton->setIcon(QIcon(":/resurs/handDrone"));
    ui->predictTrailToolButton->setIcon(QIcon(":/resurs/trail2"));
    ui->map3DToolButton->setIcon(QIcon(":/resurs/hand3D"));
    ui->editEarthToolButton->setIcon(QIcon(":/resurs/machinery"));

    Designer::setButton(ui->setRLStoolButton, Designer::toolOFF);
    Designer::setButton(ui->zoomMapToolButton, Designer::toolOFF);
    Designer::setButton(ui->moveMapToolButton, Designer::toolOFF);
    Designer::setButton(ui->predictRectToolButton, Designer::toolOFF);
    Designer::setButton(ui->predictTrailToolButton, Designer::toolOFF);
    Designer::setButton(ui->map3DToolButton, Designer::toolOFF);
    Designer::setButton(ui->editEarthToolButton, Designer::toolOFF);

    // кнопка открытия / закрытия опций инструментов
    Designer::setButton(ui->optToolsButton, Designer::white);

    //
    Designer::setButton(ui->setDirSaveImgButton, Designer::white);
    Designer::setButton(ui->setDirSaveMapButton, Designer::white);

    //
    Designer::setButton(ui->saveImgButton);
    Designer::setButton(ui->saveMapButton);

    // настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->typeVisObjGroupBox);
    Designer::setGroupBox(ui->saveDataGroupBox);
    Designer::setGroupBox(ui->toolsGroupBox);
    Designer::setGroupBox(ui->optToolsGroupBox);
    Designer::setGroupBox(ui->coordsGroupBox);

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);

    // настройка визула TabWidget-ов
    Designer::setTabWidget(ui->saveTabWidget);

    // настройка визула ComboBox-ов
    //Designer::setComboBox(ui->typeSaveImglComboBox);
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
