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

    //
    setStatusBar(nullptr);
}

void mainWindow::showFunWindow()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());

    QDockWidget* dock = windows[button];
    if (dock->isVisible())
        dock->hide();
    else
        dock->show();
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
    dock->setStyleSheet("QDockWidget::title { "
                        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                        "                                     stop: 0 rgb(255,252,254), "
                        "                                     stop: 0.3 rgb(209,226,248), "
                        "                                     stop: 1 rgb(251,252,254));"
                        "   border: 1px solid rgb(150,183,227);"
                        "   text-align: left;"
                        "   color: rgb(34,69,157);"
                        "   padding-left: 5px; "
                        "};");

    //
    connect(button, SIGNAL(clicked(bool)),
            this,   SLOT(showFunWindow()));

    windows[button] = dock;
}

mainWindow::~mainWindow()
{
    delete ui;
}
