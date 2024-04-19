#include "mapareamainwindow.h"
#include "ui_mapareamainwindow.h"

mapAreaMainWindow::mapAreaMainWindow(QImage* mapImg, Map* map, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapAreaMainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(100, 100);
    this->setMaximumSize(10080, 25000);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    toolBar = new QToolBar("Панель инструментов");
    toolBar->setStyleSheet("QToolBar {"
                           "   border: 1px solid gray;"
                           "   padding: 2px 0px;"
                           "   border-radius: 2px;"
                           "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                           "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                           "};");
    addToolBar(Qt::TopToolBarArea, toolBar); // добавляем в панель инструментов

    area = new areaDrawWidget(mapImg, map);
    ui->drawAreaLayout->addWidget(area);

    //
    scrollArea = ui->scrollArea;
    scrollArea->setMinimumSize(100, 100);
    scrollArea->setMaximumSize(10080, 25000);
    scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Игнорируем колесико (оставим его для инструментов)
    scrollArea->viewport()->installEventFilter(this);

    //
    connect(area, SIGNAL(updateCoord(QString)),
            this, SLOT(updateCoord(QString)));

    // Обычный курсор без дейсвий
    appendTool(new toolDefault(def));

    // Перетаскивание карты без лишнего
    ToolMoveMap* toolMoveMap = new ToolMoveMap(moveImg);
    connect(toolMoveMap, SIGNAL(movedMap(double,double)),
            this,        SLOT(movePosLookMap(double,double)));
    appendTool(toolMoveMap);

    // Изменение масштаба через мышь
    appendTool(new ToolZoomMap(zoomImg));


    //
    keyCurTool = def;
    Tool = Tools[def];
    lastToolButton = nullptr;
    area->setTool(Tool);

    // Настройка визуала
    this->setStyleSheet("QMainWindow{"
                        "   background-color: rgb(244,248,253);"
                        "   border: 1px solid gray;"
                        "   border-radius: 3px;"
                        "};");

    //
    statusBar = new QStatusBar;

    coordLabel = new QLabel("       ");
    coordLabel->setStyleSheet("QLabel{"
                              "   background-color: rgb(255,255,255,140);"
                              "   border: 1px solid gray;"
                              "   border-radius: 2px;"
                              "};)");
    statusBar->setFixedHeight(25);
    statusBar->addWidget(coordLabel);

    this->setStatusBar(statusBar);
    statusBar->show();
}

areaDrawWidget* mapAreaMainWindow::getDrawArea()
{
    return area;
}

bool mapAreaMainWindow::eventFilter(QObject* /*obj*/, QEvent *evt)
{
    if (evt->type() == QEvent::Wheel)
    {
        evt->ignore();
        return true;
    }

    return false;
}

void mapAreaMainWindow::wheelEvent(QWheelEvent *event)
{
    // Если нажата клавиша CTRL
    if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (event->delta() > 0)
        {
            area->zoom(0.08);
        }
        else
        {
            area->zoom(-0.08);
        }
    }
}

void mapAreaMainWindow::updateCoord(const QString &coordsData)
{
    coordLabel->setText(coordsData);
}

void mapAreaMainWindow::movePosLookMap(double dX, double dY)
{
    int curY = scrollArea->verticalScrollBar()->value();
    scrollArea->verticalScrollBar()->setValue(curY + (dY * area->height()));

    int curX = scrollArea->horizontalScrollBar()->value();
    scrollArea->horizontalScrollBar()->setValue(curX + (dX * area->width()));
}

void mapAreaMainWindow::appendTool(drawAreaTool *tool)
{
    // Назначаем область, где будет рисовать
    tool->setDrawArea(area);

    //
    int idPriority = tool->getId();
    Tools[idPriority] = tool;

    //
    if (idPriority != def)
    {
        //
        QToolButton* button = new QToolButton;
        connect(button, SIGNAL(clicked(bool)),
                this,   SLOT(changeTool()));
        //
        button->setIcon(tool->getImgButton());
        setButtonStyle(button, off);
        button->setToolTip(tool->getNameTool());

        toolBar->addWidget(button);

        // Для реакции инструмента
        objToKeyTool[button] = idPriority;
    }
}

void mapAreaMainWindow::appendToolGroup(const QVector<drawAreaTool *> &boxTools, const QString &nameGroup)
{
    //
    QToolButton* buttonGroup = new QToolButton;
    buttonGroup->setPopupMode(QToolButton::InstantPopup);
    buttonGroup->setToolTip(nameGroup);
    setButtonStyle(buttonGroup, off);

    //
    QMenu* toolMenu = new QMenu;
    buttonGroup->setMenu(toolMenu);
    Designer::setMenu(toolMenu);

    QAction* action;
    drawAreaTool* tool;
    for (int i=0; i<boxTools.size(); i++)
    {
        tool = boxTools.at(i);

        // Назначаем область, где будет рисовать
        tool->setDrawArea(area);

        //
        int idPriority = tool->getId();
        Tools[idPriority] = tool;

        //
        action = new QAction(tool->getImgButton(), tool->getNameTool(), buttonGroup);
        connect(action, SIGNAL(triggered(bool)),
                this,   SLOT(changeToolGroup()));
        toolMenu->addAction(action);

        // Для реакции инструмента
        objToKeyTool[action] = idPriority;
    }

    //
    toolBar->addWidget(buttonGroup);

    // Изначально ставим иконку последнего инструмента
    buttonGroup->setIcon(action->icon());
}

void mapAreaMainWindow::changeTool()
{
    setTool(objToKeyTool[sender()]);

    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    updateStyleToolButtons(toolButton);
}

void mapAreaMainWindow::changeToolGroup()
{
    setTool(objToKeyTool[sender()]);

    QAction* action = qobject_cast<QAction*>(sender());

    QToolButton* toolButton = qobject_cast<QToolButton*>(action->parentWidget());
    toolButton->setIcon(action->icon());

    updateStyleToolButtons(toolButton);
}

void mapAreaMainWindow::updateStyleToolButtons(QToolButton* changeButton)
{
    //
    if (lastToolButton != nullptr)
        setButtonStyle(lastToolButton, off);

    if (lastToolButton != changeButton)
    {
        lastToolButton = changeButton;
        setButtonStyle(lastToolButton, on);
    }
    else
    {
        setButtonStyle(lastToolButton, off);
    }
}

void mapAreaMainWindow::setTool(int key)
{
    //
    lastKeyTool = keyCurTool;

    // Освобождаем текущий от работы
    Tool->end();

    // Если хотим выбрать тот же инструменет, то отключаем его
    if (keyCurTool == key)
    {
        key = def;
        setButtonStyle(lastToolButton, off);
    }

    //
    Tool = Tools[key];
    keyCurTool = key;

    // Подготавливаем его к работ
    Tool->init();
    area->setTool(Tool);
}

int mapAreaMainWindow::curTool()
{
    return keyCurTool;
}

void mapAreaMainWindow::setButtonStyle(QToolButton *button, StyleButtonTool style)
{
    QString strStyle;
    switch (style) {
    case off:
        strStyle =
                "QToolButton{"
                "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                "    border-style: outset;"
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
                "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "    border-color: rgb(0,0,0);"
                "};";
        break;
    case on:
        strStyle =
                "QToolButton{"
                "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "}"
                "QToolButton:hover{"
                "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "    border-color: rgb(0,0,0);"
                "}"
                "QToolButton:pressed{"
                "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "    border-color: rgb(0,0,0);"
                "};";
        break;
    }

    button->setStyleSheet(strStyle);
}

void mapAreaMainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    /* ... */
}

mapAreaMainWindow::~mapAreaMainWindow()
{
    delete ui;
}
