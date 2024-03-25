#include "tooleditmap.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolEditMap::ToolEditMap(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    cursor = Qt::CrossCursor;

    upCurPixmap   = QPixmap(":/resurs/toolEarthUp");
    downCurPixmap = QPixmap(":/resurs/toolEarthDown");
    moveCurPixmap = QPixmap(":/resurs/toolEarthMove");

    r = 20;

    addButton(QPixmap(":/resurs/machinery"), "Редактировать рельеф");
}

void ToolEditMap::init()
{
    onButton();

    statMouse = release;

    //
    k = drawArea->getValZoom();
    updateSizeCursor();
    drawArea->setCursor(QCursor(moveCurPixmap.scaled(R,R)));
}

void ToolEditMap::procDrawTask(QPainter &painter)
{

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
    updateSizeCursor();
    switch (lastKeyMouse) {
    case left:
        cursor = QCursor(upCurPixmap.scaled(R,R));

        upEarth(idX, idY, r);
        break;
    case right:
        cursor = QCursor(downCurPixmap.scaled(R,R));

        downEarth(idX, idY, r);
        break;
    }

    drawArea->setCursor(cursor);
}

void ToolEditMap::mouseRelease(QMouseEvent *mouse)
{
    statMouse = release;
    drawArea->setCursor(QCursor(moveCurPixmap.scaled(R,R)));

    drawArea->updateSignals();
}

void ToolEditMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();


    k = drawArea->getValZoom();
    updateSizeCursor();
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
            upEarth(idX, idY, r);
            break;
        case right:
            downEarth(idX, idY, r);
            break;
        }
    }
    else
    {
        drawArea->setCursor(QCursor(moveCurPixmap.scaled(R,R)));
    }
}

void ToolEditMap::updateSizeCursor()
{
    R = r*k;
    if (R < 13) R = 13;
}

void ToolEditMap::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
    {
        r++;
    }
    else
    {
        if (r > minSIZE) r--;
    }

    updateSizeCursor();
    drawArea->setCursor(QCursor(moveCurPixmap.scaled(R,R)));
}

void ToolEditMap::end()
{
    offButton();
}
