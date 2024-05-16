#include "minimapwidget.h"

#include <QPainter>

#include <QDebug>

miniMapWidget::miniMapWidget(QWidget* parent, int maxH, int maxW):
    QLabel(parent), // Виджет, на котором будет располагаться миникарта
    maxW(maxW), maxH(maxH)
{
    kSize = (double) maxW/maxH;

    //
    this->setMouseTracking(true);

    statMouse = release;

    //
    inLookRect = false;

    //
    lookArea = new QRect(0, 0, 15, 10);

    this->move(0,0);

    this->setFixedSize(maxW, maxH);
    this->setStyleSheet("QWidget{"
                        "   background: rgb(128,128,128,25);"
                        "   border-radius: 5px;"
                        "   border: 1px solid rgb(0,0,0);"
                        "}");
    this->show();
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

    //
    if (lX) QCursor::setPos(posCursor.x(), QCursor::pos().y());
    if (lY) QCursor::setPos(QCursor::pos().x(), posCursor.y());


    lookArea->moveTo(idX, idY);

    repaint();
}

void miniMapWidget::setSizeLookArea(int W, int H)
{
    lookArea->setSize(QSize(W, H));
}

void miniMapWidget::setMaxSize(int W, int H)
{
    maxW = W; maxH = H;

    // Одоптируем размеры под текущую карту
    setSizeActionArea(sizeActionArea);
}

void miniMapWidget::setSizeActionArea(const QSize& size)
{
    //
    sizeActionArea = size;

    double kW = (double)sizeActionArea.width()  / maxW;
    double kH = (double)sizeActionArea.height() / maxH;

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

    this->setFixedSize(W, H);
}

void miniMapWidget::mousePressEvent(QMouseEvent *mouse)
{
    statMouse = press;

    posMouse = mouse->pos();
    if (lookArea->contains(posMouse))
    {
        inLookRect = true;

        pointPress = posMouse - lookArea->topLeft();

        this->setCursor(Qt::CrossCursor);
    }
}

void miniMapWidget::mouseMoveEvent(QMouseEvent *mouse)
{
    posMouse = mouse->pos();
    if (lookArea->contains(posMouse))
    {
        if (statMouse == press)
        {
            QPoint p = mouse->pos() - pointPress;
            setPosLookArea(p.x(), p.y());
        }
        else
        {
            if (!inLookRect)
            {
                inLookRect = true;

                this->setCursor(Qt::OpenHandCursor);
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

        this->setCursor(Qt::OpenHandCursor);
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
