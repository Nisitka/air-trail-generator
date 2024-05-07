#include "airwindow.h"
#include "ui_airwindow.h"
#include <QFileDialog>
#include <QDebug>

AirWindow::AirWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirWindow)
{
    ui->setupUi(this);

    connect(ui->loadingButton, SIGNAL(clicked()),
            SLOT(show_AirObject()));
    connect(ui->creatButton, SIGNAL(clicked()),
            SLOT(creat_AirObject()));
    connect(ui->loadingPhotButton, SIGNAL(clicked()),
            SLOT(dowPhoto()));
}

AirWindow::~AirWindow()
{
    delete ui;
}

void AirWindow::loading_AirObject(QString ID, QString name)
{
    ui->airBox->addItem(name, ID);
}

void AirWindow::creat_AirObject()
{
    creat_AirObject(ui->nameEdit->text(),
                    ui->longEdit->text().toDouble(),
                    ui->weightEdit->text().toDouble(),
                    ui->speedEdit->text().toDouble(),
                    ui->photEdit->text());
}

void AirWindow::clearBoxs()
{
    ui->airBox->clear();
}

void AirWindow::dowPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open text", "/home/",
                                                    "(*.png)");
    QFileInfo fileinfo(fileName);
    QString photo = fileinfo.fileName();
    ui->photEdit->setText(photo);
}

void AirWindow::show_AirObject()
{
    show_AirObject(ui->airBox->currentData().toString());
}
