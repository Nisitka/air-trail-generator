#include "toolpredrect.h"

#include "areadrawwidget.h"

#include <QDebug>

ToolPredRect::ToolPredRect(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/handDrone"), "Прогноз в области");

    dTask = new drawTask<ToolPredRect>(this, &ToolPredRect::procDrawTask);


    idXoPredict = 0;
    idYoPredict = 0;
}

void ToolPredRect::init()
{
    drawArea->setCursor(cursor);

    drawArea->appendDrawTask(areaDrawWidget::toolPredRect, dTask);
}

void ToolPredRect::procDrawTask()
{
    drawArea->setRenderHint();

    // Установленная зона прогноза в единичной итерации
    drawArea->setPen(QPen(QColor(255,0,128)));
    drawArea->drawCircle(idXoPredict, idYoPredict, Rpred);

    // Метка БПЛА
    drawArea->drawCircle(idXRect, idYRect, 2, areaDrawWidget::pix);

    // Область прогноза в единичной итерации
    drawArea->setPen(QPen(QColor(143, 32, 255)));
    drawArea->drawCircle(xMouse, yMouse, Rpred, areaDrawWidget::idMap, areaDrawWidget::pix);

    // Линия прогноза
    if (drawLineRect)
    {
        /* ... */
    }

    drawArea->setRenderHint(false);
}

void ToolPredRect::mousePress(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    statMouse = press;
    xPressMouse = xMouse;
    yPressMouse = yMouse;

//    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Пиксели относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    //
    k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    idXRect = dX / k;
    idYRect = dY / k;

    //
    idXoPredict = idXRect;
    idYoPredict = idYRect;

    drawArea->repaint();
}

void ToolPredRect::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ToolPredRect::wheelEvent(QWheelEvent *event)
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

void ToolPredRect::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    // Обновляем показания координат карты
    drawArea->updateInfoCoordMap(xMouse,
                                 yMouse);

    drawArea->repaint();
}

void ToolPredRect::end()
{
    drawArea->delDrawTask(areaDrawWidget::toolPredRect);
}
