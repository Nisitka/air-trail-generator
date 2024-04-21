#include "toolpredtrail.h"

#include "areadrawwidget.h"

ToolPredTrail::ToolPredTrail(int id, QObject *parent): drawAreaTool(id, parent)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/trail2"), "Прогноз маршрута");

    //
    pixBeginDrone = new QPixmap(":/resurs/droneStart");
    pixFinishDrone = new QPixmap(":/resurs/droneFinish");

    dTask = new drawTask<ToolPredTrail>(this, &ToolPredTrail::procDrawTask);
}

void ToolPredTrail::init()
{
    selected = true;

    drawArea->setCursor(cursor);

    drawArea->appendDrawTask(areaDrawWidget::toolPredTrail, dTask);
}

void ToolPredTrail::startPredictTrail()
{
    // Очищаем траекторию с предыдущего прогноза
    clearTrail();
}

void ToolPredTrail::finishPredictTrail()
{

}

void ToolPredTrail::addPointTrail(int idXpt, int idYpt, int idZpt)
{
    trail.append(new QPoint(idXpt, idYpt));

    drawArea->repaint();
}

void ToolPredTrail::clearTrail()
{
    for (int i=0; i<trail.size(); i++)
    {
        delete trail[i];
    }
    trail.clear();
}

void ToolPredTrail::procDrawTask()
{
    drawArea->setRenderHint();

    for (int i=0; i<trail.size() - 1; i++)
    {
        drawArea->setPen(QPen(QColor(255,0,128), 1));

        drawArea->drawCircle(trail[i]->x(), trail[i]->y(), 2, areaDrawWidget::pix);

        drawArea->drawLine(trail[i]->x(), trail[i]->y(),
                           trail[i+1]->x(), trail[i+1]->y());
    }
    // отрисовываем последнию точку
    if (trail.size() > 0)
    {
        drawArea->drawCircle(trail.last()->x(), trail.last()->y(), Rpred);
    }

    // отрисовывать начальную и конечные точкитраектории
    drawArea->setPen(QPen(QColor(51,255,240), 1));

    int bX = beginPoint.x();
    int bY = beginPoint.y();

    int fX = lastPoint.x();
    int fY = lastPoint.y();

    // Рисуем иконки начальной и конечной точек
    drawArea->drawPixmap(bX, bY, -16, -32, pixBeginDrone->scaled(32,32));
    drawArea->drawPixmap(fX, fY, -16, -34, pixFinishDrone->scaled(32,32));

    // Сами точки в виде кружков
    drawArea->drawCircle(fX, fY, 2, areaDrawWidget::pix);

    drawArea->drawCircle(bX, bY, 2, areaDrawWidget::pix);
    // Зона прогноза в единичной итерации
    drawArea->setPen(QPen(QColor(255,0,128)));
    drawArea->drawCircle(bX, bY, Rpred);

    // Самый короткий путь пунктиром
    drawArea->setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
    drawArea->drawLine(bX, bY, fX, fY);

    // Область прогноза в единичной итерации
    if (selected)
    {
        drawArea->setPen(QPen(QColor(143, 32, 255)));
        drawArea->drawCircle(xMouse, yMouse, Rpred, areaDrawWidget::idMap, areaDrawWidget::pix);
    }

    drawArea->setRenderHint(false);
}

void ToolPredTrail::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
    {
        Rpred++;
    }
    else
    {
        if (Rpred > 5) Rpred--;
    }

    setRpred(Rpred);
    drawArea->repaint();
}

void ToolPredTrail::mousePress(QMouseEvent *mouse)
{
    statMouse = press;
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Пиксели в индексы клеток карты
    idX = xPressMouse;
    idY = yPressMouse;
    drawArea->toIdMapCoords(idX, idY);

    switch (mouse->button() - 1) {
    case left:
        beginPoint.setX(idX);
        beginPoint.setY(idY);
        break;
    case right:
        lastPoint.setX(idX);
        lastPoint.setY(idY);
        break;
    }

    //
    sendPointsTrail(beginPoint.x(), beginPoint.y(),
                     lastPoint.x(),  lastPoint.y());

    drawArea->repaint();
}

void ToolPredTrail::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ToolPredTrail::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    // Обновляем показания координат карты
    drawArea->updateInfoCoordMap(xMouse,
                                 yMouse);

    drawArea->repaint();
}

void ToolPredTrail::end()
{
    selected = false;
    //drawArea->delDrawTask(areaDrawWidget::toolPredTrail);
}
