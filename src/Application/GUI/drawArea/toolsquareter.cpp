#include "toolsquareter.h"

#include "areadrawwidget.h"

ToolSquareTer::ToolSquareTer(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    setParButton(QPixmap(":/resurs/polygon"), "Площадь области");

    dTask = new drawTask<ToolSquareTer>(this, &ToolSquareTer::procDrawTask);
}

void ToolSquareTer::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolSquarTer, dTask);
}

void ToolSquareTer::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();


    //
    lastKeyMouse = mouse->button() - 1;
    switch (lastKeyMouse) {
    case left: // Добавляем новую точку
        {

        int x = xPressMouse;
        int y = yPressMouse;

        // Находим id дискрет на карте
        drawArea->toIdMapCoords(x, y);

        // В id карты
        polygon.append(QPoint(x, y));

        break;
        }
    case right: // Удаляем последнюю
        {
        if (polygon.size() > 0)
            polygon.removeLast();

        break;
        }
    }

    drawArea->repaint();
}

void ToolSquareTer::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    statMouse = release;
}

void ToolSquareTer::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();
}

void ToolSquareTer::procDrawTask()
{
    drawArea->setPen(QPen(Qt::black));
    drawArea->setBrush(QBrush(Qt::black,  Qt::Dense6Pattern));//Qt::Dense7Pattern;
    drawArea->setRenderHint();

    drawArea->drawPolygon(polygon, areaDrawWidget::idMap);

    int sumX = 0; int sumY = 0;
    int countP = polygon.size();
    int x, y;
    for (int i=0; i<countP; i++)
    {
        x = polygon[i].x();
        y = polygon[i].y();

        sumX += x;
        sumY += y;

        // Tочки в виде кружков
        drawArea->drawCircle(x, y, 2, areaDrawWidget::pix);
    }

    if(countP > 2)
    {
        float S = squarePolygon();

        //
        drawArea->drawText(QRect(sumX/countP, sumY/countP, 40, 15), "dsfsd");
    }

    drawArea->setRenderHint(false);
}

void ToolSquareTer::end()
{
    drawArea->delDrawTask(id);
}

float ToolSquareTer::squarePolygon()
{
    int countPoint = polygon.size();

    float S = 0.0;
    for (int i=0; i<countPoint-1; i++)
    {
        S += checkLine(polygon.at(i), polygon.at(i+1));
    }

    return fabs((float)S / 2.0);
}

float ToolSquareTer::checkLine(const QPoint &p1, const QPoint &p2)
{
    return (p1.x() * p2.y()) - (p1.y() * p2.x());
}
