#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    toolBar = new QToolBar("Панель инструментов");
    addToolBar(Qt::TopToolBarArea, toolBar); // добавляем в панель инструментов
}

void mainWindow::addTask(QWidget *widget,
                         const QPixmap& pix,
                         const QString& nameButton,
                         const QString& nameWindow)
{
    // вставка виджета в интерфейс
    QDockWidget* dock = new QDockWidget(nameWindow, this);
    dock->setWidget(widget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    // создаем кнопку для вызова задачи
    toolBar->addAction(pix, nameButton, // соеденяем его с кнопкой вызова
                      dock, SLOT(show()));
    dock->close(); // сразу закрываем чтобы не мешался
}

mainWindow::~mainWindow()
{
    delete ui;
}
