#include "optrlswindow.h"
#include "ui_optrlswindow.h"

#include "designer.h"

optRLSwindow::optRLSwindow(Map* map_, QWidget *parent) :
    map(map_),
    QWidget(parent),
    ui(new Ui::optRLSwindow)
{
    ui->setupUi(this);

    workingCurRLS = false;

    //
    connect(ui->setCoordRLSpushButton, SIGNAL(clicked()),
            this,                      SLOT(setNewPosRLS()));

    ui->setRLSprogressBar->setValue(0);
    ui->setRLSprogressBar->hide(); // изначально прячем загрузку

    ui->setOptRLSProgressBar->setValue(0);
    ui->setOptRLSProgressBar->hide();

    connect(ui->hZDspinBox, SIGNAL(valueChanged(int)),
            this,           SLOT(updateHZD(int)));

    // срез высоты ЗО по умолчанию
    hZD = 2000;
    hRLS = 0;

    connect(ui->hZDSlider, SIGNAL(sliderMoved(int)),
            this,          SLOT(updateHZD(int)));
    ui->hZDSlider->setMinimum(5);
    updateInfoMap();

    ui->on_off_RLS_Button->hide();
    ui->setCoordRLSpushButton->hide();

    //
    connect(ui->setOptZDvertButton, SIGNAL(clicked()),
            this,                   SLOT(setOptZDvert()));
    ui->RmaxSpinBox->setValue(2000);

    //
    connect(ui->createRLSButton, SIGNAL(clicked()),
            this,                SLOT(addRLS()));

    //
    connect(ui->removeRLSButton, SIGNAL(clicked()),
            this,                SLOT(removeRLS()));

    //
    connect(ui->listRLSComboBox, SIGNAL(currentIndexChanged(int)),
            this,                SIGNAL(setRLS(int)));

    //
    connect(ui->on_off_RLS_Button, SIGNAL(clicked()),
            this,                  SLOT(enablingRLS()));

    // Виджет для отрисорвки графика ЗО РЛС
    graphicWidget = new plotWidget;
    ui->plotZDLayout->addWidget(graphicWidget);

    setDesine();
}

void optRLSwindow::runSearchBestPos()
{
    //qDebug() << "sear"
    sendDataForSearchBestPos(0, 0, 100, 100, 200);
}

void optRLSwindow::removeRLS()
{
    if (ui->listRLSComboBox->count() > 0)
    {
        int id = ui->listRLSComboBox->currentIndex();

        delRLS(id);
        ui->listRLSComboBox->removeItem(id);

        if (ui->listRLSComboBox->count() == 0)
        {
            ui->removeRLSButton->setEnabled(false);
            ui->on_off_RLS_Button->setEnabled(false);
            ui->setCoordRLSpushButton->setEnabled(false);

            ui->on_off_RLS_Button->hide();
            ui->setCoordRLSpushButton->hide();
        }
    }

    // Очищаем виджет от графика удаленной РЛС
    graphicWidget->clear();
}

void optRLSwindow::addRLS()
{   
    // значения с интерфейса
    xRLS = ui->xRLSspinBox->value() / map->getLenBlock();
    yRLS = ui->yRLSspinBox->value() / map->getLenBlock();

    // создаем объект и передаем его адрес в менеджер РЛС
    createRLS(new QPoint(xRLS, yRLS), ui->nameNewRLSLineEdit->text()); //ui->nameNewRLSLineEdit->text()

    ui->listRLSComboBox->addItem(ui->nameNewRLSLineEdit->text());
    ui->nameNewRLSLineEdit->clear();

    // разблокируем кнопку удаления РЛС
    ui->removeRLSButton->setEnabled(true);

    // блокируем кнопку добавления РЛС пока не пройдет инициализация этой
    ui->createRLSButton->setEnabled(false);
}

void optRLSwindow::buildNewRLSready()
{
    // выбираем помледнию РЛС
    ui->listRLSComboBox->setCurrentIndex(ui->listRLSComboBox->count() - 1);
}

void optRLSwindow::setOptRLS(int Rmax, int Xpos, int Ypos, int Hzd, bool working)
{
    updateCoordRLS(Xpos, Ypos);
    updateHZD(Hzd);
    ui->RmaxSpinBox->setValue(Rmax);

    workingCurRLS = working;
    if (workingCurRLS)
    {
        Designer::setButton(ui->on_off_RLS_Button, Designer::red);
        ui->on_off_RLS_Button->setText("Выключить");
    }
    else
    {
        Designer::setButton(ui->on_off_RLS_Button, Designer::green);
        ui->on_off_RLS_Button->setText("Включить");
    }

    ui->createRLSButton->setEnabled(true);

    //
    if (ui->listRLSComboBox->count() == 1)
    {
        ui->on_off_RLS_Button->setEnabled(true);
        ui->setCoordRLSpushButton->setEnabled(true);

        ui->on_off_RLS_Button->show();
        ui->setCoordRLSpushButton->show();
    }
}

void optRLSwindow::setDesine()
{
    // настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->RmaxGroupBox);
    Designer::setGroupBox(ui->ZDvertGroupBox);
    Designer::setGroupBox(ui->HRLSgroupBox);
    Designer::setGroupBox(ui->coordRLSgroupBox);
    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->addRLSGroupBox);
    Designer::setGroupBox(ui->nameNewRLSGroupBox);
    Designer::setGroupBox(ui->listRLSGroupBox);
    Designer::setGroupBox(ui->optionsGroupBox);

    // настройка визуала кнопок
    Designer::setButton(ui->setCoordRLSpushButton);
    Designer::setButton(ui->setOptZDvertButton);
    Designer::setButton(ui->createRLSButton);
    Designer::setButton(ui->removeRLSButton, Designer::red);

    // настройка визуала полоски прогресса
    Designer::setProgressBar(ui->setRLSprogressBar);
    Designer::setProgressBar(ui->setOptRLSProgressBar);

    //
    Designer::setTabWidget(ui->generateDVOptTabWidget);

    // изначально кнопка в таком состоянии
    Designer::setButton(ui->on_off_RLS_Button, Designer::green);
}

void optRLSwindow::enablingRLS()
{
    if (workingCurRLS)
    {
        signalOffRLS();
        workingCurRLS = false;
        Designer::setButton(ui->on_off_RLS_Button, Designer::green);
        ui->on_off_RLS_Button->setText("Включить");
    }
    else
    {
        signalRunRLS(hZD / map->getLenBlock());
        workingCurRLS = true;
        Designer::setButton(ui->on_off_RLS_Button, Designer::red);
        ui->on_off_RLS_Button->setText("Выключить");
    }
}

void optRLSwindow::setNewPosRLS()
{
    // значения с интерфейса
    xRLS = ui->xRLSspinBox->value() / map->getLenBlock();
    yRLS = ui->yRLSspinBox->value() / map->getLenBlock();

    setPositionRLS(xRLS, yRLS);
}

void optRLSwindow::repaintGraphic(double* x, double* y, int count)
{
    QVector <float> X(count), Y(count);
    for (int i=0; i<count; i++)
    {
        X[i] = x[i];
        Y[i] = y[i];
    }
    delete [] x;
    delete [] y;

    graphicWidget->setData(X, Y);
}

void optRLSwindow::readyOptZDvert()
{
    ui->setOptZDvertButton->setEnabled(true);
    ui->setCoordRLSpushButton->setEnabled(true);

    ui->setOptRLSProgressBar->hide();
}

void optRLSwindow::setOptZDvert()
{
    ui->setOptZDvertButton->setEnabled(false);
    updateOptZDvert(ui->RmaxSpinBox->value(),
                    ui->countHorVecZDSpinBox->value(), ui->countPointsDVSpinBox->value());

    ui->setCoordRLSpushButton->setEnabled(false);

    ui->setOptRLSProgressBar->show();
}

void optRLSwindow::startSetOptRLS(int sizeP)
{
    ui->setOptRLSProgressBar->setValue(0);
    ui->setOptRLSProgressBar->setMaximum(sizeP);
}

void optRLSwindow::updateProgressSetOptRLS(int id)
{
    ui->setOptRLSProgressBar->setValue(id);
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
