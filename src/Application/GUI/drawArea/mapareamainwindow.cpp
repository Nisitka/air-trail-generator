#include "mapareamainwindow.h"
#include "ui_mapareamainwindow.h"

#include "scrollmapwidget.h"

#include <QIcon>

mapAreaMainWindow::mapAreaMainWindow(GISInformer* gis, QWidget *parent) :
    gis(gis), QMainWindow(parent),
    ui(new Ui::mapAreaMainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(600, 400);
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

    area = new areaDrawWidget(gis);

    //
    scrollArea = new ScrollMapWidget(area);
    setCentralWidget(scrollArea);

    //
    connect(scrollArea, SIGNAL(moveActionArea(int,int)),
            this,       SIGNAL(moveActionArea(int,int)));

    // Игнорируем колесико (оставим его для инструментов)
    scrollArea->viewport()->installEventFilter(this);

    // Обычный курсор без дейсвий
    appendTool(new toolDefault(def));

    // Перетаскивание карты
    ToolMoveMap* toolMoveMap = new ToolMoveMap(moveImg);
    connect(toolMoveMap, SIGNAL(movedLookArea(double,double)),
            scrollArea,  SLOT(movePosLookMap(double,double)));
    connect(toolMoveMap, SIGNAL(mouseReleaseSignal()),
            scrollArea,  SLOT(checkShowNewActionArea()));
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
    infoLabel = new QLabel;
    statusBar = new QStatusBar;
    statusBar->setFixedHeight(25);
    statusBar->addWidget(infoLabel);
    //
    this->setStatusBar(statusBar);
    statusBar->setStyleSheet("QStatusBar{"
                             "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                             "                                     stop: 0    #E0E0E0,"
                             "                                     stop: 0.35 rgb(251,252,254), "
                             "                                     stop: 1    rgb(231,232,234));"
                             "   border: 1px solid gray;"
                             "   padding: 1px 0px;"
                             "   border-radius: 2px;"
                             "};)");
    statusBar->show();
}

void mapAreaMainWindow::updateGeoMapImage()
{
    area->updateSize();
    repaintBackground();
}

void mapAreaMainWindow::setNewActionArea(int idXo, int idYo)
{
    area->initActionArea(idXo, idYo);
    scrollArea->setMoveMapEnabled();
}

void mapAreaMainWindow::repaintBackground()
{
    area->repaint();
}

void mapAreaMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Отрисовка подложки
    painter.setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
    painter.drawRect(0, 0, this->geometry().width(), this->geometry().height());

    painter.end();
}

void mapAreaMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
}

void mapAreaMainWindow::updateInfoStatusBar(const QString& info)
{
    infoLabel->setText(info);
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
        QAction* action = toolBar->addAction(QIcon(tool->getImgButton()), tool->getNameTool(),
                                             this,  SLOT(changeTool()));

        // Изначально выключен
        setButtonStyle(dynamic_cast<QToolButton*>(
                           toolBar->widgetForAction(action)), off);

        // Для реакции инструмента
        objToKeyTool[action] = idPriority;
    }

    //
    connect(tool, SIGNAL(info(QString)),
            this, SLOT(updateInfoStatusBar(QString)));
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

        //
        connect(tool, SIGNAL(info(QString)),
                this, SLOT(updateInfoStatusBar(QString)));
    }

    //
    toolBar->addWidget(buttonGroup);

    // Изначально ставим иконку последнего инструмента
    buttonGroup->setIcon(action->icon());
}

void mapAreaMainWindow::changeTool()
{
    setTool(objToKeyTool[sender()]);

    QAction* action = qobject_cast<QAction*>(sender());

    QToolButton* toolButton
        = dynamic_cast<QToolButton*>(toolBar->widgetForAction(action));

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
                "    background-color:transparent;"
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
