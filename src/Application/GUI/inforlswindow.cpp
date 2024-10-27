#include "inforlswindow.h"
#include "ui_inforlswindow.h"

#include "designer.h"

InfoRLSWindow::InfoRLSWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoRLSWindow)
{
    ui->setupUi(this);
    setDesine();

    // Виджет для отрисорвки графика ЗО РЛС
    graphicWidget = new plotWidget;
    ui->plotZDLayout->addWidget(graphicWidget);
}

void InfoRLSWindow::clearData()
{
    // Очищаем виджет от графика удаленной РЛС
    graphicWidget->clear();
}

void InfoRLSWindow::setGraphicData(const QVector<double> &X, const QVector<double> &Y)
{
    //
    graphicWidget->setData(X, Y);
}

void InfoRLSWindow::setDesine()
{
    // Настройка визуала GroupBox-ов
    Designer::setGroupBox(ui->coordRLSgroupBox);
    Designer::setGroupBox(ui->mainGroupBox);

    // Настройка визуала кнопок
    Designer::setButton(ui->setCoordRLSpushButton);

    // Изначально кнопка в таком состоянии
    Designer::setButton(ui->on_off_RLS_Button, Designer::green);

    //
    Designer::setTabWidget(ui->generateDVOptTabWidget);
}

InfoRLSWindow::~InfoRLSWindow()
{
    delete ui;
}
