#include "tooldefault.h"

#include "areadrawwidget.h"

toolDefault::toolDefault(int id): drawAreaTool(id)
{

}

void toolDefault::mousePress(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void toolDefault::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void toolDefault::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    // Обновляем показания координат карты
    drawArea->updateInfoCoordMap(xMouse,
                                 yMouse);
}

void toolDefault::end()
{

}
