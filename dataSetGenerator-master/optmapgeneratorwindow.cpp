#include "optmapgeneratorwindow.h"
#include "ui_optmapgeneratorwindow.h"

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
}

void optMapGeneratorWindow::updateProgressBar(int value)
{
    ui->buildProgressBar->setValue(value);
}

void optMapGeneratorWindow::finishGenerateMap()
{
    ui->buildProgressBar->setValue(0);
}

optMapGeneratorWindow::~optMapGeneratorWindow()
{
    delete ui;
}
