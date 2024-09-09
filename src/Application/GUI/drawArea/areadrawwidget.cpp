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
#include <QTextOption>

#include <QApplication>

#include "../designer.h"

areaDrawWidget::areaDrawWidget(GISInformer* gis):
    gis(gis), kZoom(1.0)
{
    isCustomCursor = true;

    // инициализация контейнера для изображений
    images = QVector <QImage*> (3);
    //images[geoMap] = mapImg;
    drawImg = gis->getGeoImage();
    updateSize();

    // отправляем данные об координатах курсора
    isExportCoord = true;

    //
    drawEnable = true;

    drawGeoMap();

    // Чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);

    this->setCursor(Qt::ArrowCursor);

    // Задачи, которые всегда должны выполняться
    appendDrawTask(background, new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawBackground));
    appendDrawTask(terImg,     new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawMap));
    //appendDrawTask(iconRLS,    new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawRLS));
    appendDrawTask(border,     new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawBorder));

    installEventFilter(this);

    angle = 0;
}

void areaDrawWidget::toPixDrawArea(int &Xid, int &Yid)
{
    Xid = (Xid - idXo) * kZoom;
    Yid = (Yid - idYo) * kZoom;
}

void areaDrawWidget::toIdMapCoords(int &Xpix, int &Ypix)
{
    Xpix = (Xpix / kZoom) + idXo;
    Ypix = (Ypix / kZoom) + idYo;
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
//    pPainter->setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
//    pPainter->drawRect(0, 0, this->geometry().width(), this->geometry().height());
}

void areaDrawWidget::drawBorder()
{
    pPainter->setPen(Qt::NoPen); //QPen(Qt::black, 1, Qt::SolidLine)
    pPainter->setBrush(Qt::NoBrush);
    pPainter->drawRect(0, 0, this->geometry().width()-1, this->geometry().height()-1);
}

void areaDrawWidget::drawMap()
{
    // Берем текущую подложку
    drawImg = gis->getGeoImage();

    //
    pPainter->drawImage(0, 0, drawImg.scaled(W, H));
}

void areaDrawWidget::setAngleRotate(qreal angle_)
{
    angle = angle_;
}

void areaDrawWidget::changeAngleRotate(qreal dAngle)
{
    angle += dAngle;
    repaint();

    qDebug() << angle;
}

void areaDrawWidget::rotate(qreal a)
{
    pPainter->rotate(a);
}

void areaDrawWidget::updateSize()
{
    //
    W = drawImg.width()  * kZoom;
    H = drawImg.height() * kZoom;

    setFixedSize(W, H);

    // Сообщаем об этом кому это нужно
    resized();
}

void areaDrawWidget::getSizePixMap(int &W, int &H)
{
    W = wightPixMap;
    H = heightPixMap;
}

double areaDrawWidget::getValZoom()
{
    return kZoom;
}

QPainter& areaDrawWidget::getPainter()
{
    return *pPainter;
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
            p.append((polygon[i] - QPoint(idXo, idYo)) * kZoom);
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
        toPixDrawArea(x1, y1);
        toPixDrawArea(x2, y2);
        break;
    case pix:

        break;
    }
    pPainter->drawLine(x1, y1,
                       x2, y2);
}

void areaDrawWidget::drawRect(int x1, int y1, int x2, int y2)
{
    toPixDrawArea(x1, y1);
    toPixDrawArea(x2, y2);

    pPainter->drawRect(QRect(QPoint(x1, y1),
                             QPoint(x2, y2)));
}

void areaDrawWidget::drawCircle(int x, int y, int R, unit uR, unit uCoords)
{
    switch (uR) {
    case idMap:
        R *= kZoom;
        break;
    case pix:

        break;
    }

    switch (uCoords) {
    case idMap:
        toPixDrawArea(x, y);
        break;
    case pix:

        break;
    }

    pPainter->drawEllipse(QPoint(x, y),
                          R, R);
}

void areaDrawWidget::drawText(const QRect& rect, const QString& text, unit uPoints,
                              int dXpix, int dYpix,
                              const QColor backColor, const QColor textColor)
{
    QBrush brush = pPainter->brush();
    QPen   pen   = pPainter->pen();

    pPainter->setBrush(QBrush(backColor));
    pPainter->setPen(textColor);

    int x, y;
    x = rect.x();
    y = rect.y();
    switch (uPoints) {
    case idMap:
        {
        toPixDrawArea(x, y);

        break;
        }
    case pix:

        break;
    }
    x += dXpix;
    y += dYpix;

    //
    QRect r(x, y, rect.width(), rect.height());
    pPainter->drawRect(r.x() - 3, r.y() - 3,
                       r.width() + 6, r.height() + 6);
    //
    pPainter->drawText(r, Qt::AlignHCenter, text);

    // Возвращаем painter-у искодное состояние
    pPainter->setPen(pen);
    pPainter->setBrush(brush);
}

void areaDrawWidget::drawPixmap(int x, int y, int dX, int dY, const QPixmap& pix)
{
    toPixDrawArea(x, y);

    pPainter->drawPixmap(x + dX, y + dY, pix);
}

void areaDrawWidget::setDrawEnabled(bool isDrawEvent)
{
    drawEnable = isDrawEvent;
}

bool areaDrawWidget::eventFilter(QObject *obj, QEvent *event)
{
    //qDebug() << obj->objectName() << event->type();

    return false;
}

void areaDrawWidget::paintEvent(QPaintEvent *pEvent)
{
    Q_UNUSED(pEvent);

//    qDebug() << "paintEvent: " <<
//                pEvent->registerEventType();

    if (drawEnable)
    {
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

        //qDebug() << "draw";
    }
}

void areaDrawWidget::setRenderHint(bool smoothing)
{
    pPainter->setRenderHint(QPainter::Antialiasing, smoothing);
}

void areaDrawWidget::initActionArea(int idXo_, int idYo_)
{
    idXo = idXo_;
    idYo = idYo_;
}

void areaDrawWidget::setTool(drawAreaTool *tool)
{
    Tool = tool;
    repaint();
}

void areaDrawWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    Tool->mousePress(mouseEvent);
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
    Tool->mouseMove(mouseEvent);
}

void areaDrawWidget::setCurrentPixPoint(int idX, int idY)
{
    toIdMapCoords(idX, idY);

    changedCurrentCoords(gis->getCoords(idX, idY));
}

void areaDrawWidget::zoom(double dK)
{
    kZoom += dK;

    if (kZoom < 0.2) kZoom = 0.2;

    updateSize();
}

void areaDrawWidget::setZoom(double k)
{
    kZoom = k;

    if (kZoom < 0.2) kZoom = 0.2;

    updateSize();
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
