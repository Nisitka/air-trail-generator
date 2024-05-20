#include "scrollmapwidget.h"

#include <QBoxLayout>
#include <QScrollBar>

ScrollMapWidget::ScrollMapWidget(areaDrawWidget* drawArea_):
    drawArea(drawArea_)
{
    backWidget = new QWidget;
    QHBoxLayout* horLayout = new QHBoxLayout(backWidget);

    this->setWidget(backWidget);
    this->setWidgetResizable(true);

    horLayout->addWidget(drawArea);

    backWidget->setStyleSheet("QWidget{"
                     "   background-color:transparent;"
                     "};)");

    this->setStyleSheet("QScrollArea{"
                        "   background-color:transparent;"
                        "};)");

    // Слайдер для изменения масштаба
    zoomSlider = new QSlider(Qt::Vertical, this);
    zoomSlider->move(7, 7);
    zoomSlider->setStyleSheet("QSlider{"
                              "   background-color:transparent;"
                              "   border: 1px solid rgb(55,55,55,0);"
                              "};)");

    //
    coordLabel = new QLabel(this);
    coordLabel->setFixedSize(135, 20);
    coordLabel->setStyleSheet("QLabel{"
                              "   background-color: rgb(255,255,255,140);"
                              "   border: 1px solid rgb(55,55,55);"
                              "   border-radius: 2px;"
                              "};)");

    //
    miniMap = new miniMapWidget(this, 150, 120);
    miniMap->setDistEdge(20, 20);
    miniMap->setSizeActionArea(drawArea->size());

    connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
            this,                SLOT(updateMiniMap()));
    connect(horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
            this,                  SLOT(updateMiniMap()));

    //
    connect(miniMap, SIGNAL(movedLookArea(double,double)),
            this,    SLOT(setPosLookMap(double,double)));

    readyActionArea = true;

    //
    verScroll = verticalScrollBar();
    horScroll = horizontalScrollBar();

    // Гифка загрузки новой области
    loadingWidget = new processTmpWidget(this);
}

void ScrollMapWidget::updateMiniMap()
{
    double pW = (double)this->width()  / drawArea->width();
    double pH = (double)this->height() / drawArea->height();

    miniMap->setSizeActionArea(drawArea->size());
    miniMap->setPaternSizeLookArea(pW,pH);
}

void ScrollMapWidget::setMoveMapEnabled(bool val)
{
    //
    verticalScrollBar()->setValue(lastCurY);
    horizontalScrollBar()->setValue(lastCurX);

    readyActionArea = val;
    loadingWidget->Hide();

    //drawArea->setDrawEnabled();
    drawArea->repaint();
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
    }
}

void ScrollMapWidget::setPosLookMap(double pX, double pY)
{
    if (readyActionArea)
    {
        verScroll->setValue(pY * (drawArea->height()));
        horScroll->setValue(pX * (drawArea->width()));
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

            //drawArea->setDrawEnabled(false);
            loadingWidget->Show();

            //qDebug() << dXmove << dYmove;

            moveActionArea(dXmove, dYmove);
            return;
        }
    }
}

void ScrollMapWidget::updatePosCoordLabel()
{
    if (horizontalScrollBar()->isVisible())
    {
        coordLabel->move(5, this->size().height() - 45);
    }
    else
    {
        coordLabel->move(5, this->size().height() - 25);
    }
}

void ScrollMapWidget::updateCoord(const QString &coordsData)
{
    coordLabel->setText(coordsData);
}

void ScrollMapWidget::updatePosMiniMap()
{
    if (horizontalScrollBar()->isVisible() ||
        verticalScrollBar()->isVisible())
    {
        int dX = 3;
        int dY = 3;

        if (horScroll->isVisible()) dY = 23;
        if (verScroll->isVisible())   dX = 23;

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
    updatePosCoordLabel();
    updatePosMiniMap();

    resized();
}
