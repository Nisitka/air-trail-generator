#include "toolzoommap.h"

#include "../areadrawwidget.h"

ToolZoomMap::ToolZoomMap(int id): drawAreaTool(id)
{
    // иконка для курсора во время приближения
    QPixmap iconZoom(":/resurs/zoomTool");
    iconZoom = iconZoom.scaled(25, 25);
    cursor = QCursor(iconZoom);

    setParButton(QPixmap(":/resurs/zoom"), "Луппа");
}

void ToolZoomMap::init()
{
    drawArea->setCursor(cursor);
}

void ToolZoomMap::mousePress(QMouseEvent *mouse)
{
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    switch (mouse->button() - 1) {
    case left:
        drawArea->zoom(dK);
        break;
    case right:
        drawArea->zoom(-dK);
        break;
    }

    drawArea->repaint();
}

void ToolZoomMap::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ToolZoomMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    // Обновляем показания координат карты
    drawArea->updateInfoCoordMap(xMouse,
                                 yMouse);
}

void ToolZoomMap::end()
{

}
