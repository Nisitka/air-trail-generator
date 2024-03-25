#include "toolvismap.h"

#include "areadrawwidget.h"

ToolVisMap::ToolVisMap(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    cursor = Qt::CrossCursor;

    addButton(QPixmap(":/resurs/hand3D"), "Область 3D визуализации");

    dTask = new drawTask<ToolVisMap>(this, &ToolVisMap::procDrawTask);
}

void ToolVisMap::init()
{
    onButton();
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolVis, dTask);
}

void ToolVisMap::procDrawTask(QPainter &painter)
{
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // отрисовка области 3D визуализации
    painter.setPen(QPen(QColor(0,0,213), 1, Qt::DashLine));

    painter.drawRect(QRect(QPoint(idXa*k + Xo, idYa*k + Yo),
                           QPoint(idXb*k + Xo, idYb*k + Yo)));
}

void ToolVisMap::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    k = drawArea->getValZoom();
    // Дискреты карты
    idXa = double (xPressMouse - Xo) / k;
    idYa = double (yPressMouse - Yo) / k;

    //drawArea->setRectVis(idXa, idYa, idXa, idYa);

    drawArea->repaint();
}

void ToolVisMap::mouseRelease(QMouseEvent *mouse)
{
    statMouse = release;

    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

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
        // Координаты левого вернего угла карты отн-но виджета
        int Xo, Yo;
        drawArea->getCoordDrawArea(Xo, Yo);

        double k = drawArea->getValZoom();

        // Пиксели относительно карты, а не виджета
        idXb = double (xMouse - Xo) / k;
        idYb = double (yMouse - Yo) / k;

//        drawArea->setRectVis(idXa, idYa,
//                             idXb, idYb);
        drawArea->repaint();
    }
}

void ToolVisMap::end()
{
    offButton();
    drawArea->delDrawTask(areaDrawWidget::toolVis);
}
