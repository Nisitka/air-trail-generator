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

    // устанавливаем карту
    map = map_;

    // устанавливаем изображения для отрисовки
    drawArea = new areaDrawWidget(geoMap);
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
    //
    Designer::setButton(ui->setDirSaveImgButton, Designer::white);
    Designer::setButton(ui->setDirSaveMapButton, Designer::white);

    //
    Designer::setButton(ui->saveImgButton);
    Designer::setButton(ui->saveMapButton);

    // настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->typeVisObjGroupBox);
    Designer::setGroupBox(ui->saveDataGroupBox);
    Designer::setGroupBox(ui->coordsGroupBox);

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);

    // настройка визула TabWidget-ов
    Designer::setTabWidget(ui->saveTabWidget);

    Designer::setComboBox(ui->typeSaveImglComboBox);
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
