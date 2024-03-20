#include "toolpredtrail.h"

#include "areadrawwidget.h"

ToolPredTrail::ToolPredTrail(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    cursor = Qt::CrossCursor;

    addButton(QPixmap(":/resurs/trail2"), "Прогноз маршрута");
}

void ToolPredTrail::init()
{
    onButton();

    drawArea->setCursor(cursor);

    drawArea->appendDrawTask(areaDrawWidget::toolPredTrail);
}

void ToolPredTrail::mousePress(QMouseEvent *mouse)
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

    //
    int idX, idY;
    double k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    idX = dX / k;
    idY = dY / k;

    switch (mouse->button() - 1) {
    case left:
        drawArea->setBeginPointTrail(idX, idY);
        break;
    case right:
        drawArea->setLastPointTrail(idX, idY);
        break;
    }
    drawArea->sendPointsTrail();

    //
    drawArea->sendPointsTrail();

    drawArea->repaint();
}

void ToolPredTrail::mouseRelease(QMouseEvent *mouse)
{

}

void ToolPredTrail::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();
}

void ToolPredTrail::end()
{
    offButton();
    //drawArea->delDrawTask(areaDrawWidget::toolPredTrail);
}
