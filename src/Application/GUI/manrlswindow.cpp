#include "manrlswindow.h"
#include "ui_manrlswindow.h"

#include "./designer.h"

#include <QDockWidget>

manRLSWindow::manRLSWindow(GISInformer* gis,
                           InformerRLS* infoRLS):
    infoRLS(infoRLS),
    ui(new Ui::manRLSWindow)
{
    ui->setupUi(this);

    //
    connect(ui->removeRLSButton, SIGNAL(clicked()),
            this,                SLOT(removeRLS()));

    //
    connect(ui->listRLSTableWidget, SIGNAL(cellClicked(int,int)),
            this,                   SLOT(setIdCurRLS()));

    //
    connect(ui->addRLSButton, SIGNAL(clicked(bool)),
            this,             SIGNAL(addRLS()));

    //
    guiRLS = new InfoRLSWindow(gis);
    QDockWidget* dock = new QDockWidget("Управление РЛС");
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setWidget(guiRLS);
    dock->setTitleBarWidget(new QWidget(dock)); //
    dock->show();

    // Таблица-список РЛС, поставленных на карту
    ui->listRLSTableWidget->setColumnCount(columnNames.size());
    ui->listRLSTableWidget->setHorizontalHeaderLabels(columnNames);

    //
    loadingWidget = new processTmpWidget(this);

    setDesine();
}

void manRLSWindow::setIdCurRLS()
{
    // Индекс текущей РЛС
    int id = ui->listRLSTableWidget->currentRow();

    // Сообщить, что выбрана РЛС с индексом id
    setCurrentRLS(id);

    // Отобразить информацию по выбранной РЛС
    updateDataRLS(id);
}

void manRLSWindow::showInfoCurRLS()
{
    if (infoRLS->countRLS() > 0)
    {
        // График ДН антены
        repaintGraphic();
    }
}

void manRLSWindow::updateListRLS()
{
    // Очищаем все от устаревших строк
    ui->listRLSTableWidget->setRowCount(0);

    // Кол-во новых строк
    int countRLS = infoRLS->countRLS();
    ui->listRLSTableWidget->setRowCount(countRLS);

    //
    for (int r=0; r<countRLS; r++)
    {
        for (int p=0; p<3; p++)
            ui->listRLSTableWidget->setItem(r, p, new QTableWidgetItem);

        RLStoTable(r, infoRLS->getInfoRLS(r));
    }

    finishProcessing();
}

void manRLSWindow::updateDataRLS(int idRLS)
{
    // Информация об РЛС
    const LabelRLS* rls = infoRLS->getInfoRLS(idRLS);

    // Добавление(изменение) данных в таблице
    RLStoTable(idRLS, rls);

    // Расширенная информация
    guiRLS->showRLS(rls);

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
    ui->addRLSButton->setEnabled(true);
}

void manRLSWindow::removeRLS()
{
    //
    delRLS(ui->listRLSTableWidget->currentRow());

    //
    guiRLS->clearData();
}

void manRLSWindow::repaintGraphic()
{
    // Получаем данные
    QVector <double> X;
    QVector <double> Y;
    infoRLS->currentRLS()->getGraphicData(X, Y);

    // Отдаем на отрисовку
    guiRLS->setGraphicData(X, Y);
}

void manRLSWindow::setDesine()
{
    Designer::setMainWindow(this);

    // Начальное состояние
    ui->setRLSprogressBar->setValue(0);
    ui->setRLSprogressBar->hide(); // изначально прячем загрузку

    // Настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->listRLSGroupBox);

    // Настройка визуала кнопок
    Designer::setButton(ui->addRLSButton);
    Designer::setButton(ui->removeRLSButton, Designer::red);

    // Настройка визуала полоски прогресса
    Designer::setProgressBar(ui->setRLSprogressBar);

}

manRLSWindow::~manRLSWindow()
{
    delete ui;
}
