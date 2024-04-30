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

    // Таймер определяет такты изменения рельефа
    timer = new QTimer(this);
    connect(timer,  SIGNAL(timeout()),
            this,   SLOT(editEarth()));
}

void ToolEditMap::init()
{
    statMouse = release;

    info("Редактор рельефа");

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

    //
    lastKeyMouse = mouse->button() - 1;
    switch (lastKeyMouse) {
    case left:
        cursor = QCursor(upCurPixmap.scaled(R,R));
        break;
    case right:
        cursor = QCursor(downCurPixmap.scaled(R,R));
        break;
    }
    setCursor();

    //
    timer->start(10);
}

void ToolEditMap::editEarth()
{
    switch (lastKeyMouse) {
    case left:
        upEarth(idX, idY, r);
        break;
    case right:
        downEarth(idX, idY, r);
        break;
    }
}

void ToolEditMap::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    timer->stop();

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

    // В целях оптимизации
    if (statMouse == press)
    {
        idX = xMouse;
        idY = yMouse;
        drawArea->toIdMapCoords(idX, idY);
    }
    else
    {
        // Обновляем показания координат карты
        drawArea->updateInfoCoordMap(xMouse,
                                     yMouse);
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
            if (r < maxSIZE) r++;
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
    info("");
}
