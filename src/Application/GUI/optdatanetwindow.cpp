#include "optdatanetwindow.h"
#include "ui_optdatanetwindow.h"

#include "designer.h"

#include <QDebug>

optDataNetWindow::optDataNetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optDataNetWindow)
{
    ui->setupUi(this);

    connect(ui->genDataNetButton, SIGNAL(clicked()),
            this,                 SIGNAL(generateImage()));
    connect(ui->setDefaultKrgbButton, SIGNAL(clicked()),
            this,                     SLOT(setDefaultK()));

    // движение ползунка сразу же обновляет коофициенты
    connect(ui->kG1Slider, SIGNAL(sliderReleased()),
            this,          SLOT(setKrgb()));
    connect(ui->kG2Slider, SIGNAL(sliderReleased()),
            this,          SLOT(setKrgb()));
    connect(ui->kG3Slider, SIGNAL(sliderReleased()),
            this,          SLOT(setKrgb()));
    connect(ui->kG4Slider, SIGNAL(sliderReleased()),
            this,          SLOT(setKrgb()));

    setDesine();
}

void optDataNetWindow::startGenerateImg(int sizeP)
{
    ui->genDNProgressBar->setValue(0);
    ui->genDNProgressBar->setMaximum(sizeP);
    ui->genDNProgressBar->show();
}

void optDataNetWindow::updateProgressGenDN(int id)
{
    ui->genDNProgressBar->setValue(id);
}

void optDataNetWindow::finishGenerateImg()
{
    ui->genDNProgressBar->hide();
}

void optDataNetWindow::setDefaultK()
{
    ui->kG1Slider->setValue(838 / maxK1);
    ui->kG2Slider->setValue(75 / maxK2);
    ui->kG3Slider->setValue(299 / maxK3);
    ui->kG4Slider->setValue(1696 / maxK4);

    setKrgb();
}

void optDataNetWindow::setKrgb()
{
    double gK1, gK2, gK3, gK4;
    gK1 = (double)((double) ui->kG1Slider->value() / MAX_VAL_SLI) * maxK1;
    gK2 = (double)((double) ui->kG2Slider->value() / MAX_VAL_SLI) * maxK2;
    gK3 = (double)((double) ui->kG3Slider->value() / MAX_VAL_SLI) * maxK3;
    gK4 = (double)((double) ui->kG4Slider->value() / MAX_VAL_SLI) * maxK4;

    //qDebug() << gK1 << gK2 << gK3 << gK4;
    updateKrgb(gK1, gK2, gK3, gK4, 0.02);

    generateImage();
}

void optDataNetWindow::setDesine()
{
    // настройка визуала кнопок
    Designer::setButton(ui->genDataNetButton);
    Designer::setButton(ui->setDefaultKrgbButton, Designer::red);

    // настройка визула TabWidget-ов
    Designer::setTabWidget(ui->tabWidget);

    // настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->rgbGroupBox);
    Designer::setGroupBox(ui->buildDataGroupBox);

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);

    Designer::setProgressBar(ui->genDNProgressBar);
    ui->genDNProgressBar->hide();
}

optDataNetWindow::~optDataNetWindow()
{
    delete ui;
}
