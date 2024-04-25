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

}

void ScrollMapWidget::movePosLookMap(double dX, double dY)
{
    int curY = verticalScrollBar()->value();
    verticalScrollBar()->setValue(curY + (dY * drawArea->height()));

    int curX = horizontalScrollBar()->value();
    horizontalScrollBar()->setValue(curX + (dX * drawArea->width()));
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
