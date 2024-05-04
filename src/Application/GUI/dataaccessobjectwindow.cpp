#include "dataaccessobjectwindow.h"
#include "ui_dataaccessobjectwindow.h"
#include "GUI/designer.h"


DataAccessObjectWindow::DataAccessObjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAccessObjectWindow)
{
    ui->setupUi(this);

    Designer::setButton(ui->connectButton);

    ui->infoLabel->hide();
    connect(ui->connectButton, SIGNAL(clicked()),
            SLOT(connect_dao())
            );
    ui->progressBar->hide();
}

DataAccessObjectWindow::~DataAccessObjectWindow()
{
    delete ui;
}

void DataAccessObjectWindow::connect_dao()
{ 
    connection(ui->nameBaseEdit->text());

    ui->connectButton->setEnabled(false);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
    ui->progressBar->show();


}

void DataAccessObjectWindow::status_connect(bool isConnected)
{
    if(isConnected)
    {
        ui->infoLabel->setText("База данных подключена");
        ui->infoLabel->setStyleSheet("color: green;");
        ui->infoLabel->show();
        ui->connectButton->setEnabled(true);
        ui->progressBar->hide();
    }
    else
    {
        ui->infoLabel->setText("База данных не подключена");
        ui->infoLabel->setStyleSheet("color: red;");
        ui->infoLabel->show();
        ui->connectButton->setEnabled(true);
        ui->progressBar->hide();
    }
//    if(a == false)
//    {
//        ui->infoLabel->setText("База данных не подключена");
//        ui->infoLabel->setStyleSheet("color: red;");
//        ui->infoLabel->show();
//        ui->connectButton->setEnabled(true);
//        ui->progressBar->hide();
//    }
}

void DataAccessObjectWindow::onTimeout()
{
    ui->progressBar->setValue(ui->progressBar->value() + 10);
}


