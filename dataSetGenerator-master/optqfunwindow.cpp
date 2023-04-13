#include "optqfunwindow.h"
#include "ui_optqfunwindow.h"

#include "designer.h"

optQFunWindow::optQFunWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optQFunWindow)
{
    ui->setupUi(this);

    // запуск обсчета и генерации изображения ЦФ
    connect(ui->calcQFunButton, SIGNAL(clicked()),
            this,               SLOT(emitSignalRunGenImage()));
    Designer::setButton(ui->calcQFunButton);

    ui->calcQFunProgressBar->setValue(0);
    // настройка визуала полоски прогресса
    Designer::setProgressBar(ui->calcQFunProgressBar);
    ui->calcQFunProgressBar->hide();

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
}

void optQFunWindow::emitSignalRunGenImage()
{
    runCalcQFun();
}

void optQFunWindow::startGenImage(int countSigment)
{
    ui->calcQFunProgressBar->setMaximum(countSigment);
    ui->calcQFunProgressBar->setValue(0);
    ui->calcQFunProgressBar->show();
}

void optQFunWindow::updateProgressGenImage(int currentSigment)
{
    ui->calcQFunProgressBar->setValue(currentSigment);
}

void optQFunWindow::finishGenImage()
{
    ui->calcQFunProgressBar->setValue(0);
    ui->calcQFunProgressBar->hide();
}

optQFunWindow::~optQFunWindow()
{
    delete ui;
}
