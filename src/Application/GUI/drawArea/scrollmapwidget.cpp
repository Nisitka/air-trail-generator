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

    loadingWidget = new processTmpWidget(this);
}

void ScrollMapWidget::setMoveMapEnabled(bool val)
{
    readyActionArea = val;
    loadingWidget->Hide();
}

void ScrollMapWidget::movePosLookMap(double dX, double dY)
{
    if (readyActionArea)
    {
        lastCurY = verticalScrollBar()->value();
        verticalScrollBar()->setValue(lastCurY + (dY * drawArea->height()));

        lastCurX = horizontalScrollBar()->value();
        horizontalScrollBar()->setValue(lastCurX + (dX * drawArea->width()));
    }
}

void ScrollMapWidget::checkShowNewActionArea()
{
    if (readyActionArea)
    {
        //
        int CurY = verticalScrollBar()->value();
        int CurX = horizontalScrollBar()->value();

        bool isMoveArea = false;
        int dXmove = 0;
        int dYmove = 0;

        lastCurX = CurX;
        lastCurY = CurY;

        if (CurX == horizontalScrollBar()->maximum())
        {
            dXmove = (drawArea->width() - this->width()  + 40) / drawArea->getValZoom();
            lastCurX = 0;
            isMoveArea = true;
        }
        if (CurY == verticalScrollBar()->maximum())
        {
            dYmove  = (drawArea->height() - this->height() + 40) / drawArea->getValZoom();
            lastCurY = 0;
            isMoveArea = true;
        }

        if (CurX == 0)
        {
            dXmove = (drawArea->width() - this->width()  + 40) / drawArea->getValZoom();
            dXmove *= -1;
            lastCurX = horizontalScrollBar()->maximum();
            isMoveArea = true;
        }
        if (CurY == 0)
        {
            dYmove  = (drawArea->height() - this->height() + 40) / drawArea->getValZoom();
            dYmove *= -1;
            lastCurY = verticalScrollBar()->maximum();
            isMoveArea = true;
        }

        if (isMoveArea)
        {
            readyActionArea = false;
            verticalScrollBar()->setValue(lastCurY);
            horizontalScrollBar()->setValue(lastCurX);

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
