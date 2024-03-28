#include "toolzoommap.h"

#include "areadrawwidget.h"

ToolZoomMap::ToolZoomMap(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    // иконка для курсора во время приближения
    QPixmap iconZoom(":/resurs/zoomTool");
    iconZoom = iconZoom.scaled(25, 25);
    cursor = QCursor(iconZoom);

    setButton(QPixmap(":/resurs/zoom"), "Луппа");
}

void ToolZoomMap::init()
{
    drawArea->setCursor(cursor);
}

void ToolZoomMap::mousePress(QMouseEvent *mouse)
{
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    int wPixMap, hPixMap;
    drawArea->getSizePixMap(wPixMap, hPixMap);

    double k;
    k = drawArea->getValZoom();

    int dW, dH;
    dW = double (wPixMap * dK) / k / 2;
    dH = double (hPixMap * dK) / k / 2;
    switch (mouse->button() - 1) {
    case left:
        Xo -= dW;
        Yo -= dH;

        drawArea->zoom(dK);
        break;
    case right:
        Xo += dW;
        Yo += dH;

        drawArea->zoom(-dK);
        break;
    }

    drawArea->setCoordDrawArea(Xo, Yo);
    drawArea->repaint();
}

void ToolZoomMap::mouseRelease(QMouseEvent *mouse)
{
    /* ... */
}

void ToolZoomMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();
}

void ToolZoomMap::end()
{

}
