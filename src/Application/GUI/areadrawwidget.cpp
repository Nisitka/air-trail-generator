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
    this->setMinimumSize(100, 100);
    this->setMaximumSize(2000, 1080);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // отправляем данные об координатах курсора
    isExportCoord = true;

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
    iconZoom = QPixmap(":/resurs/zoomTool");
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

    pixRLS = new QPixmap(":/resurs/offRLS");
    pixCurRLS = new QPixmap(":/resurs/onRLS");
    curRLScolor.setRgb(0,255,255);

    isPredictTrail = false;

    drawSFPointsTrail = false;

    setTool(def);

    isDrawRect3D = false;

    setRangeToolEditEarth(9);

    this->setCursor(Qt::ArrowCursor);
}

void areaDrawWidget::readyEditEarth()
{
    if (tool == editEarth)
    {
        if (statMouse == press)
        {
            switch (lastKeyMouse) {
            case left:
                upEarth(idX, idY, toolEarthR);
                break;
            case right:
                downEarth(idX, idY, toolEarthR);
                break;
            }
        }
        else
        {   // перемоделируем сигналы РЛС
            updateSignals();
        }
    }
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

    // отрисовка подложки
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
    painter.drawRect(0, 0, this->geometry().width(), this->geometry().height());

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

    // отрисовка области 3D визуализации
    if (isDrawRect3D)
    {
        painter.setPen(QPen(QColor(0,0,213), 1, Qt::DashLine));

        painter.drawRect(QRect(QPoint(a3D.x()* k + Xo, a3D.y()* k + Yo),
                               QPoint(b3D.x()* k + Xo, b3D.y()* k + Yo)));
    }

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
    if (trail.size() > 0) // отрисовываем последнию точку
        painter.drawEllipse(QPoint(trail.last()->x() * k  + Xo, trail.last()->y() * k  + Yo), 2, 2);

    // отрисовывать начальную и конечные точкитраектории
    if (drawSFPointsTrail)
    {
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


        if (isPredictTrail)
        {
            painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
            painter.drawLine(bX, bY, fX, fY);
        }
    }

    // отрисовка станций (только на физ. карте)
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

    // отрисовка черной рамки окна визуализации
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, this->geometry().width() - 1, this->geometry().height() - 1);

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
    isDrawRect3D = false;

    int r; // размер курсора кисти
    switch (tool) {
    case def:
        this->setCursor(Qt::ArrowCursor);
        break;

    case editEarth:
        r = toolEarthR*k;
        if (r < 13) r = 13;

        this->setCursor(QCursor(QPixmap(":/resurs/toolEarthMove").scaled(r,r)));
        break;

    case mapVis:
        isDrawRect3D = true;
        this->setCursor(rect3DCursor);
        break;

    case zoomImg:
        this->setCursor(zoomCursor);
        break;

    case setRLS:
        this->setCursor(rlsCursor);
        break;

    case predictTrail:
        drawRectPredict = true;
        this->setCursor(predictNetCursor);

    case predictRect:
        this->setCursor(predictNetCursor);
        break;

    case moveImg:

        break;
    }

    repaint();
}

int areaDrawWidget::curTool()
{
    return tool;
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

        if (isExportCoord) updateCoord(idX, idY);
    }

    // в зависимости от выбранного инструмента меняем курсор и т.д.
    switch (tool) {
    case def:

        break;

    case editEarth:

        break;

    case mapVis:
        if (statMouse == press)
        {
            b3D.setX(idX);
            b3D.setY(idY);
        }
        repaint();
        break;

    case zoomImg:

        break;

    case setRLS:

        break;

    case predictTrail:

        break;

    case predictRect:
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

void areaDrawWidget::setRangeToolEditEarth(int R)
{
    toolEarthR = R;

    int r = toolEarthR*k;
    if (r < 13) r = 13;

    this->setCursor(QCursor(QPixmap(":/resurs/toolEarthMove").scaled(r,r)));
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
        case editEarth:
            idX = (double)dX / k;
            idY = (double)dY / k;

            int r; // размер курсора инструмента
            switch (mouseEvent->button() - 1) {
            case left:
                lastKeyMouse = left;

                r = toolEarthR*k;
                if (r < 13) r = 13;
                this->setCursor(QCursor(QPixmap(":/resurs/toolEarthUp").scaled(r,r)));

                upEarth(idX, idY, toolEarthR);
                break;
            case right:
                lastKeyMouse = right;

                r = toolEarthR*k;
                if (r < 13) r = 13;
                this->setCursor(QCursor(QPixmap(":/resurs/toolEarthDown").scaled(r,r)));

                downEarth(idX, idY, toolEarthR);
                break;
            }
            break;

        case mapVis:
            idX = (double)dX / k;
            idY = (double)dY / k;

            a3D.setX(idX);
            a3D.setY(idY);

            b3D.setX(idX);
            b3D.setY(idY);

            repaint();
            break;

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
            drawSFPointsTrail = true;

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
            Xo += (this->geometry().width() / 2);

            Yo -= yPressMouse;
            Yo += (this->geometry().height() / 2);

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
            isExportCoord = false;
            break;
        }
    }
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

void areaDrawWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    statMouse = release;

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
    }
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
