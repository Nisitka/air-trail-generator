#include "toolruler.h"
#include "math.h"
#include "areadrawwidget.h"

ToolRuler::ToolRuler(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    setParButton(QPixmap(":/resurs/triangle"), "Линейка");

    dTask = new drawTask<ToolRuler>(this, &ToolRuler::procDrawTask);
}
void ToolRuler::procDrawTask()
{
    if(checkDraw)
    {
        drawArea->setPen(QPen(Qt::black));
        drawArea->setRenderHint();

        drawArea->drawCircle(Xb, Yb, 3,
                             areaDrawWidget::idMap, areaDrawWidget::pix);
        drawArea->drawCircle(Xmeas, Ymeas, 3,
                             areaDrawWidget::idMap, areaDrawWidget::pix);

        drawArea->drawLine(xPressMouse, yPressMouse,
                           Xmeas,       Ymeas,
                           areaDrawWidget::pix);

        // Расстояние (в метрах)
        int D = distance(Xb, Yb, Xmeas, Ymeas) * drawArea->getBlockSize();

        // Середина
        int Xt = Xb + ((Xmeas - Xb) / 2);
        int Yt = Yb + ((Ymeas - Yb) / 2);

        QString text = QString::number(D) + " м";
        drawArea->setBrush(QBrush(Qt::white));
        drawArea->drawText(QRect(Xt, Yt, text.size()*6, 15),
                           text);

        drawArea->setRenderHint(false);
    }
}

float ToolRuler::distance(int Xa, int Ya, int Xb, int Yb)
{
    return sqrt(pow(Xb-Xa, 2) + pow(Yb-Ya, 2));
}

void ToolRuler::init()
{
    drawArea->setCursor(cursor);

    checkDraw = false;
    drawArea->appendDrawTask(areaDrawWidget::toolRuler, dTask);
}

void ToolRuler::mousePress(QMouseEvent *mouse)
{
    statMouse = press;
    checkDraw = true;

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    //
    Xb = xPressMouse;
    Yb = yPressMouse;

    //
    Xmeas = xPressMouse;
    Ymeas = yPressMouse;

    drawArea->repaint();
}

void ToolRuler::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    statMouse = release;
}

void ToolRuler::mouseMove(QMouseEvent *mouse)
{
    // Текущие координаты
    xMouse = mouse->x();
    yMouse = mouse->y();

    // Обновляем показания координат карты
    drawArea->updateInfoCoordMap(xMouse,
                                 yMouse);

    if (statMouse == press)
    {
        Xmeas = xMouse;
        Ymeas = yMouse;

        drawArea->repaint();
    }
}

void ToolRuler::end()
{
    drawArea->delDrawTask(id);
}
