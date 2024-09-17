#include "mainswitcherwindow.h"
#include "ui_mainswitcherwindow.h"

#include <QLabel>
#include <QSpacerItem>

#include "designer.h"

#include <QDebug>

mainSwitcherWindow::mainSwitcherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainSwitcherWindow)
{
    ui->setupUi(this);

    // Настройка визуала
    Designer::setMainWindow(this);
    this->setWindowTitle("Система прогнозирования маршрутов скрытного пролета БПЛА");

    // Кнопки вызова основных окон
    toolBar = new QToolBar("Панель задач");
    toolBar->setMovable(false);  // Чтоб пользователь не потерял его :)
    Designer::setToolBar(toolBar, Designer::whiteToolBox);
    addToolBar(Qt::LeftToolBarArea, toolBar);

    //
    toolBar->setStyleSheet(
                "QToolBar {"
                "    border: 1px solid rgb(70,70,70);"
                "    background-color: rgb(75,75,80);"
                "}");

    //
    createMenus();

    //
    setStatusBar(nullptr);

    //
    this->setStyleSheet(
                "QMainWindow{"
                "    background-color: rgb(255,255,255);"
                "    border: 1px solid rgb(140,140,140);}");

}

void mainSwitcherWindow::showMainWindow()
{
    setCurrentWindow(mainWindow);
}

void mainSwitcherWindow::addWindow(QWidget *window,
                                   const QIcon &iconButton,
                                   const QString &nameButton,
                                   bool isMain)
{
    ui->stackedWidget->addWidget(window);

    //
    QToolButton* button = new QToolButton;
    button->setIcon(iconButton);
    button->setToolTip(nameButton);
    button->setText(nameButton);

    //
    windows[button] = window;
    if (isMain) mainWindow = window;

    /*
    QWidget* backWidget = new QWidget;
    QVBoxLayout* verLayout = new QVBoxLayout(backWidget);
    QHBoxLayout* horLayout = new QHBoxLayout;

    horLayout->addSpacerItem(new QSpacerItem(10, 10));
    horLayout->addWidget(button);
    horLayout->addSpacerItem(new QSpacerItem(10, 10));

    verLayout->addLayout(horLayout);
    QLabel* text = new QLabel(nameButton);
    text->setAlignment(Qt::AlignHCenter);
    verLayout->addWidget(text);*/

    //
    connect(button, SIGNAL(clicked(bool)),
            this,   SLOT(showWindow()));

    //toolBar->addWidget(backWidget);
    toolBar->addWidget(button);
}

void mainSwitcherWindow::setCurrentWindow(QWidget *window) const
{
    ui->stackedWidget->setCurrentWidget(window);
}

void mainSwitcherWindow::showWindow()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());
    ui->stackedWidget->setCurrentWidget(windows[button]);
}

void mainSwitcherWindow::createMenus()
{
        /* Создаём меню Файл */
    QMenu* mnFile = new QMenu("Файл");

    //
    QAction* openFileAction = new QAction("Открыть...",mnFile);
    //connect(openFileAction, SIGNAL(triggered()), this, SLOT(showMessage()));
    mnFile->addAction(openFileAction);

    // Меню помощь
    QMenu* mnHelp = new QMenu("Справка");
    QAction* programInfoAction = new QAction("О программе",mnHelp);
    //connect(programInfoAction, SIGNAL(triggered()), this, SLOT(showMessage()));
    mnHelp->addAction(programInfoAction);

    // Добавляем пункты меню в menuBar, т.е. те, которые будут отображаться в гл. окне
    ui->menubar->addMenu(mnFile);
    ui->menubar->addMenu(mnHelp);
}

mainSwitcherWindow::~mainSwitcherWindow()
{
    delete ui;
}
