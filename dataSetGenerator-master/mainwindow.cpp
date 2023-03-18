#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    //
    this->setWindowTitle("");

    // настройка визуала
    //this->setStyleSheet("background-color: rgb(81,83,85);");

    toolBarBuildDS = new QToolBar("Панель инструментов");
    toolBarBuildDS->setStyleSheet("background-color: rgb(240,240,240);");
    addToolBar(Qt::TopToolBarArea, toolBarBuildDS); // добавляем в панель инструментов

    toolBarUsedNet = new QToolBar("Панель инструментов");
    toolBarUsedNet->setStyleSheet("background-color: rgb(240,240,240);");
    addToolBar(Qt::TopToolBarArea, toolBarUsedNet);
}

void mainWindow::addTask(QWidget *widget,
                         const QPixmap& pix,
                         const QString& nameButton,
                         const QString& nameWindow,
                         typeTask type)
{
    // вставка виджета в интерфейс
    QDockWidget* dock = new QDockWidget(nameWindow, this);
    dock->setWidget(widget);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    // создаем кнопку для вызова задачи
    switch (type) {
    case dataSet:
        toolBarBuildDS->addAction(pix,  nameButton, // соеденяем его с кнопкой вызова
                                  dock, SLOT(show()));
        break;
    case usedNet:
        toolBarUsedNet->addAction(pix,  nameButton, // соеденяем его с кнопкой вызова
                                  dock, SLOT(show()));
        break;
    }
    dock->close(); // сразу закрываем чтобы не мешался
}

mainWindow::~mainWindow()
{
    delete ui;
}
