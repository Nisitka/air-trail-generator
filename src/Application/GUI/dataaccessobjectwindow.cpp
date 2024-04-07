#include "dataaccessobjectwindow.h"
#include "ui_dataaccessobjectwindow.h"



DataAccessObjectWindow::DataAccessObjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAccessObjectWindow)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked()),
            SLOT(connect_dao())
            );
}

DataAccessObjectWindow::~DataAccessObjectWindow()
{
    delete ui;
}

void DataAccessObjectWindow::connect_dao()
{
    connection(ui->nameBaseEdit->text());
}

void DataAccessObjectWindow::status_connect(bool a)
{
    if(a == true)
    {
        ui->infoLabel->setText("База данных подключена");
        ui->infoLabel->setStyleSheet("color: green;");
    }
    if(a == false)
    {
        ui->infoLabel->setText("База данных не подключена");
        ui->infoLabel->setStyleSheet("color: red;");
    }
}


