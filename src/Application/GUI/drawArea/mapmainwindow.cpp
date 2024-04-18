#include "mapmainwindow.h"

#include <QScrollBar>

mapMainWindow::mapMainWindow(QImage* mapImg, Map* map)
{
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

    //
    scrollArea = new QScrollArea;
    scrollArea->setMinimumSize(100, 100);
    scrollArea->setMaximumSize(10080, 25000);
    scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    scrollArea->setWidget(area);
    setCentralWidget(scrollArea);

    // Игнорируем колесико (оставим его для инструментов)
    scrollArea->viewport()->installEventFilter(this);

    scrollArea->setStyleSheet("QScrollArea { "
                              " background: transparent; "
                              " background-image: url(:/resurs/pattern1);"
                              "}");

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
                        "   background-color: rgb(255,255,255);"
                        "   border: 1px solid gray;"
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

bool mapMainWindow::eventFilter(QObject* /*obj*/, QEvent *evt)
{
    if (evt->type() == QEvent::Wheel)
    {
        evt->ignore();
        return true;
    }

    return false;
}

void mapMainWindow::updateCoord(const QString &coordsData)
{
    coordLabel->setText(coordsData);
}

void mapMainWindow::movePosLookMap(double dX, double dY)
{
    int curY = scrollArea->verticalScrollBar()->value();
    scrollArea->verticalScrollBar()->setValue(curY + (dY * area->height()));

    int curX = scrollArea->horizontalScrollBar()->value();
    scrollArea->horizontalScrollBar()->setValue(curX + (dX * area->width()));
}

void mapMainWindow::appendTool(drawAreaTool *tool)
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

void mapMainWindow::appendToolGroup(const QVector<drawAreaTool *> &boxTools, const QString &nameGroup)
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

void mapMainWindow::changeTool()
{
    setTool(objToKeyTool[sender()]);

    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    updateStyleToolButtons(toolButton);
}

void mapMainWindow::changeToolGroup()
{
    setTool(objToKeyTool[sender()]);

    QAction* action = qobject_cast<QAction*>(sender());

    QToolButton* toolButton = qobject_cast<QToolButton*>(action->parentWidget());
    toolButton->setIcon(action->icon());

    updateStyleToolButtons(toolButton);
}

void mapMainWindow::updateStyleToolButtons(QToolButton* changeButton)
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

void mapMainWindow::setTool(int key)
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

int mapMainWindow::curTool()
{
    return keyCurTool;
}

void mapMainWindow::setButtonStyle(QToolButton *button, StyleButtonTool style)
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

void mapMainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    /* ... */
}

areaDrawWidget* mapMainWindow::getDrawArea()
{
    return area;
}
