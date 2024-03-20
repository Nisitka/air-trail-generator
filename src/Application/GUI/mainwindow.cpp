#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    //
    this->setWindowTitle("Система прогнозирования маршрутов скрытного пролета БПЛА");

    // настройка визуала
    this->setStyleSheet("QMainWindow{"
                        "   background-color: rgb(201,214,234);"
                        "   border: 2px solid rgb(84,123,177);}");

    toolBar = new QToolBar("Панель задач");
    toolBar->setStyleSheet("QToolBar {"
                           "    border: 2px solid rgb(84,123,177);"
                           "    background-color: rgb(255,255,255);"
                           "}"
                           "QToolButton{"
                           "   background-color: rgb(255,255,255);"
                           "}"
                           "QToolButton:hover{"
                           "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                           "    border-color: rgb(0,0,0);"
                           "    border-style: outset;"
                           "    border-radius: 3px;"
                           "    border-width: 1px;"
                           "    border-color: rgb(0,0,0);"
                           "}"
                           "QToolButton:pressed{"
                           "    background-color : rgb(143,204,205); color: rgb(0,0,0);;"
                           "};");
    addToolBar(Qt::TopToolBarArea, toolBar); // добавляем в панель инструментов
}

void mainWindow::addTask(QWidget *widget,
                         const QPixmap& pix,
                         const QString& nameButton,
                         const QString& nameWindow,
                         Qt::DockWidgetArea showPosition)
{
    // вставка виджета в интерфейс
    QDockWidget* dock = new QDockWidget(nameWindow, this);
    dock->setStyleSheet("QDockWidget{"
                        "   background-color: rgb(201,214,234);"
                        "}");
    dock->setWidget(widget);
    addDockWidget(showPosition, dock);

    // создаем кнопку для вызова задачи
    toolBar->addAction(pix,  nameButton, // соеденяем его с кнопкой вызова
                       dock, SLOT(show()));

    dock->close(); // сразу закрываем чтобы не мешался
}

mainWindow::~mainWindow()
{
    delete ui;
}
