#include "visualinfowidget.h"
#include "ui_visualinfowidget.h"

#include <QFileDialog>
#include <QDebug>

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
    // добавляем виджет в интерфейс задачи
    ui->areaDrawLayout->addWidget(drawArea);

    //
    ui->objectVisualComboBox->addItems(strTypeVisual);
    connect(ui->objectVisualComboBox, SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(switchVisual(int)));

    //
    connect(ui->countPixSpinBox, SIGNAL(valueChanged(int)),
            this,                SLOT(updateSizeDrawArea()));

    //
    connect(drawArea, SIGNAL(setCoordRLS(int,int)),
            this,     SIGNAL(updateCoordRLS(int,int)));

    //
    connect(ui->setDirSaveImgButton, SIGNAL(clicked()),
            this,                    SLOT(setDirImg()));

    //
    connect(ui->saveImgButton, SIGNAL(clicked()),
            this,              SLOT(saveImage()));
}

void visualInfoWidget::saveImage()
{
    // определяем формат изображения
    areaDrawWidget::formatImg format;
    if (formatsImg.contains("jpg")) format = areaDrawWidget::jpg;
    if (formatsImg.contains("png")) format = areaDrawWidget::png;
    if (formatsImg.contains("bmp")) format = areaDrawWidget::bmp;

    drawArea->saveImage(ui->dirSaveImgLineEdit->text(), format);
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

    ui->xValueLabel->setText(QString::number(x * l) + "m");
    ui->yValueLabel->setText(QString::number(y * l) + "m");
    ui->hValueLabel->setText(QString::number(map->getHeight(x, y) * l) + "m");
}

void visualInfoWidget::updateSizeDrawArea()
{
    drawArea->updateSizeWidget(ui->countPixSpinBox->value());
}

void visualInfoWidget::updateImage()
{
    drawArea->repaint();
}

visualInfoWidget::~visualInfoWidget()
{
    delete ui;
}
