#include "coordsinfoform.h"
#include "ui_coordsinfoform.h"

#include <QDebug>

CoordsInfoForm::CoordsInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoordsInfoForm)
{
    ui->setupUi(this);

    ui->LabelCoordsInfo->setStyleSheet("QLabel{"
                                       "   background-color: rgb(255,255,255,140);"
                                       "   border: 1px solid rgb(55,55,55);"
                                       "   border-radius: 2px;"
                                       "};)");
    ui->LabelCoordsInfo->setMinimumHeight(20);
}

void CoordsInfoForm::setData(const Coords &coords)
{
    // Переводим в строку
    QString dataCoords = "X:" + QString::number(coords.X()) + "м"
                        " Y:" + QString::number(coords.Y()) + "м"
                        " H:" + QString::number(coords.H()) + "м";

    ui->LabelCoordsInfo->setText(dataCoords);
}

CoordsInfoForm::~CoordsInfoForm()
{
    delete ui;
}
