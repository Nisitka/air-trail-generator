#include "manrlswindow.h"
#include "ui_manrlswindow.h"

#include "./designer.h"

manRLSWindow::manRLSWindow(InformerRLS* infoRLS):
    infoRLS(infoRLS),
    ui(new Ui::manRLSWindow)
{
    ui->setupUi(this);

    //
    connect(ui->setCoordRLSpushButton, SIGNAL(clicked()),
            this,                      SLOT(setNewPosRLS()));

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

void manRLSWindow::setIdCurRLS()
{
    setCurrentRLS(ui->listRLSTableWidget->currentRow());
}

void manRLSWindow::showInfoCurRLS()
{
    if (infoRLS->countRLS() > 0)
    {
        // График ДН антены
        repaintGraphic();

        // Статус кнопки вкл/выкл
        ui->on_off_RLS_Button->show();
        if (infoRLS->currentRLS()->isWorking())
        {
            Designer::setButton(ui->on_off_RLS_Button, Designer::red);
            ui->on_off_RLS_Button->setText("Выключить");
        }
        else
        {
            Designer::setButton(ui->on_off_RLS_Button, Designer::green);
            ui->on_off_RLS_Button->setText("Включить");
        }
    }
}

void manRLSWindow::updateListRLS()
{
    // Очищаем все от устаревших строк
    ui->listRLSTableWidget->setRowCount(0);

    // Кол-во новых строк
    int countRLS = infoRLS->countRLS();
    ui->listRLSTableWidget->setRowCount(countRLS);

    if (countRLS > 0)
    {
        for (int r=0; r<countRLS; r++)
        {
            for (int p=0; p<3; p++)
                ui->listRLSTableWidget->setItem(r, p, new QTableWidgetItem);

            RLStoTable(r, infoRLS->getInfoRLS(r));
        }
    }
    else
    {
        ui->on_off_RLS_Button->hide();
    }

    finishProcessing();
}

void manRLSWindow::updateDataRLS(int idRLS)
{
    RLStoTable(idRLS, infoRLS->getInfoRLS(idRLS));
}

void manRLSWindow::RLStoTable(int numStr, const LabelRLS *rls)
{
    QTableWidget* table = ui->listRLSTableWidget;

    //
    table->item(numStr, 0)->setText(rls->getName());

    //
    QColor stat;
    if (rls->isWorking()) stat = Qt::green;
    else stat = Qt::red;
    table->item(numStr, 1)->setBackgroundColor(stat);

    //
    QVector3D pos;
    rls->getPosition(pos);
    QString coords = QString::number(pos.x()) + "; " + QString::number(pos.y());
    table->item(numStr, 2)->setText(coords);
}

void manRLSWindow::startProcessing()
{
    ui->setRLSprogressBar->show();
    ui->setRLSprogressBar->setRange(0,0);
}

void manRLSWindow::updateStatProcessing(int percent)
{
    //qDebug() << percent;

    ui->setRLSprogressBar->setMaximum(100);
    ui->setRLSprogressBar->setValue(percent);
}

void manRLSWindow::finishProcessing()
{
    ui->setRLSprogressBar->hide();

    // Разблокируем кнопку добавления РЛС
    ui->createRLSButton->setEnabled(true);
}

void manRLSWindow::removeRLS()
{
    //
    delRLS(ui->listRLSTableWidget->currentRow());

    // Очищаем виджет от графика удаленной РЛС
    graphicWidget->clear();
}

void manRLSWindow::addRLS()
{
    startProcessing();

    // Передаем исх. данные для создания РЛС в менеджер станций
    createRLS(QPoint(RLScoords.X(Coords::id), RLScoords.Y(Coords::id)),
              ui->nameNewRLSLineEdit->text());

    //
    ui->nameNewRLSLineEdit->clear();

    // разблокируем кнопку удаления РЛС
    ui->removeRLSButton->setEnabled(true);

    // блокируем кнопку добавления РЛС пока не пройдет инициализация этой
    ui->createRLSButton->setEnabled(false);
}

void manRLSWindow::enablingRLS()
{
    if (infoRLS->currentRLS()->isWorking())
    {
        offRLS();
        Designer::setButton(ui->on_off_RLS_Button, Designer::green);
        ui->on_off_RLS_Button->setText("Включить");
    }
    else
    {
        runRLS();
        Designer::setButton(ui->on_off_RLS_Button, Designer::red);
        ui->on_off_RLS_Button->setText("Выключить");
    }
}

void manRLSWindow::setNewPosRLS()
{
    // Значения с интерфейса
    int l = RLScoords.longStep();
    int idX = ui->xRLSspinBox->value() / l;
    int idY = ui->yRLSspinBox->value() / l;

    setPositionRLS(idX, idY);
}

void manRLSWindow::repaintGraphic()
{
    QVector <double> X;
    QVector <double> Y;
    infoRLS->currentRLS()->getGraphicData(X, Y);

    //
    graphicWidget->setData(X, Y);
}

void manRLSWindow::updateCoordRLS(Coords coords)
{
    RLScoords = coords;

    //
    ui->xRLSspinBox->setValue(RLScoords.X(Coords::m));
    ui->yRLSspinBox->setValue(RLScoords.Y(Coords::m));
    ui->zValueRLSLabel->setText(QString::number(RLScoords.Y(Coords::m)));
}

void manRLSWindow::setDesine()
{
    Designer::setMainWindow(this);

    // Начальное состояние
    ui->setRLSprogressBar->setValue(0);
    ui->setRLSprogressBar->hide(); // изначально прячем загрузку

    ui->on_off_RLS_Button->hide();
    ui->setCoordRLSpushButton->hide();

    // Настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->ZDvertGroupBox);
    Designer::setGroupBox(ui->coordRLSgroupBox);
    Designer::setGroupBox(ui->nameNewRLSGroupBox);
    Designer::setGroupBox(ui->listRLSGroupBox);
    Designer::setGroupBox(ui->manRLSGroupBox);

    // Настройка визуала кнопок
    Designer::setButton(ui->setCoordRLSpushButton);
    Designer::setButton(ui->createRLSButton);
    Designer::setButton(ui->removeRLSButton, Designer::red);

    // Настройка визуала полоски прогресса
    Designer::setProgressBar(ui->setRLSprogressBar);

    //
    Designer::setTabWidget(ui->generateDVOptTabWidget);

    // Изначально кнопка в таком состоянии
    Designer::setButton(ui->on_off_RLS_Button, Designer::green);
}

manRLSWindow::~manRLSWindow()
{
    delete ui;
}
