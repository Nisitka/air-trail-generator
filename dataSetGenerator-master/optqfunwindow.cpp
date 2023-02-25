#include "optqfunwindow.h"
#include "ui_optqfunwindow.h"

optQFunWindow::optQFunWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optQFunWindow)
{
    ui->setupUi(this);

    // запуск обсчета и генерации изображения ЦФ
    connect(ui->calcQFunButton, SIGNAL(clicked()),
            this,               SLOT(emitSignalRunGenImage()));

    ui->calcQFunProgressBar->setValue(0);
}

void optQFunWindow::emitSignalRunGenImage()
{
    runCalcQFun(ui->angleESpinBox->value());
}

void optQFunWindow::startGenImage(int countSigment)
{
    ui->calcQFunProgressBar->setMaximum(countSigment);
    ui->calcQFunProgressBar->setValue(0);
}

void optQFunWindow::updateProgressGenImage(int currentSigment)
{
    ui->calcQFunProgressBar->setValue(currentSigment);
}

void optQFunWindow::finishGenImage()
{
    ui->calcQFunProgressBar->setValue(0);
}

optQFunWindow::~optQFunWindow()
{
    delete ui;
}
