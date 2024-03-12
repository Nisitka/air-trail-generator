#include "optdronewindow.h"
#include "ui_optdronewindow.h"

#include <QDebug>

#include "designer.h"

optDroneWindow::optDroneWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optDroneWindow)
{
    ui->setupUi(this);

    setDesine();
}

void optDroneWindow::setDesine()
{
    //
    Designer::setGroupBox(ui->groupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->createDronesGroupBox);
    Designer::setGroupBox(ui->listDronesGroupBox);
    Designer::setGroupBox(ui->TrailsGroupBox);
    Designer::setGroupBox(ui->infoTrailGroupBox);

    //
    Designer::setTabWidget(ui->addDroneTabWidget);
    Designer::setTabWidget(ui->curDroneTabWidget);
}

optDroneWindow::~optDroneWindow()
{
    delete ui;
}
