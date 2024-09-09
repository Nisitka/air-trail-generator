#include "toolmovemap.h"

#include "../areadrawwidget.h"

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
    lastKeyMouse = mouse->button();

    cursor = Qt::ClosedHandCursor;
    setCursor();

    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    //
    drawArea->setCurrentPixPoint(xPressMouse,
                                 yPressMouse);

}

void ToolMoveMap::mouseRelease(QMouseEvent *mouse)
{
    cursor = Qt::OpenHandCursor;
    setCursor();

    statMouse = release;

    xMouse = mouse->x();
    yMouse = mouse->y();

    //
    mouseReleaseSignal();
}

void ToolMoveMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    //
    if (statMouse == press)
    {
        int W = drawArea->width();
        int H = drawArea->height();

        //
        dX = xPressMouse - xMouse;
        dY = yPressMouse - yMouse;

        switch (lastKeyMouse) {
        case Qt::LeftButton:
            movedLookArea((double) dX / W, (double) dY / H);

            break;
        case Qt::RightButton:
            drawArea->changeAngleRotate((double)dY / H);

            break;
        default:
            break;
        }

    }
    else
    {
        drawArea->setCurrentPixPoint(xMouse,
                                     yMouse);
    }
}

void ToolMoveMap::end()
{

}


