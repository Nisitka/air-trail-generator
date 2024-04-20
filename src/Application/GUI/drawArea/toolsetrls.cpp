#include "toolsetrls.h"

#include "areadrawwidget.h"

ToolSetRLS::ToolSetRLS(int id): drawAreaTool(id)
{
    cursor = Qt::CrossCursor;

    setParButton(QPixmap(":/resurs/radarBlue"), "Постановка РЛС");

    //
    pixRLS = new QPixmap(":/resurs/offRLS");
    pixCurRLS = new QPixmap(":/resurs/onRLS");
    curRLScolor.setRgb(0,255,255);

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
    // Отрисовка станций
    int rectX;
    int rectY;

    QPainter& painter = drawArea->getPainter();
    double kZoom = drawArea->getValZoom();
    for (int i=0; i<coordsRLS.size(); i++)
    {
        rectX = coordsRLS[i]->x() * kZoom;
        rectY = coordsRLS[i]->y() * kZoom;

        //
        if (i == idCurRLS)
        {
            painter.drawPixmap(rectX-16, rectY-18, pixCurRLS->scaled(36, 36));
            painter.setPen(curRLScolor);
        }

        else
        {
             painter.drawPixmap(rectX-16, rectY-18, pixRLS->scaled(36, 36));
             painter.setPen(Qt::black);
        }

        painter.drawText(QRect(rectX-16, rectY+15, 36, 20), namesRLS[i]);
    }

    // Если инструмент выбран, то рисуем метку управления станциями
    if (selected)
    {
        drawArea->setPen(QPen(Qt::black, 2, Qt::SolidLine));
        drawArea->drawCircle(xPosRLS, yPosRLS, 2, areaDrawWidget::pix);
    }
}

void ToolSetRLS::mousePress(QMouseEvent *mouse)
{
    statMouse = press;

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
    //drawArea->delDrawTask(areaDrawWidget::toolRLS);
}
