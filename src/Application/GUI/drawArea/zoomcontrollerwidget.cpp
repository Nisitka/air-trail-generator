#include "zoomcontrollerwidget.h"
#include "ui_zoomcontrollerwidget.h"

#include <QDebug>

ZoomControllerWidget::ZoomControllerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomControllerWidget)
{
    ui->setupUi(this);

    setRangeValues();

    connect(ui->verticalSlider, SIGNAL(valueChanged(int)),
            this,               SLOT(setZoomVal(int)));

    connect(ui->plusButton, SIGNAL(clicked(bool)),
            this,           SLOT(addZoom()));
    connect(ui->minusButton, SIGNAL(clicked(bool)),
            this,            SLOT(reduceZoom()));

    setDesine();
}

void ZoomControllerWidget::setZoomVal(int p)
{
    if (p < minVal) p = minVal;
    if (p > maxVal) p = maxVal;

    curValue = p;

    if (sender() != ui->verticalSlider)
    {
        qDebug() << sender()->objectName();
    }

    zoomChanged((double)curValue/100);

    ui->Label->setText(QString::number(curValue) + "%");
}

void ZoomControllerWidget::setValSlider(int p)
{
    if (p < minVal) p = minVal;
    if (p > maxVal) p = maxVal;

    curValue = p;

    ui->verticalSlider->blockSignals(true);
    ui->verticalSlider->setValue(curValue);
    ui->verticalSlider->blockSignals(false);

    ui->Label->setText(QString::number(curValue) + "%");
}

void ZoomControllerWidget::addZoom()
{
    ui->verticalSlider->setValue(curValue + dZoom);
}

void ZoomControllerWidget::reduceZoom()
{
    ui->verticalSlider->setValue(curValue - dZoom);
}

void ZoomControllerWidget::setRangeValues(int minPer, int maxPer)
{
    minVal = minPer;
    maxVal = maxPer;

    ui->verticalSlider->setRange(minVal, maxVal);
}

void ZoomControllerWidget::setDesine()
{
    QString styleButton = "QPushButton{"
                          "   background-color:transparent;"
                          "   border: 1px solid rgb(55,55,55,0);"
                          "}"
                          "QPushButton:hover{"
                          "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                          "                                     stop: 0 rgb(255,252,254), "
                          "                                     stop: 0.3 rgb(209,226,248), "
                          "                                     stop: 1 rgb(251,252,254));"
                          "   border-radius: 5px;"
                          "   border: 1px solid rgb(150,183,227);"
                          "}"
                          "QPushButton:pressed{"
                          "   border: 1px solid rgb(255,165,0);"
                          "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                          "                                     stop: 0 rgb(255,252,254), "
                          "                                     stop: 0.4 rgb(255,204,60), "
                          "                                     stop: 1 rgb(255,251,230));"
                          "   color: rgb(102,51,0);"
                          "}";

    ui->plusButton->setStyleSheet(styleButton);
    ui->plusButton->setIcon(QIcon(":/resurs/plus.png"));
    ui->plusButton->setFixedSize(22, 22);

    ui->minusButton->setStyleSheet(styleButton);
    ui->minusButton->setIcon(QIcon(":/resurs/minus.png"));
    ui->minusButton->setFixedSize(22, 22);

    //
    ui->Label->setStyleSheet("QLabel {"
                             "   background-color: rgb(255,255,255,75);"
                             "   border-radius: 3px;"
                             "   border: 1px solid rgb(0,0,0);"
                             "}");

    ui->verticalSlider->setStyleSheet(
                "QSlider::handle:vertical {"
                "   height: 10px;"
                "   background-color: rgb(255,255,255,75);"
                "   border-radius: 3px;"
                "   border: 1px solid rgb(0,0,0);"
                "}"
                "QSlider::handle:vertical:hover {"
                "   height: 10px;"
                "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                "                                     stop: 0 rgb(255,252,254), "
                "                                     stop: 0.3 rgb(209,226,248), "
                "                                     stop: 1 rgb(251,252,254));"
                "   border: 1px solid rgb(150,183,227);"
                "   border-radius: 3px;"
                "}"
                "QSlider::handle:vertical:pressed{"
                "   height: 10px;"
                "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                "                                     stop: 0 rgb(255,252,254), "
                "                                     stop: 0.4 rgb(255,204,60), "
                "                                     stop: 1 rgb(255,251,230));"
                "   border: 1px solid rgb(255,165,0);"
                "   border-radius: 3px;"
                "}");
}

ZoomControllerWidget::~ZoomControllerWidget()
{
    delete ui;
}
