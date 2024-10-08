#include "scrollmapwidget.h"

#include <QBoxLayout>
#include <QScrollBar>

#include <QApplication>

ScrollMapWidget::ScrollMapWidget(areaDrawWidget* drawArea_):
    drawArea(drawArea_)
{
    backWidget = new QWidget;
    QHBoxLayout* horLayout = new QHBoxLayout(backWidget);

    this->setWidget(backWidget);
    this->setWidgetResizable(true);

    //
    horLayout->addWidget(drawArea);
//    connect(drawArea, SIGNAL(changedCurrentCoords(const Coords)),
//            this,     SLOT(updateCoord(const Coords)));
    connect(drawArea, SIGNAL(changedCurrentCoords(const Coords)),
            this,     SLOT(updateInfoCurCoords(const Coords)));

    backWidget->setStyleSheet("QWidget{"
                     ///"   background-image: url(:/resurs/pattern4.jpg);"
                     "   background-color: rgb(255,255,255);"
                     "   border: 1px solid transparent;"
                     "};)");

    this->setStyleSheet("QScrollArea{"
                        "   background-color: rgb(230,230,230);"
                        "   border: 1px solid gray;"
                        "};)");

    // Слайдер для изменения масштаба
    zoomSlider = new ZoomControllerWidget(this);
    zoomSlider->move(-5, 0);
    connect(zoomSlider, SIGNAL(zoomChanged(double)),
            drawArea,   SLOT(setZoom(double)));
    connect(drawArea, SIGNAL(resized()),
            this,     SLOT(updateZoomContr()));

    // Миникарта
    miniMap = new miniMapWidget(this, 150, 120);
    miniMap->setDistEdge(20, 20);
    miniMap->setSizeActionArea(drawArea->size());
    connect(miniMap, SIGNAL(movedLookArea(double,double)),
            this,    SLOT(setPosLookMap(double,double)));

    //
    verScroll = verticalScrollBar();
    horScroll = horizontalScrollBar();

    connect(verScroll, SIGNAL(rangeChanged(int,int)),
            this,      SLOT(updateMiniMap()));
    connect(horScroll, SIGNAL(rangeChanged(int,int)),
            this,      SLOT(updateMiniMap()));
    connect(verScroll, SIGNAL(valueChanged(int)),
            this,      SLOT(updateMiniMap()));
    connect(horScroll, SIGNAL(valueChanged(int)),
            this,      SLOT(updateMiniMap()));

    readyActionArea = true;

    // Гифка загрузки новой области
    loadingWidget = new processTmpWidget(this);
}

void ScrollMapWidget::updateInfoCurCoords(const Coords coords)
{
    if (readyActionArea)
    {
        changedCurrentCoords(coords);
    }
}

void ScrollMapWidget::updateZoomContr()
{
    zoomSlider->setValSlider(drawArea->getValZoom() * 100);
}

void ScrollMapWidget::CreateItems()
{

}

void ScrollMapWidget::ItemChanged(ScrollItem *item)
{

}


void ScrollMapWidget::updateMiniMap()
{

    //
    double pW = (double)this->width()  / drawArea->width();
    double pH = (double)this->height() / drawArea->height();
    miniMap->setSizeActionArea(drawArea->size());
    miniMap->setPaternSizeLookArea(pW,pH);

    //
    double pY = (double)verScroll->value() / drawArea->height();
    double pX = (double)horScroll->value() / drawArea->width();
    miniMap->setPosLookArea(pX, pY);
}

void ScrollMapWidget::setMoveMapEnabled(bool val)
{
    //
    verticalScrollBar()->setValue(lastCurY);
    horizontalScrollBar()->setValue(lastCurX);

    readyActionArea = val;

    if (readyActionArea)
    {
        loadingWidget->Hide();
        drawArea->repaint();
    }
}

void ScrollMapWidget::movePosLookMap(double dX, double dY)
{
    if (readyActionArea)
    {
        lastCurY = verScroll->value();
        int posY = lastCurY + (dY * drawArea->height());
        verScroll->setValue(posY);

        lastCurX = horScroll->value();
        int posX = lastCurX + (dX * drawArea->width());
        horScroll->setValue(posX);

        // Перемещаем область на миникарте соответсвенно
        miniMap->setPosLookArea((double)posX/drawArea->height(),
                                (double)posY/drawArea->width());

        ///
        //drawArea->movePosCamera(dX, dY);
    }
}

void ScrollMapWidget::setPosLookMap(double pX, double pY)
{
    if (readyActionArea)
    {
        verScroll->setValue(pY * (drawArea->height()));
        horScroll->setValue(pX * (drawArea->width()));

        //drawArea->setPosCamera(pX, pY);
    }
}

void ScrollMapWidget::checkShowNewActionArea()
{
    if (readyActionArea)
    {
        if (!verScroll->isVisible() &&
            !horScroll->isVisible()) return;

        //
        int CurY = verScroll->value();
        int CurX = horScroll->value();

        bool isMoveArea = false;
        int dXmove = 0;
        int dYmove = 0;

        lastCurX = CurX;
        lastCurY = CurY;

        int dPix = 36;

        if (CurX == horScroll->maximum() && horScroll->isVisible())
        {
            dXmove = (drawArea->width() - this->width()  + dPix) / drawArea->getValZoom();
            lastCurX = 0;
            isMoveArea = true;
        }
        if (CurY == verScroll->maximum() && verScroll->isVisible())
        {
            dYmove  = (drawArea->height() - this->height() + dPix) / drawArea->getValZoom();
            lastCurY = 0;
            isMoveArea = true;
        }

        if (CurX == 0 && horScroll->isVisible())
        {
            dXmove = (drawArea->width() - this->width()  + dPix) / drawArea->getValZoom();
            dXmove *= -1;
            lastCurX = horScroll->maximum();
            isMoveArea = true;
        }
        if (CurY == 0 && verScroll->isVisible())
        {
            dYmove  = (drawArea->height() - this->height() + dPix) / drawArea->getValZoom();
            dYmove *= -1;
            lastCurY = verScroll->maximum();
            isMoveArea = true;
        }

        if (isMoveArea)
        {
            readyActionArea = false;
            loadingWidget->Show();

            moveActionArea(dXmove, dYmove);
            return;
        }
    }
}

void ScrollMapWidget::updatePosMiniMap()
{
    if (horizontalScrollBar()->isVisible() ||
        verticalScrollBar()->isVisible())
    {
        int dX = 3;
        int dY = 3;

        if (verScroll->isVisible()) dX = 23;
        if (horScroll->isVisible()) dY = 23;

        miniMap->setDistEdge(dX, dY);
        miniMap->updatePos();

        miniMap->Show();
    }
    else
    {
        miniMap->Hide();
    }
}

void ScrollMapWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    // Чтоб QScrollBar не загараживал
    updatePosMiniMap();

    resized();
}
