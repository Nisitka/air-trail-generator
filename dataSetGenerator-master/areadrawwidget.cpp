#include "areadrawwidget.h"

#include <QImage>
#include <QDebug>

#include <cmath>
#include <QBrush>

#include <QGuiApplication>

#include <QPixmap>

areaDrawWidget::areaDrawWidget(QImage* mapImg,
                               QImage* netDataImg,
                               QImage* QFunImg)
{
    this->setFixedSize(width, length);

    // инициализация контейнера для изображений
    images = QVector <QImage*> (3);

    images[geoMap] = mapImg;
    images[netData] = netDataImg;
    images[QFunction] = QFunImg;

    //
    strFormatImg = QVector <const char*> (3);
    strFormatImg[jpg] = "JPG";
    strFormatImg[png] = "PNG";
    strFormatImg[bmp] = "BMP";

    drawGeoMap();

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);

    // иконка для курсора во время приблтижения
    iconZoom = QPixmap(":/resurs/zoom2");
    iconZoom = iconZoom.scaled(25, 25);
    zoomCursor = QCursor(iconZoom);
    k = 1;

    drawRectPredict = false;
    drawRectInit = false;

    idXoPredict = 0;
    idYoPredict = 0;

    paintPredictRect = false;

    pixBeginDrone = new QPixmap(":/resurs/droneStart");
    pixFinishDrone = new QPixmap(":/resurs/droneFinish");

    isPredictTrail = false;
}

void areaDrawWidget::clearTrail()
{
    for (int i=0; i<trail.size(); i++)
    {
        delete trail[i];
    }
    trail.clear();
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

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0, 0, width, length);

    // какое изображение отрисовать
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

    // чтобы цвет закраски был просзрачным
    QBrush b;
    painter.setBrush(b);

    // отрисовка эелементов поставленного БПЛА
    if (drawRectPredict)
    {
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
    }

    // отрисовка квадрата прогноза (возможного)
    if (tool == predictRect)
    {
        painter.setPen(QColor(143, 32, 255));
        if (drawRectInit)
            painter.drawRect(xMouse - (100 * k) + 1, yMouse - (100 * k) + 1, 200*k - 1, 200*k - 1);

    }

    // отрисовать прогноз в квадрате
    if (paintPredictRect)
    {
        painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
        painter.drawLine(idXRect * k  + Xo, idYRect  * k + Yo,
                         idPRectX * k + Xo, idPRectY * k + Yo);
    }

    // отрисовка траектории прогноза
    for (int i=0; i<trail.size() - 1; i++)
    {
        painter.setPen(QPen(QColor(255,0,128), 1));
        painter.drawEllipse(QPoint(trail[i]->x() * k  + Xo, trail[i]->y() * k  + Yo), 2, 2);
        painter.drawLine(trail[i]->x() * k  + Xo, trail[i]->y() * k  + Yo,
                         trail[i+1]->x() * k  + Xo, trail[i+1]->y() * k  + Yo);
    }

    // если !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (true)
    {
        painter.setPen(QPen(QColor(51,255,240), 1));

        int bX = beginPoint.x() * k  + Xo;
        int bY = beginPoint.y() * k  + Yo;

        int fX = lastPoint.x() * k  + Xo;
        int fY = lastPoint.y() * k  + Yo;

        if (curOptRepaint == geoMap)
        {
            painter.drawImage(bX-16, bY-32, pixBeginDrone->scaled(32,32).toImage());
            painter.drawImage(fX-16, fY-34, pixFinishDrone->scaled(32,32).toImage());
        }

        painter.drawEllipse(QPoint(fX, fY), 2, 2);
        painter.drawEllipse(QPoint(bX, bY), 2, 2);


        if (isPredictTrail)
        {
            painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
            painter.drawLine(bX, bY, fX, fY);
        }
    }

    // отрисовка черной рамки окна визуализации
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width - 1, length - 1);

    if (isDrawPositionRLS)
    {
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
        painter.setBrush(QBrush(Qt::black));
        painter.drawEllipse(xPosRLS * k + Xo - 1, yPosRLS * k + Yo - 1, 4, 4);
    }

    painter.end();
}

void areaDrawWidget::addPointTrail(int idXpt, int idYpt)
{
    drawRectPredict = true;
    trail.append(new QPoint(idXpt, idYpt));
}

void areaDrawWidget::setTool(tools tool_)
{
    statMouse = release;

    tool = tool_;
    if (tool == predictRect) drawRectPredict = true;

    repaint();
}

void areaDrawWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    xMouse = mouseEvent->x();
    yMouse = mouseEvent->y();

    int dX, dY;
    dX = xMouse - Xo;
    dY = yMouse - Yo;
    if (dX < wightPixMap && dY < heightPixMap &&
        dX > 0 && dY > 0)
    {
        idX = (double)dX / k;
        idY = (double)dY / k;
        updateCoord(idX, idY);
    }
    switch (tool) {
    case zoomImg:
        this->setCursor(zoomCursor);
        break;

    case setRLS:
        this->setCursor(rlsCursor);
        break;

    case predictTrail:
        this->setCursor(predictNetCursor);

    case predictRect:
        this->setCursor(predictNetCursor);
        if (dX < wightPixMap && dY < heightPixMap &&
            dX > 0 && dY > 0)
        {
            drawRectInit = true;
        }
        else
        {
            drawRectInit = false;
        }
        repaint();

        break;

    case moveImg:
        if (statMouse == press)
        {
            this->setCursor(moveCloseCursor);
            matchTranslateMove();
            this->repaint();
        }
        else
        {
            this->setCursor(moveOpenCursor);
        }
        break;
    }
}

void areaDrawWidget::matchTranslateMove()
{
    Xo = pXo - (xPressMouse - xMouse);
    Yo = pYo - (yPressMouse - yMouse);
}

void areaDrawWidget::setPredictRect(int idXo, int idYo)
{
    idXoPredict = idXo;
    idYoPredict = idYo;
}

void areaDrawWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    statMouse = press;

    xPressMouse = mouseEvent->x();
    yPressMouse = mouseEvent->y();

    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;
    if (dX < wightPixMap && dY < heightPixMap &&
        dX > 0 && dY > 0){

        pXo = Xo;
        pYo = Yo;

        switch (tool) {
        case predictRect:
            idX = (double)dX / k;
            idY = (double)dY / k;

            drawRectPredict = true;
            predictMoveDroneRect(idX, idY);

            // больше не рисовать предыдущий прогноз
            paintPredictRect = false;

            repaint();
            break;

        case predictTrail:
            idX = (double)dX / k;
            idY = (double)dY / k;

            switch (mouseEvent->button() - 1) {
            case left:
                beginPoint.setX(idX);
                beginPoint.setY(idY);
                break;
            case right:
                lastPoint.setX(idX);
                lastPoint.setY(idY);
                break;
            }
            setPointsTrail(beginPoint, lastPoint);

            repaint();
            break;

        case zoomImg:
            Xo -= xPressMouse;
            Xo += (width / 2);

            Yo -= yPressMouse;
            Yo += (length / 2);

            switch (mouseEvent->button() - 1) {
            case left:
                Xo -= double ((double) drawImg->width() * dk) / 2;
                Yo -= double ((double) drawImg->height() * dk) / 2;

                k += dk;
                break;
            case right:
                Xo += double ((double) drawImg->width() * dk) / 2;
                Yo += double ((double) drawImg->height() * dk) / 2;

                k -= dk;
                break;
            }
            repaint();
            break;
        case setRLS:
            xPosRLS = (xPressMouse - Xo) / k;
            yPosRLS = (yPressMouse - Yo) / k;

            setCoordRLS(xPosRLS, yPosRLS);

            if (isDrawPositionRLS) repaint();
            break;
        case moveImg:
            this->setCursor(moveCloseCursor);
            break;
        }
    }
}

void areaDrawWidget::startPredictTrail()
{
    clearTrail();
    isPredictTrail = true;
}

void areaDrawWidget::finishPredictTrail()
{
    isPredictTrail = false;
}

void areaDrawWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    statMouse = release;

    pXo = Xo;
    pYo = Yo;

    switch (tool) {
    case zoomImg:

        break;
    case setRLS:

        break;
    case moveImg:
        this->setCursor(moveOpenCursor);

        break;
    }
}

void areaDrawWidget::updateSizeWidget(int w, int h)
{
    length = h;
    width = w;

    setFixedSize(width, length);
}

void areaDrawWidget::drawGeoMap()
{
    isDrawPositionRLS = true;

    curOptRepaint = geoMap;
    repaint();
}

void areaDrawWidget::drawDataNet()
{
    isDrawPositionRLS = false;

    curOptRepaint = netData;
    repaint();
}

void areaDrawWidget::drawQFunction()
{
    isDrawPositionRLS = false;

    curOptRepaint = QFunction;
    repaint();
}
