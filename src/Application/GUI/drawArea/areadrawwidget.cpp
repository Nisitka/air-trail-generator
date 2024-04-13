#include "areadrawwidget.h"

#include <QImage>
#include <QDebug>

#include <cmath>
#include <QBrush>

#include <QComboBox>
#include <QFontComboBox>
#include <QMenu>

#include <QGuiApplication>

#include <QPixmap>

#include "../designer.h"

areaDrawWidget::areaDrawWidget(QImage* mapImg, Map* map): map(map)
{
    this->setMinimumSize(100, 100);
    this->setMaximumSize(10080, 25000);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // отправляем данные об координатах курсора
    isExportCoord = true;

    // инициализация контейнера для изображений
    images = QVector <QImage*> (3);

    images[geoMap] = mapImg;

    drawGeoMap();

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);

    k = 1.0;

    pixRLS = new QPixmap(":/resurs/offRLS");
    pixCurRLS = new QPixmap(":/resurs/onRLS");
    curRLScolor.setRgb(0,255,255);

    this->setCursor(Qt::ArrowCursor);

    toolBar = new QToolBar("Панель инструментов");
    toolBar->setStyleSheet("QToolBar {"
                           "   border: 1px solid gray;"
                           "   padding: 2px 0px;"
                           "   border-radius: 2px;"
                           "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                           "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                           "};");
    addToolBar(Qt::TopToolBarArea, toolBar); // добавляем в панель инструментов

    //
    appendTool(new toolDefault(this, def));
    appendTool(new ToolMoveMap(this, moveImg));
    appendTool(new ToolZoomMap(this, zoomImg));

    keyCurTool = def;
    Tool = Tools[def];
    lastToolButton = nullptr;

    // Задачи, которые всегда должны выполняться
    appendDrawTask(background, new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawBackground));
    appendDrawTask(terImg,     new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawMap));
    appendDrawTask(iconRLS,    new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawRLS));
    appendDrawTask(border,     new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawBorder));

    // Настройка визуала
    this->setStyleSheet("QMainWindow{"
                        "   background-color: rgb(255,255,255);"
                        "   border: 1px solid gray;"
                        "};");

    isCustomCursor = true;

    //
    QStatusBar* statusBar = new QStatusBar;

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

void areaDrawWidget::setBlockSize(int size)
{
    lBlock = size;
}

void areaDrawWidget::appendTool(drawAreaTool *toolArea)
{
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
        connect(button,   SIGNAL(clicked(bool)),
                toolArea, SLOT(assign()));

        toolBar->addWidget(button);

        setButtonStyle(button, off);
    }
}

void areaDrawWidget::appendToolGroup(const QVector<drawAreaTool *> &boxTools,
                                     const QString& nameGroup)
{
    QToolButton* inputButton = new QToolButton;
    QMenu* toolMenu = new QMenu(inputButton);
    Designer::setMenu(toolMenu);

    drawAreaTool* tool;
    int idPriority;
    int countTool = boxTools.size();
    for (int i=0; i<countTool; i++)
    {
        tool = boxTools.at(i);

        idPriority = tool->getId();
        Tools[idPriority] = tool;

        toolMenu->addAction(tool->getImgButton(), tool->getNameTool(),
                            tool, SLOT(assign()));
    }

    inputButton->setMenu(toolMenu);
    inputButton->setPopupMode(QToolButton::MenuButtonPopup);

    connect(inputButton, SIGNAL(clicked(bool)),
            inputButton, SLOT(showMenu()));
    connect(inputButton, SIGNAL(triggered(QAction*)),
            this,        SLOT(changeGroupTools(QAction*)));

    setButtonStyle(inputButton, off);
    inputButton->setToolTip(nameGroup);
    inputButton->setIcon(tool->getImgButton());

    toolBar->addWidget(inputButton);
}

void areaDrawWidget::changeGroupTools(QAction* action)
{
    if (lastToolButton != nullptr)
        setButtonStyle(lastToolButton, off);

    QToolButton* bMenu = qobject_cast<QToolButton*>(sender());
    lastToolButton = bMenu;

    lastToolButton->setIcon(action->icon());
    setButtonStyle(lastToolButton, on);
}

void areaDrawWidget::changeTool()
{
    if (lastToolButton != nullptr)
        setButtonStyle(lastToolButton, off);

    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    lastToolButton = toolButton;
    setButtonStyle(lastToolButton, on);
}

void areaDrawWidget::setButtonStyle(QToolButton *button, StyleButtonTool style)
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

void areaDrawWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    /* ... */
}

void areaDrawWidget::appendDrawTask(int priorityKey, taskPainter* task)
{
    // Добавляем задачу только если её не было
    if (!drawTasks.contains(priorityKey))
    {
        drawTasks[priorityKey] = task;
    }
}

void areaDrawWidget::delDrawTask(int priorityKey)
{
    drawTasks.remove(priorityKey);
}

void areaDrawWidget::drawBackground()
{
    // Отрисовка подложки
    pPainter->setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
    pPainter->drawRect(0, 0, this->geometry().width(), this->geometry().height());
}

void areaDrawWidget::drawBorder()
{
    pPainter->setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    pPainter->setBrush(Qt::NoBrush);
    pPainter->drawRect(0, 0, this->geometry().width()-1, this->geometry().height()-1);
}

void areaDrawWidget::drawMap()
{
    // Какое изображение отрисовать
    switch (curOptRepaint)
    {
        case geoMap:
            drawImg = images[geoMap];
            break;

        case netData:
            drawImg = images[netData];
            break;

        case QFunction:
            drawImg = images[QFunction];
            break;
    }
    wightPixMap = drawImg->width() * k;
    heightPixMap = drawImg->height() * k;
    pPainter->drawImage(Xo, Yo, drawImg->scaled(wightPixMap, heightPixMap));
}

void areaDrawWidget::drawRLS()
{
    // Отрисовка станций (только на физ. карте)
    if (curOptRepaint == geoMap)
    {
        int rectX;
        int rectY;

        for (int i=0; i<coordsRLS.size(); i++)
        {
            rectX = coordsRLS[i]->x() * k  + Xo;
            rectY = coordsRLS[i]->y() * k  + Yo;

            //
            if (i == idCurRLS)
            {
                pPainter->drawPixmap(rectX-16, rectY-18, pixCurRLS->scaled(36, 36));
                pPainter->setPen(curRLScolor);
            }

            else
            {
                 pPainter->drawPixmap(rectX-16, rectY-18, pixRLS->scaled(36, 36));
                 pPainter->setPen(Qt::black);
            }

            pPainter->drawText(QRect(rectX-16, rectY+15, 36, 20), namesRLS[i]);
        }
    }
}

void areaDrawWidget::getCoordDrawArea(int &Xo_, int &Yo_)
{
    Xo_ = Xo;
    Yo_ = Yo;
}

void areaDrawWidget::getSizePixMap(int &W, int &H)
{
    W = wightPixMap;
    H = heightPixMap;
}

double areaDrawWidget::getValZoom()
{
    return k;
}

void areaDrawWidget::addRLS(QPoint *posRLS, const QString& nameNewRLS)
{
    coordsRLS.append(posRLS);
    namesRLS.append(nameNewRLS);
}

void areaDrawWidget::delRLS(int indexRLS)
{
    coordsRLS.removeAt(indexRLS);
    namesRLS.removeAt(indexRLS);

    repaint();
}

void areaDrawWidget::setCurRLS(int idRLS)
{
    idCurRLS = idRLS;
    repaint();
}

void areaDrawWidget::toIdMapCoords(int &Xpix, int &Ypix)
{
    Xpix = (Xpix - Xo) / k;
    Ypix = (Ypix - Yo) / k;
}

void areaDrawWidget::setPen(const QPen &pen)
{
    pPainter->setPen(pen);
}

void areaDrawWidget::setBrush(const QBrush &b)
{
    pPainter->setBrush(b);
}

void areaDrawWidget::drawPolygon(const QPolygon &polygon, unit uPoints)
{
    QPolygon p;

    switch (uPoints) {
    case idMap:
        for (int i=0; i<polygon.size(); i++)
        {
            p.append(polygon[i] * k + QPoint(Xo, Yo));
        }
        break;
    case pix:

        break;
    }

    pPainter->drawPolygon(p);
}

void areaDrawWidget::drawLine(int x1, int y1, int x2, int y2, unit uPoints)
{
    switch (uPoints) {
    case idMap:
        pPainter->drawLine(x1 * k + Xo, y1 * k + Yo,
                           x2 * k + Xo, y2 * k + Yo);
        break;
    case pix:
        pPainter->drawLine(x1, y1,
                           x2, y2);
        break;
    }
}

void areaDrawWidget::drawRect(int x1, int y1, int x2, int y2)
{
    pPainter->drawRect(QRect(QPoint(x1*k + Xo, y1*k + Yo),
                             QPoint(x2*k + Xo, y2*k + Yo)));
}

void areaDrawWidget::drawCircle(int x, int y, int R, unit uR, unit uCoords)
{
    switch (uR) {
    case idMap:
        R *= k;
        break;
    case pix:

        break;
    }

    switch (uCoords) {
    case idMap:
        x = x * k + Xo;
        y = y * k + Yo;
        break;
    case pix:

        break;
    }

    pPainter->drawEllipse(QPoint(x, y),
                          R, R);
}

void areaDrawWidget::drawText(const QRect& rect, const QString& text, unit uPoints)
{
    QBrush brush = pPainter->brush();

    pPainter->setBrush(QBrush(QColor(255,255,255, 180)));

    switch (uPoints) {
    case idMap:
        {
        int x = rect.x() * k + Xo;
        int y = rect.y() * k + Yo;

        QRect r(x, y, rect.width(), rect.height());

        pPainter->drawRect(r.x() - 3, r.y() - 3,
                           r.width() + 3, r.height() + 3);

        pPainter->drawText(r, text);
        break;
        }
    case pix:
        pPainter->drawRect(rect.x() - 3, rect.y() - 3,
                           rect.width() + 3, rect.height() + 3);

        pPainter->drawText(rect, text);
        break;
    }

    pPainter->setBrush(brush);
}

void areaDrawWidget::drawPixmap(int x, int y, int dX, int dY, const QPixmap& pix)
{
    x *= k;
    y *= k;

    pPainter->drawPixmap(x + Xo + dX, y + Yo + dY, pix);
}

void areaDrawWidget::paintEvent(QPaintEvent *pEvent)
{
    Q_UNUSED(pEvent);

    QPainter painter(this);
    pPainter = &painter;
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);

    // Выполнение задач отрисовки
    for (auto it = drawTasks.begin(); it != drawTasks.end(); ++it) {

        // Очередная задача по отрисовке
        it.value()->processing();

        // чтобы цвет закраски был просзрачным
        painter.setBrush(Qt::NoBrush);
    }

    painter.end();
}

void areaDrawWidget::setRenderHint(bool smoothing)
{
    pPainter->setRenderHint(QPainter::Antialiasing, smoothing);
}

// Изменяем текущий инструмент
void areaDrawWidget::setTool(int key)
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

    // Подготавливаем его к работе
    Tool->init();

    repaint();
}

int areaDrawWidget::curTool()
{
    return keyCurTool;
}

void areaDrawWidget::setCoordDrawArea(int Xo_, int Yo_)
{
    Xo = Xo_;
    Yo = Yo_;
}

bool areaDrawWidget::mouseFromArea(QMouseEvent *mouseEvent)
{
    bool inArea;

    int xPressMouse = mouseEvent->x();
    int yPressMouse = mouseEvent->y();

    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    // Условия
    inArea = dX < wightPixMap &&
             dY < heightPixMap &&
             dX > 0 &&
             dY > 0;

    if (inArea)
    {   //
        if (isCustomCursor)
            Tool->setCursor();
    }
    else
    {
         this->setCursor(Qt::CustomCursor);
    }

    return inArea;
}

void areaDrawWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseFromArea(mouseEvent)){

        Tool->mousePress(mouseEvent);
    }
}

void areaDrawWidget::wheelEvent(QWheelEvent *event)
{
    Tool->wheelEvent(event);
}

void areaDrawWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    Tool->mouseRelease(mouseEvent);
}

void areaDrawWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseFromArea(mouseEvent))
    {
        Tool->mouseMove(mouseEvent);
    }
}

void areaDrawWidget::updateInfoCoordMap(int idX, int idY)
{
    coordLabel->setText( "X:" + QString::number(double (idX - Xo) / k * lBlock) + "м"
                        " Y:" + QString::number(double (idY - Yo) / k * lBlock) + "м"
                        " H:" + QString::number(map->getHeight(idX - Xo, idY - Yo, Map::m)) + "м");
}

int areaDrawWidget::getBlockSize() const
{
    return lBlock;
}

void areaDrawWidget::zoom(double dK)
{
    k += dK;

    if (k <= 0) k = 0.1;
}

void areaDrawWidget::drawGeoMap()
{
    curOptRepaint = geoMap;
    repaint();
}

void areaDrawWidget::drawDataNet()
{
    curOptRepaint = netData;
    repaint();
}

void areaDrawWidget::drawQFunction()
{
    curOptRepaint = QFunction;
    repaint();
}
