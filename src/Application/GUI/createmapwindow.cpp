#include "createmapwindow.h"
#include "ui_createmapwindow.h"

createMapWindow::createMapWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createMapWindow)
{
    ui->setupUi(this);


}

void createMapWindow::createMap()
{
    // Данные для инициализации карты
    MapData mapData;
    mapData.H = ui->sizeZSpinBox->value();
    mapData.W = ui->sizeXSpinBox->value();
    mapData.L = ui->sizeYSpinBox->value();
}

createMapWindow::~createMapWindow()
{
    delete ui;
}
