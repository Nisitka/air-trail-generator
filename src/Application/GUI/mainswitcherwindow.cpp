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
    //Designer::setToolBar(toolBar, Designer::whiteToolBox);
    addToolBar(Qt::LeftToolBarArea, toolBar);

    //
    createMenus();
}

void mainSwitcherWindow::addWindow(QWidget *window,
                                   const QIcon &iconButton,
                                   const QString &nameButton)
{
    ui->stackedWidget->addWidget(window);

    //
    QToolButton* button = new QToolButton;
    button->setIcon(iconButton);
    button->setToolTip(nameButton);
    button->setText(nameButton);

    //
    windows[button] = window;

    QWidget* backWidget = new QWidget;
    QVBoxLayout* verLayout = new QVBoxLayout(backWidget);
    QHBoxLayout* horLayout = new QHBoxLayout;

    horLayout->addSpacerItem(new QSpacerItem(20, 20));
    horLayout->addWidget(button);
    horLayout->addSpacerItem(new QSpacerItem(20, 20));

    verLayout->addLayout(horLayout);
    QLabel* text = new QLabel(nameButton);
    text->setAlignment(Qt::AlignHCenter);
    verLayout->addWidget(text);

    //
    connect(button, SIGNAL(clicked(bool)),
            this,   SLOT(showWindow()));

    toolBar->addWidget(backWidget);
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
