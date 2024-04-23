#include "toolsetrls.h"

#include "areadrawwidget.h"

ToolSetRLS::ToolSetRLS(int id): drawAreaTool(id)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/radarBlue"), "Постановка РЛС");

    //
    pixRLS = QPixmap(":/resurs/offRLS").scaled(36, 36, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);;
    pixCurRLS = QPixmap(":/resurs/onRLS").scaled(36, 36, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);;
    curRLScolor.setRgb(0,255,255);
    RLScolor = Qt::black;

    dTask = new drawTask<ToolSetRLS>(this, &ToolSetRLS::procDrawTask);
}

void ToolSetRLS::addRLS(QPoint *posRLS, const QString& nameNewRLS)
{
    coordsRLS.append(posRLS);
    namesRLS.append(nameNewRLS);
}

void ToolSetRLS::delRLS(int indexRLS)
{
    coordsRLS.removeAt(indexRLS);
    namesRLS.removeAt(indexRLS);

    drawArea->repaint();
}

void ToolSetRLS::setCurRLS(int idRLS)
{
    idCurRLS = idRLS;
    drawArea->repaint();
}

void ToolSetRLS::init()
{
    drawArea->setCursor(cursor);
    drawArea->appendDrawTask(areaDrawWidget::toolRLS, dTask);
    selected = true;
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
    drawArea->setRenderHint();

    // Отрисовка станций
    QPixmap icon;
    QColor textColor;
    for (int i=0; i<coordsRLS.size(); i++)
    {
        //
        if (i == idCurRLS) // В юудущем можно будет проверять выделенность нескольких РЛС
        {
            icon = pixCurRLS ;
            textColor = curRLScolor;
        }
        else
        {
            icon = pixRLS;
            textColor = RLScolor;
        }

        // Рисуем условное обозначение РЛС
        drawArea->drawPixmap(coordsRLS[i]->x(), coordsRLS[i]->y(),
                                           -16,               -18,
                             icon);

        drawArea->drawText(QRect(coordsRLS[i]->x(), coordsRLS[i]->y(), 36, 12), namesRLS[i],
                           areaDrawWidget::idMap,
                           -16, 15,
                           QColor(0, 0, 0,30), textColor);
    }

    // Если инструмент выбран, то рисуем метку управления станциями
    if (selected)
    {
        drawArea->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        drawArea->drawCircle(xPosRLS, yPosRLS, 2, areaDrawWidget::pix);
    }

    drawArea->setRenderHint(false);
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

    // Пиксели в индексы клеток карты
    drawArea->toIdMapCoords(xRLS, yRLS);

    //
    xPosRLS = xRLS;
    yPosRLS = yRLS;

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
    selected = false;
    //drawArea->delDrawTask(areaDrawWidget::toolRLS);
}
