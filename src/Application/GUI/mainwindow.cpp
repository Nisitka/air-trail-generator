#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "designer.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    // Настройка визуала
    Designer::setMainWindow(this);
    this->setWindowTitle("Система прогнозирования маршрутов скрытного пролета БПЛА");

    // Кнопки вызова основных окон
    toolBar = new QToolBar("Панель задач");
    Designer::setToolBar(toolBar, Designer::whiteToolBox);
    addToolBar(Qt::TopToolBarArea, toolBar);
}

void mainWindow::addTask(QWidget *widget,
                         const QPixmap& pix,
                         const QString& nameButton,
                         const QString& nameWindow,
                         Qt::DockWidgetArea showPosition)
{
    // Вставка виджета в интерфейс
    QDockWidget* dock = new QDockWidget(nameWindow, this);
    Designer::setDockWidget(dock);

    dock->setWidget(widget);
    addDockWidget(showPosition, dock);

    //
    functionWindow* funcWin = new functionWindow(dock);

    // Создаем кнопку для вызова задачи
    toolBar->addAction(pix,     nameButton, // соеденяем его с кнопкой вызова
                       funcWin, SLOT(editShowStatus()));
    dock->close(); // Сразу закрываем чтобы не мешался
}

mainWindow::~mainWindow()
{
    delete ui;
}
