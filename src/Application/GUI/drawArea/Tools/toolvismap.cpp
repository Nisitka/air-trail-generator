#include "toolvismap.h"

#include "../areadrawwidget.h"

ToolVisMap::ToolVisMap(int id): drawAreaTool(id)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/hand3D"), "Область 3D визуализации");

    dTask = new drawTask<ToolVisMap>(this, &ToolVisMap::procDrawTask);
}

void ToolVisMap::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolVis, dTask);

    statMouse = release;
}

void ToolVisMap::procDrawTask()
{
    drawArea->setPen(QPen(QColor(0,0,213), 1, Qt::DashLine));
    drawArea->drawRect(idXa, idYa, idXb, idYb);
}

void ToolVisMap::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Пиксели в индексы клеток карты
    idXa = xPressMouse;
    idYa = yPressMouse;
    drawArea->toIdMapCoords(idXa, idYa);

    idXb = idXa;
    idYb = idYa;

    drawArea->repaint();
}

void ToolVisMap::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    statMouse = release;

    int idXo, idYo;
    if (idXa > idXb) idXo = idXb;
    else idXo = idXa;
    if (idYa > idYb) idYo = idYb;
    else idYo = idYa;

    int numW = abs(idXa - idXb);
    int numL = abs(idYa - idYb);

    if (numW < 2) numW = 2;
    if (numL < 2) numL = 2;

    updateRect3D(idXo, idYo,
                 numW, numL);
}

void ToolVisMap::mouseMove(QMouseEvent *mouse)
{ 
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    if (statMouse == press)
    {
        // Пиксели относительно карты, а не виджета
        idXb = xMouse;
        idYb = yMouse;
        drawArea->toIdMapCoords(idXb, idYb);

//        drawArea->setRectVis(idXa, idYa,
//                             idXb, idYb);
        drawArea->repaint();
    }

    // Обновляем показания координат карты
    drawArea->setCurrentPixPoint(xMouse,
                                 yMouse);
}

void ToolVisMap::end()
{
    drawArea->delDrawTask(areaDrawWidget::toolVis);
}
