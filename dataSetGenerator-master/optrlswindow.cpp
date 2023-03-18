#include "optrlswindow.h"
#include "ui_optrlswindow.h"

#include "designer.h"

optRLSwindow::optRLSwindow(Map* map_, QWidget *parent) :
    map(map_),
    QWidget(parent),
    ui(new Ui::optRLSwindow)
{
    ui->setupUi(this);

    // настройка визуала кнопок
    Designer::setButton(ui->setCoordRLSpushButton);
    Designer::setButton(ui->setOptZDvertButton);

    // запуск моделирования работы РЛС по нажатию кнопки
    connect(ui->setCoordRLSpushButton, SIGNAL(clicked()),
            this,                      SLOT(runRLS()));
    ui->setRLSprogressBar->setValue(0);
    // настройка визуала полоски прогресса
    Designer::setProgressBar(ui->setRLSprogressBar);
    ui->setRLSprogressBar->hide(); // изначально прячем загрузку

    connect(ui->hZDspinBox, SIGNAL(valueChanged(int)),
            this,           SLOT(updateHZD(int)));

    // срез высоты ЗО по умолчанию
    hZD = 2000;
    hRLS = 0;

    connect(ui->hZDSlider, SIGNAL(sliderMoved(int)),
            this,          SLOT(updateHZD(int)));
    ui->hZDSlider->setMinimum(5);
    updateInfoMap();

    cPlot = ui->graphicDVWidget;

    cPlot->addGraph();
    cPlot->graph(0)->setPen(QPen(Qt::blue));
    cPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    //
    connect(ui->setOptZDvertButton, SIGNAL(clicked()),
            this,                   SLOT(setOptZDvert()));
    ui->RmaxSpinBox->setValue(2000);

    colorH = new QColor;
}

void optRLSwindow::repaintGraphic(double* x, double* y, int count)
{
    QVector <double> X(count), Y(count);
    double Xmax = 0;
    double Ymax = 0;
    for (int i=0; i<count; i++)
    {
        X[i] = x[i];
        if (Xmax < x[i]) Xmax = x[i];

        Y[i] = y[i];
        if (Ymax < y[i]) Ymax = y[i];
    }
    delete [] x;
    delete [] y;

    //qDebug() << X << Y;

    cPlot->graph(0)->setData(X, Y, true);

    cPlot->xAxis->setRange(0, Xmax + 100);
    cPlot->xAxis2->setRange(0, Xmax + 100);

    cPlot->yAxis->setRange(0, Ymax + 100);
    cPlot->yAxis2->setRange(0, Ymax + 100);

    cPlot->replot();
}

void optRLSwindow::readyOptZDvert()
{
    ui->setOptZDvertButton->setEnabled(true);
    ui->setCoordRLSpushButton->setEnabled(true);

    cursor = Qt::ArrowCursor;
    this->setCursor(cursor);
}

void optRLSwindow::setOptZDvert()
{
    ui->setOptZDvertButton->setEnabled(false);
    updateOptZDvert(ui->RmaxSpinBox->value());

    ui->setCoordRLSpushButton->setEnabled(false);

    cursor = Qt::WaitCursor;
    this->setCursor(cursor);
}

void optRLSwindow::updateCoordRLS(int x, int y)
{
    double l = map->getLenBlock();

    xRLS = x;
    yRLS = y;
    hRLS = map->getHeight(xRLS, yRLS) ;

    ui->xRLSspinBox->setValue(xRLS * l);
    ui->yRLSspinBox->setValue(yRLS * l);
    ui->zValueRLSLabel->setText(QString::number(hRLS * l));

    // автоматически выставляем срез высоты на 10м больше высоты РЛС
    if (hZD < hRLS * l + 10)
    {
        hZD = hRLS * l + 10;
    }
    ui->hZDSlider->setMinimum(hRLS * l + 10);

    ui->hZDspinBox->setValue(hZD);
    updateColorH();
}

void optRLSwindow::readyVector(int numVector)
{
    ui->setRLSprogressBar->setValue(numVector);
}

void optRLSwindow::finishGenerateZD()
{
    ui->setRLSprogressBar->setValue(0);
    ui->setRLSprogressBar->hide();
}

void optRLSwindow::runRLS()
{
    signalRunRLS(xRLS,
                 yRLS,
                 hZD / map->getLenBlock());
}

void optRLSwindow::updateInfoMap()
{
    ui->hZDSlider->setMaximum(map->getCountLayers() * map->getLenBlock());
}

void optRLSwindow::updateHZD(int value)
{
    double l = map->getLenBlock();

    // автоматически выставляем срез высоты на 10м больше высоты РЛС
    if (value < hRLS * l + 10)
    {
        value = hRLS * l + 10;
        ui->hZDSlider->setMinimum(value);
    }
    hZD = value;

    // обновление визуала
    ui->hZDspinBox->setValue(hZD);
    ui->hZDSlider->setValue(hZD);
    updateColorH();
}

void optRLSwindow::updateColorH()
{
    getColorHeight(colorH, hZD / map->getLenBlock());
    int r = colorH->red();
    int g = colorH->green();
    int b = colorH->blue();
    ui->colorHLabel->setStyleSheet(
                "QLabel {"
                    "background-color: rgb("
                    + QString::number(r) + ","
                    + QString::number(g) + ","
                    + QString::number(b) + ");"
                    "color: rgb(0,0,0);"

                    "border-style: outset;"
                    "border-radius: 3px;"
                    "border-width: 2px;"
                    "border-color: rgb(0,0,0);"
                "}"
                        );
}

void optRLSwindow::startGenerateZD(int countVectors)
{
    ui->setRLSprogressBar->setMaximum(countVectors);
    ui->setRLSprogressBar->show();
}

optRLSwindow::~optRLSwindow()
{
    delete ui;
}
