#include "toolpredrect.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolPredRect::ToolPredRect(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    cursor = Qt::CrossCursor;

    addButton(QPixmap(":/resurs/handDrone"), "Прогноз в области");

    dTask = new drawTask<ToolPredRect>(this, &ToolPredRect::procDrawTask);


    idXoPredict = 0;
    idYoPredict = 0;
}

void ToolPredRect::init()
{
    onButton();

    drawArea->setCursor(cursor);

    drawArea->appendDrawTask(areaDrawWidget::toolPredRect, dTask);
}

void ToolPredRect::procDrawTask(QPainter &painter)
{
    // отрисовка эелементов поставленного БПЛА
    k = drawArea->getValZoom();

    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Квадрат прогноза (текущего)
    painter.setPen(QColor(255,0,128));
    painter.drawRect(idXoPredict * k + Xo + 1, idYoPredict * k + Yo + 1, 200*k - 1, 200*k - 1);

    // Метка БПЛА
    int x = idXRect*k + Xo;
    int y = idYRect*k + Yo;

    painter.drawLine(x-3, y,
                     x+3, y);
    painter.drawLine(x, y-3,
                     x, y+3);

    // Квадрат прогноза (возможного)
    painter.setPen(QColor(143, 32, 255));
    painter.drawRect(xMouse - (100 * k) + 1, yMouse - (100 * k) + 1, 200*k - 1, 200*k - 1);

    // Линия прогноза
    if (drawLineRect)
    {
        painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
        painter.drawLine(idXRect * k  + Xo, idYRect  * k + Yo,
                         idPRectX * k + Xo, idPRectY * k + Yo);
    }
}

void ToolPredRect::mousePress(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    statMouse = press;
    xPressMouse = xMouse;
    yPressMouse = yMouse;

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Пиксели относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    //
    k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    idXRect = dX / k;
    idYRect = dY / k;

    //
    idXoPredict = idXRect  - 100;
    idYoPredict = idYRect  - 100;

    drawArea->repaint();
}

void ToolPredRect::mouseRelease(QMouseEvent *mouse)
{

}

void ToolPredRect::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    drawArea->repaint();
}

void ToolPredRect::end()
{
    offButton();
    drawArea->delDrawTask(areaDrawWidget::toolPredRect);
}
