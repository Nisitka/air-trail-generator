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
    this->setStyleSheet("QMainWindow{"
                        "   background-color: rgb(201,214,234);"
                        "   border: 2px solid rgb(84,123,177);}");

    toolBarBuildDS = new QToolBar("Панель инструментов");
    toolBarBuildDS->setStyleSheet("QToolBar {"
                                  "    border: 2px solid rgb(84,123,177);"
                                  "    background-color: rgb(255,255,255);"
                                  "};");
    addToolBar(Qt::TopToolBarArea, toolBarBuildDS); // добавляем в панель инструментов

    toolBarUsedNet = new QToolBar("Панель инструментов");
    toolBarUsedNet->setStyleSheet("QToolBar {"
                                  "    border: 2px solid rgb(84,123,177);"
                                  "    background-color: rgb(255,255,255);"
                                  "};");
    addToolBar(Qt::TopToolBarArea, toolBarUsedNet);
}

void mainWindow::addTask(QWidget *widget,
                         const QPixmap& pix,
                         const QString& nameButton,
                         const QString& nameWindow,
                         typeTask type,
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
