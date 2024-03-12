#include "areadrawwidget.h"

#include <QImage>
#include <QDebug>

#include <cmath>
#include <QBrush>

#include <QGuiApplication>

#include <QPixmap>

areaDrawWidget::areaDrawWidget(QImage* mapImg)
{
    this->setMinimumSize(100, 100);
    this->setMaximumSize(10080, 25000);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // отправляем данные об координатах курсора
    isExportCoord = true;

    // инициализация контейнера для изображений
    images = QVector <QImage*> (3);

    images[geoMap] = mapImg;

    //
    strFormatImg = QVector <const char*> (3);
    strFormatImg[jpg] = "JPG";
    strFormatImg[png] = "PNG";
    strFormatImg[bmp] = "BMP";

    drawGeoMap();

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);

    k = 1;

    idXoPredict = 0;
    idYoPredict = 0;

    paintPredictRect = false;

    pixBeginDrone = new QPixmap(":/resurs/droneStart");
    pixFinishDrone = new QPixmap(":/resurs/droneFinish");

    pixRLS = new QPixmap(":/resurs/offRLS");
    pixCurRLS = new QPixmap(":/resurs/onRLS");
    curRLScolor.setRgb(0,255,255);

    isPredictTrail = false;

    isDrawRect3D = false;

    setRangeToolEditEarth(9);

    this->setCursor(Qt::ArrowCursor);

    toolBar = new QToolBar("Панель инструментов");
    toolBar->setStyleSheet("QToolBar {"
                           "   border: 2px solid gray;"
                           "   padding: 2px 0px;"
                           "   border-radius: 2px;"
                           "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                           "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                           "};");
    addToolBar(Qt::TopToolBarArea, toolBar); // добавляем в панель инструментов

    //
    Tools[def]          = new toolDefault(this, def);
    Tools[editEarth]    = new ToolEditMap(this, editEarth);
    Tools[moveImg]      = new ToolMoveMap(this, moveImg);
    Tools[predictRect]  = new ToolPredRect(this, predictRect);
    Tools[predictTrail] = new ToolPredTrail(this, predictTrail);
    Tools[setRLS]       = new ToolSetRLS(this, setRLS);
    Tools[mapVis]       = new ToolVisMap(this, mapVis);
    Tools[zoomImg]      = new ToolZoomMap(this, zoomImg);

    tool = def;
    Tool = Tools[def];


    //qDebug() << (toolRLS < toolVis);

    //
    drawTasks[background]    = &areaDrawWidget::drawBackground;
    drawTasks[terImg]        = &areaDrawWidget::drawMap;
    drawTasks[iconRLS]       = &areaDrawWidget::drawRLS;
    drawTasks[toolRLS]       = &areaDrawWidget::drawEleToolRLS;
    drawTasks[toolVis]       = &areaDrawWidget::drawEleToolVis;
    drawTasks[toolPredRect]  = &areaDrawWidget::drawEleToolPredRect;
    drawTasks[toolPredTrail] = &areaDrawWidget::drawEleToolPredTrail;

    appendDrawTask(background);
    appendDrawTask(terImg);
    appendDrawTask(iconRLS);

    p = &areaDrawWidget::drawBackground;

    // Настройка визуала
    this->setStyleSheet("QMainWindow{"
                        "   background-color: rgb(255,255,255);"
                        "   border: 2px solid gray;"
                        "};");
}

void areaDrawWidget::contextMenuEvent(QContextMenuEvent *event)
{
    /* ... */
}

QToolBar* areaDrawWidget::getToolBar()
{
    return toolBar;
}

void areaDrawWidget::appendDrawTask(drawTasksID task)
{   // Добавляем задачу только если её не было
    if (!curDrawTasks.contains(task))
    {
        curDrawTasks[task] = drawTasks[task];
    }
}

void areaDrawWidget::delDrawTask(drawTasksID task)
{
    curDrawTasks.remove(task);
}

void areaDrawWidget::drawBackground(QPainter &painter)
{
    //qDebug() << "drawBackground";

    // отрисовка подложки
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
    painter.drawRect(0, 0, this->geometry().width(), this->geometry().height());

}

void areaDrawWidget::drawMap(QPainter &painter)
{
    //qDebug() << "drawMap";

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
    painter.drawImage(Xo, Yo, drawImg->scaled(wightPixMap, heightPixMap));
}

void areaDrawWidget::drawEleToolRLS(QPainter &painter)
{
    if (isDrawPositionRLS)
    {
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
        painter.setBrush(QBrush(Qt::black));
        painter.drawEllipse(xPosRLS * k + Xo - 1, yPosRLS * k + Yo - 1, 4, 4);
    }
}

void areaDrawWidget::drawRLS(QPainter &painter)
{
    // Отрисовка станций (только на физ. карте)
    if (curOptRepaint == geoMap)
    {
        int rectX;
        int rectY;

        QColor colorText;
        for (int i=0; i<coordsRLS.size(); i++)
        {
            rectX = coordsRLS[i]->x() * k  + Xo;
            rectY = coordsRLS[i]->y() * k  + Yo;

            //
            if (i == idCurRLS)
            {
                painter.drawPixmap(rectX-16, rectY-18, pixCurRLS->scaled(36, 36));
                painter.setPen(curRLScolor);
            }

            else
            {
                 painter.drawPixmap(rectX-16, rectY-18, pixRLS->scaled(36, 36));
                 painter.setPen(Qt::black);
            }

            painter.drawText(QRect(rectX-16, rectY+15, 36, 20), namesRLS[i]);
        }
    }
}

void areaDrawWidget::drawEleToolVis(QPainter &painter)
{
    // отрисовка области 3D визуализации
    painter.setPen(QPen(QColor(0,0,213), 1, Qt::DashLine));

    painter.drawRect(QRect(QPoint(a3D.x()* k + Xo, a3D.y()* k + Yo),
                           QPoint(b3D.x()* k + Xo, b3D.y()* k + Yo)));
}

void areaDrawWidget::drawEleToolPredRect(QPainter &painter)
{
    // отрисовка эелементов поставленного БПЛА

    // отрисовка квадрата прогноза (текущего)
    painter.setPen(QColor(255,0,128));
    painter.drawRect(idXoPredict * k + Xo + 1, idYoPredict * k + Yo + 1, 200*k - 1, 200*k - 1);

    // индексы дискрет центра квадрата прогноза
    idXRect = idXoPredict + 100;
    idYRect = idYoPredict + 100;

    // отрисовка БПЛА
    int x = idXRect*k + Xo;
    int y = idYRect*k + Yo;

    painter.drawLine(x-3, y,
                     x+3, y);
    painter.drawLine(x, y-3,
                     x, y+3);

    // отрисовка квадрата прогноза (возможного)
    int xMouse, yMouse;
    Tool->getCoordMouse(xMouse, yMouse);
    painter.setPen(QColor(143, 32, 255));
    //if (drawRectInit)
        painter.drawRect(xMouse - (100 * k) + 1, yMouse - (100 * k) + 1, 200*k - 1, 200*k - 1);


    // отрисовать прогноз в квадрате
    if (paintPredictRect)
    {
        painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
        painter.drawLine(idXRect * k  + Xo, idYRect  * k + Yo,
                         idPRectX * k + Xo, idPRectY * k + Yo);
    }
}

void areaDrawWidget::drawEleToolPredTrail(QPainter &painter)
{
    // отрисовка траектории прогноза
    for (int i=0; i<trail.size() - 1; i++)
    {
        painter.setPen(QPen(QColor(255,0,128), 1));
        painter.drawEllipse(QPoint(trail[i]->x() * k  + Xo, trail[i]->y() * k  + Yo), 2, 2);
        painter.drawLine(trail[i]->x() * k  + Xo, trail[i]->y() * k  + Yo,
                         trail[i+1]->x() * k  + Xo, trail[i+1]->y() * k  + Yo);
    }
    if (trail.size() > 0) // отрисовываем последнию точку
        painter.drawEllipse(QPoint(trail.last()->x() * k  + Xo, trail.last()->y() * k  + Yo), 2, 2);

    // отрисовывать начальную и конечные точкитраектории
    painter.setPen(QPen(QColor(51,255,240), 1));

    int bX = beginPoint.x() * k  + Xo;
    int bY = beginPoint.y() * k  + Yo;

    int fX = lastPoint.x() * k  + Xo;
    int fY = lastPoint.y() * k  + Yo;

    if (curOptRepaint == geoMap)
    {
        painter.drawPixmap(bX-16, bY-32, pixBeginDrone->scaled(32,32));
        painter.drawPixmap(fX-16, fY-34, pixFinishDrone->scaled(32,32));
    }

    painter.drawEllipse(QPoint(fX, fY), 2, 2);
    painter.drawEllipse(QPoint(bX, bY), 2, 2);

    //
    painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
    painter.drawLine(bX, bY, fX, fY);
}

void areaDrawWidget::setMarkCoordRLS(int xMark, int yMark)
{
    xPosRLS = xMark;
    yPosRLS = yMark;

    // Отправляем координаты потонциальной РЛС
    setCoordRLS(xPosRLS, yPosRLS);

    //
    if (isDrawPositionRLS) repaint();
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

    qDebug() << "add RLS";
}

void areaDrawWidget::delRLS(int indexRLS)
{
    coordsRLS.removeAt(indexRLS);
    namesRLS.removeAt(indexRLS);

    repaint();
    qDebug() << "delete RLS";
}

void areaDrawWidget::clearTrail()
{
    for (int i=0; i<trail.size(); i++)
    {
        delete trail[i];
    }
    trail.clear();
}

void areaDrawWidget::setCurRLS(int idRLS)
{
    idCurRLS = idRLS;
    repaint();
}

void areaDrawWidget::drawResultPredictRect(int idXres, int idYres)
{
    idPRectX = idXres;
    idPRectY = idYres;

    paintPredictRect = true;

    repaint();
}

void areaDrawWidget::saveImage(const QString &dirName, formatImg fImg, typeSaveImg tSave)
{
    // выбираем изображение которое будем сохранять
    QImage saveImg;
    switch (curOptRepaint) {
    case geoMap:
        saveImg = *images[geoMap];
        break;
    case netData:
        saveImg = *images[netData];
        break;
    case QFunction:
        saveImg = *images[QFunction];
        break;
    }

    // сохраняем
    switch (tSave) {
    case full:
        saveImg.save(dirName,
                      strFormatImg[fImg],
                      100);
        break;
    case screen:
        this->getScreen().toImage().save(dirName,
                                         strFormatImg[fImg],
                                         100);
        break;
    case rect:
        size_t offset = idXoPredict * saveImg.depth() / 8
                      + idYoPredict * saveImg.bytesPerLine();

        QImage(saveImg.bits() + offset, 200, 200,
               saveImg.bytesPerLine(), saveImg.format()).save(dirName,
                                                                strFormatImg[fImg],
                                                                100);
        break;
    }
}

QPixmap areaDrawWidget::getScreen()
{
    QPixmap pix(this->size());
    this->render(&pix);

    return pix;
}

void areaDrawWidget::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter;
    painter.begin(this);

    // Прозрачная закраска
    QBrush voidBrush;

    // Выполнение задач отрисовки
    for (auto it = curDrawTasks.begin(); it != curDrawTasks.end(); ++it) {
        (this->*it.value())(painter);

        // чтобы цвет закраски был просзрачным
        painter.setBrush(voidBrush);
    }

    // отрисовка черной рамки окна визуализации
//    painter.setPen(Qt::black);
//    painter.drawRect(0, 0, this->geometry().width() - 1, this->geometry().height() - 1);

    painter.end();
}

void areaDrawWidget::addPointTrail(int idXpt, int idYpt)
{
    trail.append(new QPoint(idXpt, idYpt));
}

void areaDrawWidget::setTool(int key)
{
    tool = key;

    // Изменяем текущий инструмент
    Tool->end();  // освобождаем текущий от работы
    Tool = Tools[key];
    Tool->init(); // подготавливаем его к работе

    repaint();
}

int areaDrawWidget::curTool()
{
    return tool;
}

void areaDrawWidget::setCoordDrawArea(int Xo_, int Yo_)
{
    Xo = Xo_;
    Yo = Yo_;
}

void areaDrawWidget::setPredictRect(int idXo, int idYo)
{
    idXoPredict = idXo;
    idYoPredict = idYo;
}

void areaDrawWidget::setRangeToolEditEarth(int R)
{
    toolEarthR = R;

    int r = toolEarthR*k;
    if (r < 13) r = 13;

    this->setCursor(QCursor(QPixmap(":/resurs/toolEarthMove").scaled(r,r)));
}

bool areaDrawWidget::mouseFromArea(QMouseEvent *mouseEvent)
{
    int xPressMouse = mouseEvent->x();
    int yPressMouse = mouseEvent->y();

    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    // Условия
    return dX < wightPixMap &&
           dY < heightPixMap &&
           dX > 0 &&
           dY > 0;
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

void areaDrawWidget::setRectVis(int idXa, int idYa, int idXb, int idYb)
{
    a3D.setX(idXa);
    a3D.setY(idYa);

    b3D.setX(idXb);
    b3D.setY(idYb);
}

void areaDrawWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    Tool->mouseRelease(mouseEvent);

    /*
    pXo = Xo;
    pYo = Yo;

    int r; // размер курсора инструмента редактора рельефа
    switch (tool) {
    case editEarth:
        r = toolEarthR*k;
        if (r < 13) r = 13;
        this->setCursor(QCursor(QPixmap(":/resurs/toolEarthMove").scaled(r,r)));
        break;

    case mapVis:
        int dX, dY;
        dX = mouseEvent->x() - Xo;
        dY = mouseEvent->y() - Yo;

        b3D.setX((double)dX / k);
        b3D.setY((double)dY / k);

        int idXo, idYo;
        if (a3D.x() > b3D.x()) idXo = b3D.x();
        else idXo = a3D.x();
        if (a3D.y() > b3D.y()) idYo = b3D.y();
        else idYo = a3D.y();

        angX3D = idXo;
        angY3D = idYo;

        numW = abs(a3D.x() - b3D.x());
        numL = abs(a3D.y() - b3D.y());

        if (numW < 2) numW = 2;
        if (numL < 2) numL = 2;

        updateRect3D(angX3D, angY3D,
                     numW, numL);

        break;

    case zoomImg:

        break;
    case setRLS:

        break;
    case moveImg:
        this->setCursor(moveOpenCursor);
        isExportCoord = true;

        break;
    }*/
}

void areaDrawWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseFromArea(mouseEvent))
    {
        Tool->mouseMove(mouseEvent);

        int idX, idY;
        Tool->getCoordMouse(idX, idY);

        // Обновляем координаты курсора
        updateCoord(double (idX - Xo) / k,
                    double (idY - Yo) / k);
    }
}

void areaDrawWidget::zoom(double dK)
{
    k += dK;

    if (k <= 0) k = 0.1;
}

void areaDrawWidget::setBeginPointTrail(int idX, int idY)
{
    beginPoint.setX(idX);
    beginPoint.setY(idY);
}

void areaDrawWidget::setLastPointTrail(int idX, int idY)
{
    lastPoint.setX(idX);
    lastPoint.setY(idY);
}

void areaDrawWidget::sendPointsTrail()
{
    setPointsTrail(beginPoint, lastPoint);
}

void areaDrawWidget::startPredictTrail()
{
    // очищаем траекторию с предыдущего прогноза
    clearTrail();

    isPredictTrail = true;

    // не рисуем прогноз в области
    paintPredictRect = false;
}

void areaDrawWidget::finishPredictTrail()
{
    isPredictTrail = false;

}

void areaDrawWidget::drawGeoMap()
{
    isDrawPositionRLS = true;

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
