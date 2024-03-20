#include "plotwidget.h"

#include <QPainter>
#include <QDebug>

plotWidget::plotWidget()
{
    points = nullptr;
    drawPoints = nullptr;

    clear();

    this->setStyleSheet(
                "QWidget {"
                "   background-color: white;"
                "   border: 2px solid gray;"
                "   padding: 2px 0px;"
                "   border-radius: 2px;"
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
    int pixW = this->width() - (2*pixMargin);
    int pixH = this->height() - (2*pixMargin);

    float kW = (float) pixW / dW;
    float kH = (float) pixH / dH;

    // Разметка
    int countXLine = pixW / dPartX;
    int countYLine = pixH / dPartY;

    QVector <QLine> Xlines;
    int dX = pixW / countXLine;
    painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
    for (int i=0; i<countXLine; i++)
    {
        Xlines.append(QLine(dX/2 + dX*i, 0,
                            dX/2 + dX*i, pixH + (2*pixMargin)));
        if (isData)
            painter.drawText(dX/2 + dX*i + 3, pixH + (2*pixMargin) - 5, QString::number((pixMargin + dX/2 + dX*i)/kW));
    }
    painter.setPen(QPen(QColor(100,100,100), 1, Qt::DashLine));
    painter.drawLines(Xlines);

    QVector <QLine> Ylines;
    int dY = pixH / countYLine;
    painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
    for (int i=0; i<countYLine; i++)
    {
        Ylines.append(QLine(3,    dY/2 + dY*i,
                            pixW + (2*pixMargin), dY/2 + dY*i));
        if (isData)
            painter.drawText(5, dY/2 + dY*i - 3, QString::number(pixMargin + (dY/2 + dY*(countYLine - i - 1))/kH, 'g', 4));
    }
    painter.setPen(QPen(QColor(100,100,100), 1, Qt::DashLine));
    painter.drawLines(Ylines);

    // Отрисовка графика
    if (isData)
    {
        painter.setPen(QPen(QColor(10, 80, 255), 1, Qt::SolidLine));
        painter.setBrush(QBrush(QColor(10, 180, 255, 80)));

        for (int i=0; i<countPoint; i++)
        {
            drawPoints[i].setX(pixMargin + (float)points[i].x() * kW);
            drawPoints[i].setY(pixMargin + pixH - (float)points[i].y() * kH);
        }

        painter.drawPolygon(drawPoints, countPoint);
    }
}

void plotWidget::clear()
{
    isData = false;

    repaint();
}

void plotWidget::setData(QVector<float> X, QVector<float> Y)
{
    isData = true;

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
    dW = Xmax - Xmin;
    dH = Ymax - Ymin;

    repaint();
}
