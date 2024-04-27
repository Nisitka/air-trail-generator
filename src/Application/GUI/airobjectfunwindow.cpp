#include "airobjectfunwindow.h"
#include "ui_airobjectfunwindow.h"

AirObjectFunWindow::AirObjectFunWindow() :
    ui(new Ui::AirObjectFunWindow)
{
    ui->setupUi(this);

    showTmpDock(new QWidget);
}

AirObjectFunWindow::~AirObjectFunWindow()
{
    delete ui;
}
