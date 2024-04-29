#include "airobjectfunwindow.h"
#include "ui_airobjectfunwindow.h"
#include <QDebug>

AirObjectFunWindow::AirObjectFunWindow() :
    ui(new Ui::AirObjectFunWindow)
{
    ui->setupUi(this);

   //showTmpDock(new QWidget);
}

AirObjectFunWindow::~AirObjectFunWindow()
{
    delete ui;
}

void AirObjectFunWindow::setParameters(QString name, double longs, double wight, double speed, QString photo)
{
    ui->nameEdit->setText(name);
    ui->longEdit->setText(QString::number(longs));
    ui->wightEdit->setText(QString::number(wight));
    ui->speedEdit->setText(QString::number(speed));
    QPixmap pix(":/resurs/"+ photo +"");
    ui->photoLlabel->setPixmap(pix.scaled(290,150,Qt::KeepAspectRatio));
}
