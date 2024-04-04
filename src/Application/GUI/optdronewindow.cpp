#include "optdronewindow.h"
#include "ui_optdronewindow.h"

#include <QDebug>

#include "designer.h"

optDroneWindow::optDroneWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optDroneWindow)
{
    ui->setupUi(this);

    connect(ui->runPredictTrailButton, SIGNAL(clicked(bool)),
            this,                      SLOT(startPredictTrail()));

    ui->predictProgressBar->hide();
    ui->predictProgressBar->setMaximum(100);

    setDesine();
}

void optDroneWindow::setPredictPoints(int idXa, int idYa, int idXb, int idYb)
{
    ui->XaSpinBox->setValue(idXa);
    ui->YaSpinBox->setValue(idYa);

    ui->XbSpinBox->setValue(idXb);
    ui->YbSpinBox->setValue(idYb);
}

void optDroneWindow::startPredictTrail()
{
    runPredictTrail(ui->XaSpinBox->value(), ui->YaSpinBox->value(),
                    ui->XbSpinBox->value(), ui->YbSpinBox->value());
}

void optDroneWindow::startSetOptPredict()
{
    ui->predictProgressBar->setValue(0);
    ui->predictProgressBar->show();
}

void optDroneWindow::updateProgSetOptPred(int percent)
{
    ui->predictProgressBar->setValue(percent);
}

void optDroneWindow::finishSetOptPredict()
{
    ui->predictProgressBar->hide();
}

void optDroneWindow::setDesine()
{
    //
    Designer::setGroupBox(ui->groupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->createDronesGroupBox);
    Designer::setGroupBox(ui->listDronesGroupBox);
    Designer::setGroupBox(ui->TrailsGroupBox);
    Designer::setGroupBox(ui->infoTrailGroupBox);
    Designer::setGroupBox(ui->TPointAGBox);
    Designer::setGroupBox(ui->TPointBGBox);

    //
    Designer::setButton(ui->runPredictTrailButton);

    //
    Designer::setTabWidget(ui->addDroneTabWidget);
    Designer::setTabWidget(ui->curDroneTabWidget);

    //
    Designer::setProgressBar(ui->predictProgressBar);
}

optDroneWindow::~optDroneWindow()
{
    delete ui;
}
