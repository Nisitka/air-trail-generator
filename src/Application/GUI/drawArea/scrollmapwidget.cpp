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

    // Чтоб QScrollBar не загараживал
    connect(this, SIGNAL(resized()),
            this, SLOT(updatePosCoordLabel()));

    readyActionArea = true;

    //
    verScroll = verticalScrollBar();
    horScroll = horizontalScrollBar();

    // Гифка загрузки новой области
    loadingWidget = new processTmpWidget(this);
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
        verScroll->setValue(lastCurY + (dY * drawArea->height()));

        lastCurX = horScroll->value();
        horScroll->setValue(lastCurX + (dX * drawArea->width()));
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

void ScrollMapWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    resized();
}
