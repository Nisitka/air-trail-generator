#include "optrlswindow.h"
#include "ui_optrlswindow.h"

#include "designer.h"

#include <QDebug>

#include <QTableWidgetItem>

optRLSwindow::optRLSwindow(InformerRLS* infoRLS, QWidget *parent):
    infoRLS(infoRLS), QWidget(parent),
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
    connect(ui->on_off_RLS_Button, SIGNAL(clicked()),
            this,                  SLOT(enablingRLS()));

    //
    connect(ui->listRLSTableWidget, SIGNAL(cellClicked(int,int)),
            this,                   SLOT(setIdCurRLS()));


    // Виджет для отрисорвки графика ЗО РЛС
    graphicWidget = new plotWidget;
    ui->plotZDLayout->addWidget(graphicWidget);

    // Таблица-список РЛС, поставленных на карту
    ui->listRLSTableWidget->setColumnCount(columnNames.size());
    ui->listRLSTableWidget->setHorizontalHeaderLabels(columnNames);

    //
    loadingWidget = new processTmpWidget(this);

    setDesine();
}

void optRLSwindow::setIdCurRLS()
{
    idCurRLS = ui->listRLSTableWidget->currentRow();

    qDebug() << "Id current RLS: " << idCurRLS;

    setRLS(idCurRLS);
}

void optRLSwindow::updateListRLS()
{
    // Очищаем все от устаревших строк
    ui->listRLSTableWidget->setRowCount(0);

    // Кол-во новых строк
    int countRLS = infoRLS->countRLS();
    ui->listRLSTableWidget->setRowCount(countRLS);

    QTableWidgetItem* item;
    QColor stat;
    QVector3D pos;
    for (int r=0; r<countRLS; r++)
    {
        const LabelRLS* rls = infoRLS->getInfoRLS(r);

        //
        ui->listRLSTableWidget->setItem(r, 0, new QTableWidgetItem(rls->getName()));

        //
        if (rls->isWorking()) stat = Qt::green;
        else stat = Qt::red;

        item = new QTableWidgetItem;
        item->setBackgroundColor(stat);
        ui->listRLSTableWidget->setItem(r, 1, item);

        rls->getPosition(pos);
        QString coords = QString::number(pos.x()) + "; " + QString::number(pos.y());
        ui->listRLSTableWidget->setItem(r, 2, new QTableWidgetItem(coords));
    }

    finishProcessing();
}

void optRLSwindow::startProcessing()
{
    ui->setRLSprogressBar->show();
    ui->setRLSprogressBar->setRange(0,0);

}

void optRLSwindow::updateStatProcessing(int percent)
{
    //qDebug() << percent;

    ui->setRLSprogressBar->setMaximum(100);
    ui->setRLSprogressBar->setValue(percent);
}

void optRLSwindow::finishProcessing()
{
    ui->setRLSprogressBar->hide();

    // Разблокируем кнопку добавления РЛС
    ui->createRLSButton->setEnabled(true);
}

void optRLSwindow::removeRLS()
{
    //
    setIdCurRLS();

    //
    delRLS(idCurRLS);

    // Очищаем виджет от графика удаленной РЛС
    graphicWidget->clear();
}

void optRLSwindow::addRLS()
{   
    startProcessing();

    // Передаем исх. данные для создания РЛС в менеджер станций
    createRLS(new QPoint(RLScoords.X(Coords::id), RLScoords.Y(Coords::id)),
              ui->nameNewRLSLineEdit->text());

    //
    ui->nameNewRLSLineEdit->clear();

    // разблокируем кнопку удаления РЛС
    ui->removeRLSButton->setEnabled(true);

    // блокируем кнопку добавления РЛС пока не пройдет инициализация этой
    ui->createRLSButton->setEnabled(false);
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
}

void optRLSwindow::setDesine()
{
    // Начальное состояние
    ui->setRLSprogressBar->setValue(0);
    ui->setRLSprogressBar->hide(); // изначально прячем загрузку

    ui->on_off_RLS_Button->hide();
    ui->setCoordRLSpushButton->hide();

    // Настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->RmaxGroupBox);
    Designer::setGroupBox(ui->ZDvertGroupBox);
    Designer::setGroupBox(ui->coordRLSgroupBox);
    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
    Designer::setGroupBox(ui->nameNewRLSGroupBox);
    Designer::setGroupBox(ui->listRLSGroupBox);
    Designer::setGroupBox(ui->optionsGroupBox);
    Designer::setGroupBox(ui->manRLSGroupBox);

    // Настройка визуала кнопок
    Designer::setButton(ui->setCoordRLSpushButton);
    Designer::setButton(ui->setOptZDvertButton);
    Designer::setButton(ui->createRLSButton);
    Designer::setButton(ui->removeRLSButton, Designer::red);

    // Настройка визуала полоски прогресса
    Designer::setProgressBar(ui->setRLSprogressBar);

    //
    Designer::setTabWidget(ui->generateDVOptTabWidget);
    Designer::setTabWidget(ui->mainTabWidget);

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

void optRLSwindow::setOptZDvert()
{
    //ui->setOptZDvertButton->setEnabled(false);
    updateOptZDvert(ui->RmaxSpinBox->value(),
                    ui->countHorVecZDSpinBox->value(),
                    ui->countPointsDVSpinBox->value());

    //ui->setCoordRLSpushButton->setEnabled(false);
}

void optRLSwindow::updateCoordRLS(Coords coords)
{
    RLScoords = coords;

    //
    ui->xRLSspinBox->setValue(RLScoords.X(Coords::m));
    ui->yRLSspinBox->setValue(RLScoords.Y(Coords::m));
    ui->zValueRLSLabel->setText(QString::number(RLScoords.Y(Coords::m)));
}

optRLSwindow::~optRLSwindow()
{
    delete ui;
}
