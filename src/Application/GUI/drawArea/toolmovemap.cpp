#include "toolmovemap.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolMoveMap::ToolMoveMap(int id): drawAreaTool(id)
{
    setParButton(QPixmap(":/resurs/hand"), "Перемещение на карте");
    cursor = Qt::OpenHandCursor;
}

void ToolMoveMap::init()
{
    setCursor();
    statMouse = release;
}

void ToolMoveMap::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    cursor = Qt::ClosedHandCursor;
    setCursor();

    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    //
    drawArea->updateInfoCoordMap(xPressMouse,
                                 yPressMouse);

}

void ToolMoveMap::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    cursor = Qt::OpenHandCursor;
    setCursor();

    statMouse = release;
}

void ToolMoveMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    //
    if (statMouse == press)
    {
        int dX, dY;

        int W = drawArea->width();
        int H = drawArea->height();

        dX = xPressMouse - xMouse;
        dY = yPressMouse - yMouse;

        movedMap((double) dX / W, (double) dY / H);
    }
    else
    {
        drawArea->updateInfoCoordMap(xMouse,
                                     yMouse);
    }
}

void ToolMoveMap::end()
{

}


