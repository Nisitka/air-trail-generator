#include "optrlswindow.h"
#include "ui_optrlswindow.h"

#include "designer.h"

#include <QDebug>

optRLSwindow::optRLSwindow( QWidget *parent):
    QWidget(parent),
    ui(new Ui::optRLSwindow)
{
    ui->setupUi(this);

    workingCurRLS = false;

    //
    connect(ui->setCoordRLSpushButton, SIGNAL(clicked()),
            this,                      SLOT(setNewPosRLS()));

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

    //
    loadingWidget = new processTmpWidget(this);

    setDesine();
}

void optRLSwindow::startProcessing()
{
    ui->setOptRLSProgressBar->show();
    ui->setOptRLSProgressBar->setRange(0,0);

}

void optRLSwindow::updateStatProcessing(int percent)
{
    ui->setOptRLSProgressBar->setMaximum(100);
    ui->setOptRLSProgressBar->setValue(percent);
}

void optRLSwindow::finishProcessing()
{
    ui->setOptRLSProgressBar->hide();
}

void optRLSwindow::runSearchBestPos()
{
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
    //
    loadingWidget->Show();

    // Передаем исх. данные для создания РЛС в менеджер станций
    createRLS(new QPoint(RLScoords.X(Coords::id), RLScoords.Y(Coords::id)),
              ui->nameNewRLSLineEdit->text());

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
    loadingWidget->Hide();

    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //updateCoordRLS(Xpos, Ypos);
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
    // Начальное состояние
    ui->setRLSprogressBar->setValue(0);
    ui->setRLSprogressBar->hide(); // изначально прячем загрузку

    ui->setOptRLSProgressBar->setValue(0);
    ui->setOptRLSProgressBar->hide();

    ui->on_off_RLS_Button->hide();
    ui->setCoordRLSpushButton->hide();

    // Настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->RmaxGroupBox);
    Designer::setGroupBox(ui->ZDvertGroupBox);
    Designer::setGroupBox(ui->coordRLSgroupBox);
    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->addRLSGroupBox);
    Designer::setGroupBox(ui->nameNewRLSGroupBox);
    Designer::setGroupBox(ui->listRLSGroupBox);
    Designer::setGroupBox(ui->optionsGroupBox);

    // Настройка визуала кнопок
    Designer::setButton(ui->setCoordRLSpushButton);
    Designer::setButton(ui->setOptZDvertButton);
    Designer::setButton(ui->createRLSButton);
    Designer::setButton(ui->removeRLSButton, Designer::red);

    // Настройка визуала полоски прогресса
    Designer::setProgressBar(ui->setRLSprogressBar);
    Designer::setProgressBar(ui->setOptRLSProgressBar);

    //
    Designer::setTabWidget(ui->generateDVOptTabWidget);

    // Изначально кнопка в таком состоянии
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
        signalRunRLS();
        workingCurRLS = true;
        Designer::setButton(ui->on_off_RLS_Button, Designer::red);
        ui->on_off_RLS_Button->setText("Выключить");
    }
}

void optRLSwindow::setNewPosRLS()
{
    // Значения с интерфейса
    int l = RLScoords.longStep();
    int idX = ui->xRLSspinBox->value() / l;
    int idY = ui->yRLSspinBox->value() / l;

    setPositionRLS(idX, idY);
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

void optRLSwindow::updateCoordRLS(Coords coords)
{
    RLScoords = coords;

    //
    ui->xRLSspinBox->setValue(RLScoords.X(Coords::m));
    ui->yRLSspinBox->setValue(RLScoords.Y(Coords::m));
    ui->zValueRLSLabel->setText(QString::number(RLScoords.Y(Coords::m)));
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

void optRLSwindow::startGenerateZD(int countVectors)
{
    ui->setRLSprogressBar->setMaximum(countVectors);
    ui->setRLSprogressBar->show();
}

optRLSwindow::~optRLSwindow()
{
    delete ui;
}
