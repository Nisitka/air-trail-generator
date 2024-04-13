#include "toolmovemap.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolMoveMap::ToolMoveMap(areaDrawWidget* area, int id): drawAreaTool(area, id)
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

    //
    drawArea->getCoordDrawArea(pXo, pYo);
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


