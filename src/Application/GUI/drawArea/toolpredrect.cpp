#include "toolpredrect.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolPredRect::ToolPredRect(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    cursor = Qt::CrossCursor;

    addButton(QPixmap(":/resurs/handDrone"), "Прогноз в области");
}

void ToolPredRect::init()
{
    onButton();

    drawArea->setCursor(cursor);

    drawArea->appendDrawTask(areaDrawWidget::toolPredRect);
}

void ToolPredRect::drawTask(QPainter &painter)
{

}

void ToolPredRect::mousePress(QMouseEvent *mouse)
{
    statMouse = press;
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Пиксели относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    //
    int idX, idY;
    double k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    idX = dX / k;
    idY = dY / k;

    drawArea->predictMoveDroneRect(idX, idY);

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
