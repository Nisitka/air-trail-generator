#include "tooleditmap.h"

#include "areadrawwidget.h"

#include <QDebug>
#include <QApplication>

ToolEditMap::ToolEditMap(int id): drawAreaTool(id)
{
    cursor = Qt::CrossCursor;

    upCurPixmap   = QPixmap(":/resurs/toolEarthUp");
    downCurPixmap = QPixmap(":/resurs/toolEarthDown");
    moveCurPixmap = QPixmap(":/resurs/toolEarthMove");

    r = 20;

    setParButton(QPixmap(":/resurs/machinery"), "Редактировать рельеф");
}

void ToolEditMap::init()
{
    statMouse = release;

    //
    k = drawArea->getValZoom();
    updateSizeCursor();
    drawArea->setCursor(QCursor(moveCurPixmap.scaled(R,R)));
}

void ToolEditMap::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    //
    idX = xPressMouse;
    idY = yPressMouse;
    drawArea->toIdMapCoords(idX, idY);

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

    setCursor();
}

void ToolEditMap::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    statMouse = release;

    cursor = QCursor(moveCurPixmap.scaled(R,R));
    setCursor();

    drawArea->updateSignals();
}

void ToolEditMap::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    if (statMouse == press)
    {
        //
        idX = xMouse;
        idY = yMouse;
        drawArea->toIdMapCoords(idX, idY);

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
        // Обновляем показания координат карты
        drawArea->updateInfoCoordMap(xMouse,
                                     yMouse);

        cursor = QCursor(moveCurPixmap.scaled(R,R));
        drawArea->setCursor(cursor);
    }
}

void ToolEditMap::updateSizeCursor()
{
    k = drawArea->getValZoom();
    R = r*k;
    if (R < 13) R = 13;
}

void ToolEditMap::wheelEvent(QWheelEvent *event)
{
    // Если не нажата клавиша CTRL
    if (QApplication::keyboardModifiers() != Qt::ControlModifier)
    {
        if (event->angleDelta().y() > 0)
        {
            r++;
        }
        else
        {
            if (r > minSIZE) r--;
        }
    }

    updateSizeCursor();
    cursor = QCursor(moveCurPixmap.scaled(R,R));
    drawArea->setCursor(cursor);
}

void ToolEditMap::end()
{

}
