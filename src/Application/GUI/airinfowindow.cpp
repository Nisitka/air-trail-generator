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
