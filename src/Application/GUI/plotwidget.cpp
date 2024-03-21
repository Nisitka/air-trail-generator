#include "plotwidget.h"

#include <QPainter>
#include <QDebug>

plotWidget::plotWidget()
{
    points = nullptr;
    drawPoints = nullptr;

    this->setStyleSheet(
                "QWidget {"
                "   background-color: white;"
                "   border: 2px solid gray;"
                "   border-radius: 4px;"
                "}");

    this->setMinimumSize(3*dPartX, 3*dPartY);
}

void plotWidget::pVal(float &Xmin, float &Xmax, float &Ymin, float &Ymax)
{
    Xmax = -1.0;
    Ymax = -1.0;

    Xmin = 9999999.0;
    Ymin = 9999999.0;

    float x;
    float y;
    QPointF* p;
    for (int i=0; i<countPoint; i++)
    {
        p = points + i;
        x = p->x();
        y = p->y();

        if (Xmax < x) Xmax = x;
        if (Xmin > x) Xmin = x;

        if (Ymax < y) Ymax = y;
        if (Ymin > y) Ymin = y;
    }

    return;
}

void plotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Расчет коофициента масштабирования
    int pixW = this->width();
    int pixH = this->height();

    //
    int longVecX = pixW - pixMarginL - pixMargin;
    int longVecY = pixH - pixMarginU - pixMargin;

    //
    float kW = (float) longVecX / dW;
    float kH = (float) longVecY / dH;

    // Разметка
    int countXLine = longVecX / dPartX;
    int countYLine = longVecY / dPartY;

    //
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawLine(pixMarginL, pixMargin, pixMarginL, pixH - pixMarginU);
    painter.drawLine(pixMarginL, pixH - pixMarginU, pixW - pixMargin, pixH - pixMarginU);

    QVector <QLine> Xlines;
    QVector <QLine> hXlines;
    int dX = longVecX / countXLine;
    painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
    for (int i=1; i<=countXLine; i++)
    {
        Xlines.append(QLine(dX*i, pixMargin,
                            dX*i, pixH - pixMarginU));
        hXlines.append(QLine(dX*i, pixH - pixMarginU - 5,
                             dX*i, pixH - pixMarginU));

        painter.drawText(QRect(dX*i - 20, pixH - pixMarginU, 40, 20), QString::number(dX*i/kW, 'g', 5));
    }
    Xlines.append(QLine(pixW - pixMargin, pixMargin,
                        pixW - pixMargin, pixH - pixMarginU));
    hXlines.append(QLine(pixW - pixMargin, pixH - pixMarginU - 5,
                         pixW - pixMargin, pixH - pixMarginU));

    painter.setPen(QPen(QColor(200,200,200), 1, Qt::DashLine));
    painter.drawLines(Xlines);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawLines(hXlines);

    QVector <QLine> Ylines;
    QVector <QLine> hYlines;
    int dY = longVecY / countYLine;
    painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
    for (int i=1; i<=countYLine; i++)
    {
        Ylines.append(QLine(pixMarginL,        dY*i,
                            pixW - pixMargin, dY*i));
        hYlines.append(QLine(pixMarginL,     dY*i,
                             pixMarginL + 5, dY*i));

        painter.drawText(QRect(6, dY*i - 10, 40, 20), QString::number(dY*(countYLine - i + 1)/kH, 'g', 5));
    }
    Ylines.append(QLine(pixMarginL, pixMargin,
                        pixW - pixMargin, pixMargin));
    hYlines.append(QLine(pixMarginL,     pixMargin,
                         pixMarginL + 5, pixMargin));
    painter.setPen(QPen(QColor(200,200,200), 1, Qt::DashLine));
    painter.drawLines(Ylines);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawLines(hYlines);

    // Отрисовка графика
    if (isData)
    {
        QVector <QLine> rays;

        painter.setPen(QPen(QColor(10, 80, 255), 1, Qt::SolidLine));
        painter.setBrush(QBrush(QColor(10, 180, 255, 80)));

        int x, y;
        for (int i=0; i<countPoint; i++)
        {
            x = pixMarginL + (float)points[i].x() * kW;
            y = pixMargin  + longVecY - (float)points[i].y() * kH;

            drawPoints[i].setX(x);
            drawPoints[i].setY(y);

            rays.append(QLine(pixMarginL, pixH - pixMarginU, x, y));
        }
        painter.drawPolygon(drawPoints, countPoint);

        //painter.drawLines(rays);
    }

    painter.end();
}

void plotWidget::clear()
{
    isData = false;

    qDebug() << "Clear!";
    repaint();
}

void plotWidget::setData(QVector<float> X, QVector<float> Y)
{
    delete [] points;
    delete [] drawPoints;

    countPoint = X.size();
    points = new QPointF[countPoint];
    drawPoints = new QPointF[countPoint];

    for (int i=0; i<countPoint; i++)
    {
        points[i].setX(X[i]);
        points[i].setY(Y[i]);
    }

    pVal(Xmin, Xmax, Ymin, Ymax);
    //Ymin += Ymin*0.1;
    dW = (float)Xmax*1.05 - Xmin;
    dH = (float)Ymax*1.05 - Ymin;

    isData = true;

    repaint();
}
