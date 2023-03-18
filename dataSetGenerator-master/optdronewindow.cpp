#include "optdronewindow.h"
#include "ui_optdronewindow.h"

#include <QDebug>

optDroneWindow::optDroneWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optDroneWindow)
{
    ui->setupUi(this);

    connect(ui->setTrakButton, SIGNAL(clicked()),
            this,              SLOT(setTrackOptions()));
}

void optDroneWindow::setTrackOptions()
{
    setAngleE(ui->angleESpinBox->value());
}

optDroneWindow::~optDroneWindow()
{
    delete ui;
}
