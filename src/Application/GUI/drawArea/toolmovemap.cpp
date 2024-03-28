#include "toolmovemap.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolMoveMap::ToolMoveMap(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    setButton(QPixmap(":/resurs/hand"), "Перемещение на карте");
}

void ToolMoveMap::init()
{
    drawArea->setCursor(Qt::OpenHandCursor);
    statMouse = release;
}

void ToolMoveMap::mousePress(QMouseEvent *mouse)
{
    drawArea->setCursor(Qt::ClosedHandCursor);

    statMouse = press;
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    //
    drawArea->getCoordDrawArea(pXo, pYo);
}

void ToolMoveMap::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    drawArea->setCursor(Qt::OpenHandCursor);

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
        // Новые индексы левого верхнего угла карты
        int Xo, Yo;
        Xo = pXo - (xPressMouse - xMouse);
        Yo = pYo - (yPressMouse - yMouse);

        drawArea->setCoordDrawArea(Xo, Yo);
        drawArea->repaint(); // !!! В будущем для оптимизации можно перенести в Release
    }
}

void ToolMoveMap::end()
{

}


