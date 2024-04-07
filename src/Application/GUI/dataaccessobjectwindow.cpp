#include "dataaccessobjectwindow.h"
#include "ui_dataaccessobjectwindow.h"



DataAccessObjectWindow::DataAccessObjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAccessObjectWindow)
{
    ui->setupUi(this);

    ui->infoLabel->hide();
    ui->errorLabel->hide();

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
