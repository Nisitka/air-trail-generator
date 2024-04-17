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

    //
    connect(area, SIGNAL(updateCoord(QString)),
            this, SLOT(updateCoord(QString)));

    //
    appendTool(new toolDefault(area, def));
    ToolMoveMap* toolMoveMap = new ToolMoveMap(area, moveImg);
    connect(toolMoveMap, SIGNAL(movedMap(double,double)),
            this,        SLOT(movePosLookMap(double,double)));
    appendTool(toolMoveMap);

    appendTool(new ToolZoomMap(area, zoomImg));
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

void mapMainWindow::appendTool(drawAreaTool *toolArea)
{   //
    int idPriority = toolArea->getId();

    Tools[idPriority] = toolArea;

    //
    if (idPriority != def)
    {
        QToolButton* button = new QToolButton;
        button->setIcon(toolArea->getImgButton());
        button->setToolTip(toolArea->getNameTool());

        // Для изменения визуала
        connect(button, SIGNAL(clicked(bool)),
                this,   SLOT(changeTool()));

        // Для реакции инструмента
        buttonToKey[button] = idPriority;

        toolBar->addWidget(button);

        setButtonStyle(button, off);
    }
}

void mapMainWindow::appendToolGroup(const QVector<drawAreaTool *> &boxTools, const QString &nameGroup)
{
    /* ... */
}

void mapMainWindow::changeTool()
{
    if (lastToolButton != nullptr)
        setButtonStyle(lastToolButton, off);

    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());

    lastToolButton = toolButton;
    setButtonStyle(lastToolButton, on);

    setTool(buttonToKey[toolButton]);
}

void mapMainWindow::setTool(int key)
{
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
