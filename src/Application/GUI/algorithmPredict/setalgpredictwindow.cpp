#include "setalgpredictwindow.h"
#include "ui_setalgpredictwindow.h"

#include <QDebug>

setAlgPredictWindow::setAlgPredictWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setAlgPredictWindow)
{
    ui->setupUi(this);

    comArea = new composPredFunctionArea;

    ui->Layout->addWidget(comArea);

    this->setMinimumHeight(200);
}

setAlgPredictWindow::~setAlgPredictWindow()
{
    delete ui;
}
