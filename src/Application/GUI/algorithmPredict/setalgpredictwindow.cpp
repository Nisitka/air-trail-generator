#include "setalgpredictwindow.h"
#include "ui_setalgpredictwindow.h"

#include <QDebug>

setAlgPredictWindow::setAlgPredictWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setAlgPredictWindow)
{
    ui->setupUi(this);

    comArea = new composPredFunctionArea;

    this->setCentralWidget(comArea);
}

setAlgPredictWindow::~setAlgPredictWindow()
{
    delete ui;
}
