#include "toolpredtrail.h"

#include "areadrawwidget.h"

ToolPredTrail::ToolPredTrail(areaDrawWidget* area, int id, QObject *parent): drawAreaTool(area, id, parent)
{
    cursor = Qt::CrossCursor;

    addButton(QPixmap(":/resurs/trail2"), "Прогноз маршрута");

    //
    pixBeginDrone = new QPixmap(":/resurs/droneStart");
    pixFinishDrone = new QPixmap(":/resurs/droneFinish");

    dTask = new drawTask<ToolPredTrail>(this, &ToolPredTrail::procDrawTask);
}

void ToolPredTrail::init()
{
    onButton();

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

void ToolPredTrail::procDrawTask(QPainter &painter)
{
    k = drawArea->getValZoom();
    int rP = 50 * k;

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;

    int pX, pY;
    drawArea->getCoordDrawArea(Xo, Yo);
    for (int i=0; i<trail.size() - 1; i++)
    {
        painter.setPen(QPen(QColor(255,0,128), 1));

        pX = trail[i]->x() * k  + Xo;
        pY = trail[i]->y() * k  + Yo;

        painter.drawEllipse(QPoint(pX, pY), 2, 2);
        //painter.drawEllipse(QPoint(pX, pY), rP, rP);
        painter.drawLine(pX, pY,
                         trail[i+1]->x() * k  + Xo, trail[i+1]->y() * k  + Yo);
    }
    // отрисовываем последнию точку
    if (trail.size() > 0)
    {
        painter.drawEllipse(QPoint(trail.last()->x() * k  + Xo, trail.last()->y() * k  + Yo), rP, rP);
    }


    // отрисовывать начальную и конечные точкитраектории
    painter.setPen(QPen(QColor(51,255,240), 1));

    int bX = beginPoint.x() * k  + Xo;
    int bY = beginPoint.y() * k  + Yo;

    int fX = lastPoint.x() * k  + Xo;
    int fY = lastPoint.y() * k  + Yo;

    painter.drawPixmap(bX-16, bY-32, pixBeginDrone->scaled(32,32));
    painter.drawPixmap(fX-16, fY-34, pixFinishDrone->scaled(32,32));

    painter.drawEllipse(QPoint(fX, fY), 2, 2);
    painter.drawEllipse(QPoint(bX, bY), 2, 2);

    //
    painter.setPen(QPen(QColor(255,0,128), 1, Qt::DashLine));
    painter.drawLine(bX, bY, fX, fY);
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
    k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    idX = dX / k;
    idY = dY / k;

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
