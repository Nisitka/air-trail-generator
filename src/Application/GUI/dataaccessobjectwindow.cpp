#include "dataaccessobjectwindow.h"
#include "ui_dataaccessobjectwindow.h"



DataAccessObjectWindow::DataAccessObjectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAccessObjectWindow)
{
    ui->setupUi(this);

    ui->infoLabel->hide();
    ui->errorLabel->hide();

    dao = new DAO;

    connect(ui->connectButton, SIGNAL(clicked()),
            SLOT(connect_dao())
            );

    connect(this, SIGNAL(connection(QString)),
            dao, SLOT(test_query(QString))
            );
}

DataAccessObjectWindow::~DataAccessObjectWindow()
{
    delete ui;
}

void DataAccessObjectWindow::connect_dao()
{
   int n = connection(ui->nameBaseEdit->text());
   if(n == 0)
   {
     ui->infoLabel->show();
     ui->errorLabel->hide();
   }
   if(n == 1)
   {
       ui->errorLabel->show();
       ui->infoLabel->hide();
   };

}
