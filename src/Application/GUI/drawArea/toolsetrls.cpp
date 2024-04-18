#include "toolsetrls.h"

#include "areadrawwidget.h"

ToolSetRLS::ToolSetRLS(int id): drawAreaTool(id)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/radarBlue"), "Постановка РЛС");

    dTask = new drawTask<ToolSetRLS>(this, &ToolSetRLS::procDrawTask);
}

void ToolSetRLS::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolRLS, dTask);
}

void ToolSetRLS::setMarkCoordRLS()
{
    // Отправляем координаты потонциальной РЛС
    setCoordRLS(xPosRLS, yPosRLS);

    //
    drawArea->repaint();
}

void ToolSetRLS::procDrawTask()
{
    qDebug() << "draw!";

    drawArea->setPen(QPen(Qt::black, 2, Qt::SolidLine));
    drawArea->drawCircle(xPosRLS, yPosRLS, 2, areaDrawWidget::pix);
}

void ToolSetRLS::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    qDebug() << "press!!!";

    // Координаты левого вернего угла карты отн-но виджета
    int Xo, Yo;
    drawArea->getCoordDrawArea(Xo, Yo);

    // Размеры карты в пикселях
    int Wpm, Hpm;
    drawArea->getSizePixMap(Wpm, Hpm);

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    // Пиксели относительно карты, а не виджета
    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    pXo = Xo;
    pYo = Yo;

    k = drawArea->getValZoom();

    // Пиксели в индексы клеток карты
    xPosRLS = dX / k;
    yPosRLS = dY / k;

    setMarkCoordRLS();
}

void ToolSetRLS::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ToolSetRLS::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    // Обновляем показания координат карты
    drawArea->updateInfoCoordMap(xMouse,
                                 yMouse);
}

void ToolSetRLS::end()
{
    drawArea->delDrawTask(areaDrawWidget::toolRLS);
}
