#include "toolsetrls.h"

#include "areadrawwidget.h"

ToolSetRLS::ToolSetRLS(areaDrawWidget* area): drawAreaTool(area)
{

}

void ToolSetRLS::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Размеры карты в пикселях
    int Wpm, Hpm;
    drawArea->getSizePixMap(Wpm, Hpm);

    // Координаты относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    // Только если клик входит в зону карты
    if (dX < Wpm && dY < Hpm &&
        dX > 0 && dY > 0){

        pXo = Xo;
        pYo = Yo;

        int xMark, yMark;
        double k = drawArea->getValZoom();

        xMark = (xPressMouse - Xo) / k;
        yMark = (yPressMouse - Yo) / k;

        drawArea->setMarkCoordRLS(xMark, yMark);
    }
    else {
        return;
    }
}

void ToolSetRLS::mouseRelease(QMouseEvent *mouse)
{

}

void ToolSetRLS::mouseMove(QMouseEvent *mouse)
{

}
