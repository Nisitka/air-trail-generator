#include "optmapgeneratorwindow.h"
#include "ui_optmapgeneratorwindow.h"

#include "backend/ray.h"
#include "designer.h"

#include <QFileDialog>

optMapGeneratorWindow::optMapGeneratorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optMapGeneratorWindow)
{
    ui->setupUi(this);

    // запуск генерации карты по нажатию кнопки
    connect(ui->generateNewGbutton, SIGNAL(clicked()),
            this,                   SLOT(startGenerateMap()));

    ui->buildProgressBar->setValue(0);

    // значение длины ребра блока по умолчанию
    ui->lenBlockSpinBox->setValue(20);

    // минимальное значение не меньше дискреты полета луча сигнала
    ui->lenBlockSpinBox->setMinimum(Ray::mSIZE);

    connect(ui->openMapButton, SIGNAL(clicked()),
            this,              SLOT(openMap()));
    connect(ui->setDirNameMapButton, SIGNAL(clicked()),
            this,                    SLOT(setDirNameMap()));

    setDesine();        
}

void optMapGeneratorWindow::setDirNameMap()
{
    QString dirNameFile = QFileDialog::getOpenFileName();
    ui->dirMapLineEdit->setText(dirNameFile);

    openMap();
}

void optMapGeneratorWindow::setDesine()
{
    // настройка визула TabWidget-ов
    Designer::setTabWidget(ui->optTabWidget);

    // настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->geoGroupBox);
    Designer::setGroupBox(ui->optBlocksGroupBox);
    Designer::setGroupBox(ui->dirOpenMapGroupBox);

    // настройка визуала кнопок
    Designer::setButton(ui->generateNewGbutton);
    Designer::setButton(ui->openMapButton);
    Designer::setButton(ui->setDirNameMapButton, Designer::white);

    // настройка визуала полоски прогресса
    Designer::setProgressBar(ui->buildProgressBar);
    ui->buildProgressBar->hide();

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
}

void optMapGeneratorWindow::openMap()
{
    openMap_signal(ui->dirMapLineEdit->text());
}

void optMapGeneratorWindow::startGenerateMap()
{
    ui->buildProgressBar->setValue(0);

    runGenerateMap(ui->pBuildBlockSpinBox->value(),
                   ui->countEpochsSpinBox->value(),
                   ui->countWidBlocksSpinBox->value(),
                   ui->countLenBlocksSpinBox->value(),
                   ui->countHeiBlocksSpinBox->value(),
                   ui->lenBlockSpinBox->value()
                   );
}

void optMapGeneratorWindow::setProgressBar(int countLayers)
{
    ui->buildProgressBar->setMaximum(countLayers);
    ui->buildProgressBar->show();
}

void optMapGeneratorWindow::updateProgressBar(int value)
{
    ui->buildProgressBar->setValue(value);
}

void optMapGeneratorWindow::finishGenerateMap()
{
    ui->buildProgressBar->setValue(0);
    ui->buildProgressBar->hide();
}

optMapGeneratorWindow::~optMapGeneratorWindow()
{
    delete ui;
}
