#include "optdronewindow.h"
#include "ui_optdronewindow.h"

#include <QDebug>

#include "designer.h"

optDroneWindow::optDroneWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optDroneWindow)
{
    ui->setupUi(this);

    connect(ui->setTrakButton, SIGNAL(clicked()),
            this,              SLOT(setTrackOptions()));

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->trailGroupBox);
    Designer::setButton(ui->setTrakButton);
}

void optDroneWindow::setTrackOptions()
{
    setAngleE(ui->angleESpinBox->value());
}

optDroneWindow::~optDroneWindow()
{
    delete ui;
}
