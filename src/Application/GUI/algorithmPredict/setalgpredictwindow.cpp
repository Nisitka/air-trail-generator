#include "setalgpredictwindow.h"
#include "ui_setalgpredictwindow.h"

#include <QDebug>

#include "../designer.h"

setAlgPredictWindow::setAlgPredictWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setAlgPredictWindow)
{
    ui->setupUi(this);

    Designer::setScrollArea(ui->scrollArea);

    comArea = new composPredFunctionArea;

    ui->scrollArea->setWidget(comArea);
    //ui->Layout->addWidget(comArea);

    this->setMinimumHeight(200);
}

setAlgPredictWindow::~setAlgPredictWindow()
{
    delete ui;
}
