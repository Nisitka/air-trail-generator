#include "neuronnetworkwindow.h"
#include "ui_neuronnetworkwindow.h"

#include <QDebug>

neuronNetworkWindow::neuronNetworkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::neuronNetworkWindow)
{
    ui->setupUi(this);

    connect(ui->predictButton, SIGNAL(clicked()),
            this,              SLOT(runPredict()));
    connect(ui->trainNetButton, SIGNAL(clicked()),
            this,               SLOT(runTrainNet()));

    ui->typePredictComboBox->addItems(listTypePredict);
}

void neuronNetworkWindow::runPredict()
{
    switch (ui->typePredictComboBox->currentIndex()) {
    case rect:
        runPredictRect();
        break;
    case trail:
        runPredictTrail();
        break;
    }
}

void neuronNetworkWindow::runPredictRect()
{
    ui->predictButton->setEnabled(false);
    predictToRect();
}

void neuronNetworkWindow::runPredictTrail()
{
    predictTrail(beginPoint.x(), beginPoint.y(),
                 lastPoint.x(), lastPoint.y());
}

void neuronNetworkWindow::finishRectPredict(int idX, int idY)
{
    ui->predictButton->setEnabled(true);
    qDebug() << idX << idY;
}

void neuronNetworkWindow::setPointsPredictTrail(const QPoint &begin, const QPoint &last)
{
    beginPoint = begin;
    lastPoint = last;
}

void neuronNetworkWindow::runTrainNet()
{
    //ui->trainNetButton->setEnabled(false);
    trainNet(ui->patchConsolAppLineEdit->text(),
             ui->patchInputDataLineEdit->text(),
             ui->patchRewardDataLineEdit->text(),
             ui->countEpochSpinBox->value(),
             ui->patchBuildModelLineEdit->text() + "\\" + ui->nameBuildModelLineEdit->text());
}

neuronNetworkWindow::~neuronNetworkWindow()
{
    delete ui;
}
