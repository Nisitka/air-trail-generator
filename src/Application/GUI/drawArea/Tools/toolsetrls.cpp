#include "toolsetrls.h"

#include "../areadrawwidget.h"

ToolSetRLS::ToolSetRLS(int id,
                       GISInformer* gis,
                       InformerRLS* infoRLS):
    drawAreaTool(id), gis(gis), infoRLS(infoRLS)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/radarBlue"), "Постановка РЛС");

    //
    pixRLS    = QPixmap(":/resurs/offRLS").scaled(36, 36, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);;
    pixCurRLS = QPixmap(":/resurs/onRLS").scaled(36, 36, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);;
    curRLScolor.setRgb(0,255,255);
    RLScolor = Qt::black;

    dTask = new drawTask<ToolSetRLS>(this, &ToolSetRLS::procDrawTask);
}

void ToolSetRLS::updateInfoRLS()
{
    drawArea->repaint();
}

void ToolSetRLS::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolRLS, dTask);
    selected = true;
}

void ToolSetRLS::procDrawTask()
{
    drawArea->setRenderHint();

    // Отрисовка станций
    int countRLS = infoRLS->countRLS();
    int idCurRLS = infoRLS->idCurrentRLS();
    for (int id=0; id<countRLS; id++)
    {
        const LabelRLS* station = infoRLS->getInfoRLS(id);

        // Выбранная РЛС рисуется иначе
        if (id == idCurRLS)
            drawRLS(station, pixCurRLS, curRLScolor);
        else
            drawRLS(station, pixRLS, RLScolor);
    }

    // Если инструмент выбран, то рисуем метку управления станциями
    if (selected)
    {
        drawArea->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        drawArea->drawCircle(xPosRLS, yPosRLS, 2, areaDrawWidget::pix);
    }

    drawArea->setRenderHint(false);
}

void ToolSetRLS::drawRLS(const LabelRLS *station,
                         const QPixmap &icon,
                         const QColor& textColor) const
{
    //
    QVector3D pos;
    station->getPosition(pos);

    // Рисуем условное обозначение РЛС
    drawArea->drawPixmap(pos.x(), pos.y(),
                             -16,     -18,
                         icon);

    // Позывной под РЛС
    drawArea->drawText(QRect(pos.x(), pos.y(), 36, 12), station->getName(),
                       areaDrawWidget::idMap,
                       -16, 15,
                       QColor(0, 0, 0,30), textColor);
}

void ToolSetRLS::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

    // Пиксели клика на виджете
    xPressMouse = mouse->x();
    yPressMouse = mouse->y();

    //
    int xRLS = xPressMouse;
    int yRLS = yPressMouse;

    // Пиксели в индексы клеток текущей активной зоны
    drawArea->toIdMapCoords(xRLS, yRLS);

    //
    xPosRLS = xRLS;
    yPosRLS = yRLS;

    setMarkCoordRLS();
}

void ToolSetRLS::setMarkCoordRLS()
{
    // Отправляем координаты потонциальной РЛС
    setCoordRLS(gis->getCoords(xPosRLS, yPosRLS));

    //
    drawArea->repaint();
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
    selected = false;
    //drawArea->delDrawTask(areaDrawWidget::toolRLS);
}
