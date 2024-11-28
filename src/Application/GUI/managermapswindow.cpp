#include "managermapswindow.h"
#include "ui_managermapswindow.h"

#include "./designer.h"

ManagerMapsWindow::ManagerMapsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerMapsWindow)
{
    ui->setupUi(this);

    ui->listMapsDockWidget->setTitleBarWidget(new QWidget);


    // Настройки дизайна
    Designer::setButton(ui->selectMapPushButton);
    Designer::setTabWidget(ui->tabWidget);
    Designer::setGroupBox(ui->currentMapGroupBox);

}

ManagerMapsWindow::~ManagerMapsWindow()
{
    delete ui;
}
