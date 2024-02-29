#include "toolsetrls.h"

#include "areadrawwidget.h"

ToolSetRLS::ToolSetRLS(areaDrawWidget* area): drawAreaTool(area)
{
    cursor = Qt::CrossCursor;
}

void ToolSetRLS::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolRLS);
}

void ToolSetRLS::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Размеры карты в пикселях
    int Wpm, Hpm;
    drawArea->getSizePixMap(Wpm, Hpm);

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Пиксели относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    pXo = Xo;
    pYo = Yo;

    int xMark, yMark;
    double k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    xMark = dX / k;
    yMark = dY / k;

    drawArea->setMarkCoordRLS(xMark, yMark);
}

void ToolSetRLS::mouseRelease(QMouseEvent *mouse)
{
    /* ... */
}

void ToolSetRLS::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();
}

void ToolSetRLS::end()
{
    drawArea->delDrawTask(areaDrawWidget::toolRLS);
}
