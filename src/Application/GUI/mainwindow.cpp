#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "designer.h"

#include "processtmpwidget.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    // Настройка визуала
    Designer::setMainWindow(this);

    // Кнопки вызова основных окон
    toolBar = new QToolBar("Панель задач");
    toolBar->setMovable(false);  // Чтоб пользователь не потерял его :)
    Designer::setToolBar(toolBar, Designer::whiteToolBox);
    addToolBar(Qt::TopToolBarArea, toolBar); //LeftToolBarArea

}

void mainWindow::showFunWindow()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());

    QDockWidget* dock = windows[button];
    if (dock->isVisible())
    {
        dock->hide();
    }
    else
    {
        dock->show();
    }
}

void mainWindow::addTask(QWidget *window,
                         const QIcon& iconButton,
                         const QString& nameButton,
                         const QString& nameWin,
                         Qt::DockWidgetArea showPosition)
{
    //
    QToolButton* button = new QToolButton;
    button->setIcon(iconButton);
    button->setToolTip(nameButton);

    toolBar->addWidget(button);

    //
    QDockWidget* dock = new QDockWidget(nameWin);
    this->addDockWidget(showPosition, dock);
    dock->setWidget(window);
    dock->close(); // Сразу закрываем чтобы не мешался

    //
    connect(button, SIGNAL(clicked(bool)),
            this,   SLOT(showFunWindow()));

    windows[button] = dock;
}

mainWindow::~mainWindow()
{
    delete ui;
}
