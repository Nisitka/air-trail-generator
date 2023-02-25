#include "optbuilddatasetwindow.h"
#include "ui_optbuilddatasetwindow.h"

#include <QDebug>

optBuildDataSetWindow::optBuildDataSetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optBuildDataSetWindow)
{
    ui->setupUi(this);

    ui->buildDSProgressBar->setValue(0);

    //
    connect(ui->setDirNetImgButton, SIGNAL(clicked()),
            this,                   SLOT(setDirNetImages()));
    //
    connect(ui->setDirQFunButton, SIGNAL(clicked()),
            this,                 SLOT(setDirQFunData()));

    // запуск генерации обучающей выборки
    connect(ui->buildDataSetButton, SIGNAL(clicked()),
            this,                   SLOT(generateDataSet()));
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
    int sizeDataSet = ui->sizeDataSetSpinBox->value();

    startGenerateDataSet();

    qDebug() << "Start generate data";
}

optBuildDataSetWindow::~optBuildDataSetWindow()
{
    delete ui;
}
