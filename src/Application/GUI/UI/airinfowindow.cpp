#include "airinfowindow.h"
#include "ui_airinfowindow.h"

AirInfoWindow::AirInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirInfoWindow)
{
    ui->setupUi(this);
}

AirInfoWindow::~AirInfoWindow()
{
    delete ui;
}

void AirInfoWindow::showInfo(AirObject *AirObj)
{
    AirInfoWindow *air = new AirInfoWindow;

    air->ui->nameEdit->setText(AirObj->getNameAir());
    air->ui->longEdit->setText(QString::number(AirObj->getLongAir()));
    air->ui->weightEdit->setText(QString::number(AirObj->getWightAir()));
    air->ui->speedEdit->setText(QString::number(AirObj->getSpeedAir()));
    QPixmap pix(":/resurs/"+ AirObj->getPhotoAir() +"");

    air->ui->label->setPixmap(QPixmap(pix.scaled(290,150,Qt::KeepAspectRatio)));

    addDocks(air);

}
