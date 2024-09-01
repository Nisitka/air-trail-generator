#include "hellowindow.h"
#include "ui_hellowindow.h"

helloWindow::helloWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helloWindow)
{
    ui->setupUi(this);
}

helloWindow::~helloWindow()
{
    delete ui;
}
