#include "optbuilddatasetwindow.h"
#include "ui_optbuilddatasetwindow.h"

#include <QDebug>

#include "designer.h"

optBuildDataSetWindow::optBuildDataSetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optBuildDataSetWindow)
{
    ui->setupUi(this);

    ui->buildDSProgressBar->setValue(0);
    // настройка визуала полоски прогресса
    Designer::setProgressBar(ui->buildDSProgressBar);
    ui->buildDSProgressBar->hide();

    //
    connect(ui->setDirNetImgButton, SIGNAL(clicked()),
            this,                   SLOT(setDirNetImages()));
    //
    connect(ui->setDirQFunButton, SIGNAL(clicked()),
            this,                 SLOT(setDirQFunData()));

    // запуск генерации обучающей выборки
    connect(ui->buildDataSetButton, SIGNAL(clicked()),
            this,                   SLOT(generateDataSet()));
    Designer::setButton(ui->buildDataSetButton);

    // обновляем значения размера ОВ после каждого изменения знач.
    connect(ui->countMapSpinBox, SIGNAL(valueChanged(int)),
            this,                SLOT(updateSizeDS()));
    connect(ui->countRectSpinBox, SIGNAL(valueChanged(int)),
            this,                 SLOT(updateSizeDS()));
    updateSizeDS();
}

void optBuildDataSetWindow::readyPart()
{
    currentData++;
    ui->buildDSProgressBar->setValue(currentData);

    if (currentData == sizeDataSet)
    {
        ui->buildDSProgressBar->setValue(0);
        ui->buildDSProgressBar->hide();
    }
}

void optBuildDataSetWindow::setDirNetImages()
{
    dirNetImages = QFileDialog::getExistingDirectory(0, "Входные образы нейронной сети", "");
    ui->netImagesDirLineEdit->setText(dirNetImages);
}

void optBuildDataSetWindow::setDirQFunData()
{
    dirQFunData = QFileDialog::getExistingDirectory(0, "Значения целевой функции", "");
    ui->qFunDirLineEdit->setText(dirQFunData);
}

void optBuildDataSetWindow::generateDataSet()
{
    sizeDataSet = ui->countMapSpinBox->value();

    currentData = 0;
    ui->buildDSProgressBar->setValue(currentData);
    ui->buildDSProgressBar->setMaximum(sizeDataSet);
    ui->buildDSProgressBar->show();

    int countRect = ui->countRectSpinBox->value();

    // запускаем генератор обучающей выборки
    startGenerateDataSet(sizeDataSet,
                         dirNetImages,
                         dirQFunData,
                         countRect);
}

void optBuildDataSetWindow::updateSizeDS()
{
    ui->sizeDSLabelValue->setText(QString::number(ui->countMapSpinBox->value() *
                                                  ui->countRectSpinBox->value()));
}

optBuildDataSetWindow::~optBuildDataSetWindow()
{
    delete ui;
}
