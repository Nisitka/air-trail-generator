#include "coordsinfoform.h"
#include "ui_coordsinfoform.h"

#include <QDebug>

CoordsInfoForm::CoordsInfoForm(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CoordsInfoForm)
{
    ui->setupUi(this);

    ui->LabelCoordsInfo->setStyleSheet("QLabel{"
                                       "   background-color: rgb(255,255,255,140);"
                                       "   border: 1px solid rgb(55,55,55);"
                                       "   border-radius: 2px;"
                                       "};)");

    installEventFilter(this);
}

void CoordsInfoForm::setData(const Coords &coords)
{
    // Переводим в строку
    QString dataCoords = "X:" + QString::number(coords.X()) + "м"
                        " Y:" + QString::number(coords.Y()) + "м"
                        " H:" + QString::number(coords.H()) + "м";
    ///ui->LabelCoordsInfo->setText(dataCoords);
}

bool CoordsInfoForm::eventFilter(QObject *watched, QEvent *event)
{
    //qDebug() << "Coords label: "  << watched->objectName() << event->type();
    event->ignore();

    return true;
}

CoordsInfoForm::~CoordsInfoForm()
{
    delete ui;
}
