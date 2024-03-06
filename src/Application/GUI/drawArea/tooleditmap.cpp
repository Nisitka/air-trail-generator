#include "tooleditmap.h"

#include "areadrawwidget.h"

ToolEditMap::ToolEditMap(areaDrawWidget* area): drawAreaTool(area)
{
    cursor = Qt::CrossCursor;

    r = 20;
}

void ToolEditMap::init()
{
    statMouse = release;
}

void ToolEditMap::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Пиксели относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    k = drawArea->getValZoom();
    idX = (double)dX / k;
    idY = (double)dY / k;

    lastKeyMouse = mouse->button() - 1;

    editEarth();
}

void ToolEditMap::editEarth()
{
    int R; // размер курсора инструмента

    R = r*k;
    if (R < 13) R = 13;
    switch (lastKeyMouse) {
    case left:
        drawArea->setCursor(QCursor(QPixmap(":/resurs/toolEarthUp").scaled(R,R)));

        drawArea->upEarth(idX, idY, r);
        break;
    case right:
        drawArea->setCursor(QCursor(QPixmap(":/resurs/toolEarthDown").scaled(R,R)));

        drawArea->downEarth(idX, idY, r);
        break;
    }
}

void ToolEditMap::mouseRelease(QMouseEvent *mouse)
{
    statMouse = release;

    drawArea->updateSignals();
}

void ToolEditMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    int R; // размер курсора инструмента
    double k = drawArea->getValZoom();
    R = r*k;
    if (R < 13) R = 13;
    if (statMouse == press)
    {
        // Координаты левого вернего угла карты отн-но виджета
        int Xo, Yo;
        drawArea->getCoordDrawArea(Xo, Yo);

        // Пиксели относительно карты, а не виджета
        int dX, dY;
        dX = xMouse - Xo;
        dY = yMouse  - Yo;

        int idX = (double)dX / k;
        int idY = (double)dY / k;

        switch (lastKeyMouse) {
        case left:
            drawArea->upEarth(idX, idY, r);
            break;
        case right:
            drawArea->downEarth(idX, idY, r);
            break;
        }
    }
    else
    {
        drawArea->setCursor(QCursor(QPixmap(":/resurs/toolEarthMove").scaled(R,R)));
    }
}

void ToolEditMap::end()
{

}
