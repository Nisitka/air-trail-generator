#include "tooldefault.h"

#include "areadrawwidget.h"

toolDefault::toolDefault(areaDrawWidget* area): drawAreaTool(area)
{

}

void toolDefault::mousePress(QMouseEvent *mouse)
{

}

void toolDefault::mouseRelease(QMouseEvent *mouse)
{

}

void toolDefault::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();
}

void toolDefault::end()
{

}
