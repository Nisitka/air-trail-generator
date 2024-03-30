#include "toolruler.h"

#include "areadrawwidget.h"

ToolRuler::ToolRuler(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    setParButton(QPixmap(":/resurs/triangle"), "Линейка");

    dTask = new drawTask<ToolRuler>(this, &ToolRuler::procDrawTask);
}
void ToolRuler::procDrawTask()
{
    if (statMouse == press)
    {
        drawArea->setPen(QPen(Qt::black));

        drawArea->drawCircle(xPressMouse, yPressMouse, 3,
                             areaDrawWidget::idMap, areaDrawWidget::pix);
        drawArea->drawCircle(Xmeas, Ymeas, 3,
                             areaDrawWidget::idMap, areaDrawWidget::pix);

        drawArea->drawLine(xPressMouse, yPressMouse,
                           Xmeas,       Ymeas,
                           areaDrawWidget::pix);
    }
}

void ToolRuler::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolRuler, dTask);
}

void ToolRuler::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    Xmeas = xPressMouse;
    Ymeas = yPressMouse;

    drawArea->repaint();
}

void ToolRuler::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    statMouse = release;
}

void ToolRuler::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    if (statMouse == press)
    {
        Xmeas = xMouse;
        Ymeas = yMouse;

        drawArea->repaint();
    }
}

void ToolRuler::end()
{
    drawArea->delDrawTask(id);
}
