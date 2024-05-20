#include "minimapwidget.h"

#include <QPainter>

#include <QDebug>

miniMapWidget::miniMapWidget(QWidget* parent, int maxW, int maxH, Alignment typePos):
    QLabel(parent), Parent(parent), // Виджет, на котором будет располагаться миникарта
    typePos(typePos)
{
    dAlign.setX(0);
    dAlign.setY(0);

    //
    this->setMouseTracking(true);

    statMouse = release;

    //
    inLookRect = false;

    //
    lookArea = new QRect(0, 0, 15, 10);

    setMaxSize(maxW, maxH);
    this->setStyleSheet("QWidget{"
                        "   background: rgb(128,128,128,25);"
                        "   border-radius: 5px;"
                        "   border: 1px solid rgb(0,0,0);"
                        "}");
}

void miniMapWidget::setPaternSizeLookArea(double pW, double pH)
{

//    qDebug() << pW * sizeActionArea.width();
//    qDebug() << pH * sizeActionArea.height();

    //
    setSizeLookArea(pW * sizeActionArea.width(),
                    pH * sizeActionArea.height());
}

void miniMapWidget::Show()
{
    this->show();
}

void miniMapWidget::Hide()
{
    this->hide();
}

void miniMapWidget::setDistEdge(int dXpx, int dYpx)
{
    dAlign.setX(dXpx);
    dAlign.setY(dYpx);
}

void miniMapWidget::updatePos()
{
    QPoint pos;

    switch (typePos) {
    case topRight:

        break;
    case topLeft:

        break;

    case bottomLeft:

        break;
    case bottomRight:
        pos.setX(Parent->width()  - this->width());
        pos.setY(Parent->height() - this->height());

        pos -= dAlign;
        break;
    }

    this->move(pos);

    //qDebug() << "miniMap: " << pos;
}

void miniMapWidget::setPosLookArea(int idX, int idY)
{
    bool lX = false;
    bool lY = false;

    if (idX < 0) {idX = 0; lX = true;}
    if (idY < 0) {idY = 0; lY = true;}

    if (idX + lookArea->width()  >= maxW) {idX = maxW - lookArea->width()  - 1;
                                           lX = true;}
    if (idY + lookArea->height() >= maxH) {idY = maxH - lookArea->height() - 1;
                                           lY = true;}

//    //
//    if (lX) QCursor::setPos(posCursor.x(), QCursor::pos().y());
//    if (lY) QCursor::setPos(QCursor::pos().x(), posCursor.y());


    lookArea->moveTo(idX, idY);

    repaint();
}

void miniMapWidget::setPosLookArea(double partX, double partY)
{
    int idX = sizeActionArea.width()  * partX;
    int idY = sizeActionArea.height() * partY;

    setPosLookArea(idX, idY);
}

void miniMapWidget::setSizeLookArea(int W, int H)
{
    lookArea->setSize(QSize(W, H));
}

void miniMapWidget::setMaxSize(int W, int H)
{
    maxW = W; maxH = H;
    kSize = (double) maxW/maxH;

    // Одоптируем размеры под текущую карту
    //setSizeActionArea(sizeActionArea);
}

void miniMapWidget::setSizeActionArea(const QSize& size)
{
    //
    double kW = (double)size.width()  / maxW;
    double kH = (double)size.height() / maxH;

    int W, H;

    if (kW > kH)
    {
        W = maxW;
        H = W / kSize;
    }
    else
    {
        H = maxH;
        W = H * kSize;
    }

    // Применяем вычесленные размеры
    sizeActionArea.setWidth(W);
    sizeActionArea.setHeight(H);
    this->setFixedSize(sizeActionArea);
}

void miniMapWidget::mousePressEvent(QMouseEvent *mouse)
{
    statMouse = press;

    posMouse = mouse->pos();
    pointPressWidget = posMouse;
    if (lookArea->contains(posMouse))
    {
        inLookRect = true;

        pointPressArea = posMouse - lookArea->topLeft();

        this->setCursor(Qt::SizeAllCursor);
    }
}

void miniMapWidget::mouseMoveEvent(QMouseEvent *mouse)
{
    posMouse = mouse->pos();
    if (lookArea->contains(posMouse))
    {
        if (statMouse == press)
        {
            QPoint p = posMouse - pointPressArea;
            setPosLookArea(p.x(), p.y());

            //
            double dX = (double) lookArea->topLeft().x() / sizeActionArea.width();
            double dY = (double) lookArea->topLeft().y() / sizeActionArea.height();

            //qDebug() << dX << dY;

            movedLookArea(dX, dY);
        }
        else
        {
            if (!inLookRect)
            {
                inLookRect = true;

                this->setCursor(Qt::PointingHandCursor);
            }
        }
    }
    else
    {
        if (inLookRect)
        {
            inLookRect = false;

            this->setCursor(Qt::ArrowCursor);
        }
    }

    posCursor = QCursor::pos();
}

void miniMapWidget::mouseReleaseEvent(QMouseEvent *mouse)
{
    statMouse = release;

    if (lookArea->contains(mouse->pos()))
    {
        inLookRect = true;

        this->setCursor(Qt::PointingHandCursor);
    }
}

void miniMapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //
    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(QColor(0,0,255,30)));
    painter.drawRect(*lookArea);

    painter.end();
}
