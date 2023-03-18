#include "visualinfowidget.h"
#include "ui_visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

#include "designer.h"

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
    connect(drawArea, SIGNAL(predictMoveDroneRect(int,int)),
            this,     SLOT(setIdCoordsRectPredict(int,int)));
    //
    connect(drawArea, SIGNAL(setPointsTrail(QPoint,QPoint)),
            this,     SIGNAL(setPointsTrail(QPoint,QPoint)));
    updateSizeDrawArea();
    // добавляем виджет в интерфейс задачи
    ui->areaDrawLayout->addWidget(drawArea);

    //
    ui->objectVisualComboBox->addItems(strTypeVisual);
    connect(ui->objectVisualComboBox, SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(switchVisual(int)));


    //
    connect(ui->setDirSaveImgButton, SIGNAL(clicked()),
            this,                    SLOT(setDirImg()));

    //
    connect(ui->saveImgButton, SIGNAL(clicked()),
            this,              SLOT(saveImage()));

    //
    connect(ui->setSizeAreaButton, SIGNAL(clicked()),
            this,                  SLOT(updateSizeDrawArea()));
    Designer::setButton(ui->setSizeAreaButton);

    ui->saveImgButton->setIcon(QIcon(":/resurs/save"));
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
    ui->setRLStoolButton->setIcon(QIcon(":/resurs/radarBlue"));
    ui->moveMapToolButton->setIcon(QIcon(":/resurs/hand"));
    ui->zoomMapToolButton->setIcon(QIcon(":/resurs/zoom"));
    ui->predictRectToolButton->setIcon(QIcon(":/resurs/handDrone"));
    ui->predictTrailToolButton->setIcon(QIcon(":/resurs/trail2"));

    Designer::setButton(ui->setRLStoolButton, Designer::toolOFF);
    Designer::setButton(ui->zoomMapToolButton, Designer::toolOFF);
    Designer::setButton(ui->moveMapToolButton, Designer::toolOFF);
    Designer::setButton(ui->predictRectToolButton, Designer::toolOFF);
    Designer::setButton(ui->predictTrailToolButton, Designer::toolOFF);

    // настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->groupBox);
    Designer::setGroupBox(ui->groupBox_2);
    Designer::setGroupBox(ui->groupBox_3);

    // изначально выбираем постановку РЛС
    lastButtonTool = ui->predictRectToolButton;
    setToolRLS();

    connect(ui->saveMapButton, SIGNAL(clicked()),
            this,              SLOT(saveMap()));

    isPredictTrail = false;

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);
}

void visualInfoWidget::setResultPredictRect(int idX, int idY)
{
    drawArea->drawResultPredictRect(idX, idY);
}

void visualInfoWidget::setIdCoordsRectPredict(int idX, int idY)
{
    int Wmap = map->getWidth();
    int Lmap = map->getLength();

    if (idX + 100 > Wmap) idX = Wmap - 100;
    if (idY + 100 > Lmap) idY = Lmap - 100;

    if (idX - 100 < 0) idX = 100;
    if (idY - 100 < 0) idY = 100;

    setRectPredict(idX - 100, idY - 100);

    // если прогнозируем траекторию, то добавить точку для её отрисовки
    if (isPredictTrail) drawArea->addPointTrail(idX, idY);

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

void visualInfoWidget::setDirImg()
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
    drawArea->setTool(areaDrawWidget::moveImg);

    Designer::setButton(ui->moveMapToolButton, Designer::toolON);
    Designer::setButton(lastButtonTool, Designer::toolOFF);

    lastButtonTool = ui->moveMapToolButton;
}

void visualInfoWidget::setToolRLS()
{
    drawArea->setTool(areaDrawWidget::setRLS);

    Designer::setButton(ui->setRLStoolButton, Designer::toolON);
    Designer::setButton(lastButtonTool, Designer::toolOFF);

    lastButtonTool = ui->setRLStoolButton;
}

void visualInfoWidget::setToolZoom()
{
    drawArea->setTool(areaDrawWidget::zoomImg);

    Designer::setButton(ui->zoomMapToolButton, Designer::toolON);
    Designer::setButton(lastButtonTool, Designer::toolOFF);

    lastButtonTool = ui->zoomMapToolButton;
}

void visualInfoWidget::setToolPredictRect()
{
    drawArea->setTool(areaDrawWidget::predictRect);

    Designer::setButton(ui->predictRectToolButton, Designer::toolON);
    Designer::setButton(lastButtonTool, Designer::toolOFF);

    lastButtonTool = ui->predictRectToolButton;
}

void visualInfoWidget::setToolPredictTrail()
{
    drawArea->setTool(areaDrawWidget::predictTrail);

    Designer::setButton(ui->predictTrailToolButton, Designer::toolON);
    Designer::setButton(lastButtonTool, Designer::toolOFF);

    lastButtonTool = ui->predictTrailToolButton;
}

void visualInfoWidget::showInfoCoord(double x, double y)
{
    int l = map->getLenBlock();

    ui->xValueLabel->setText(QString::number(x * l) + "m");
    ui->yValueLabel->setText(QString::number(y * l) + "m");
    ui->hValueLabel->setText(QString::number(map->getHeight(x, y) * l) + "m");
}

void visualInfoWidget::updateSizeDrawArea()
{
    drawArea->updateSizeWidget(ui->wAreaSpinBox->value(),
                               ui->hAreaSpinBox->value());
}

void visualInfoWidget::updateImage()
{
    drawArea->repaint();
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
