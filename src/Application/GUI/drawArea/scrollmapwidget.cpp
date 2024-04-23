#include "scrollmapwidget.h"

#include <QBoxLayout>
#include <QPainter>

ScrollMapWidget::ScrollMapWidget(areaDrawWidget* drawArea)
{
    w = new QWidget;
    QHBoxLayout* horLayout = new QHBoxLayout(w);

    this->setWidget(w);
    this->setWidgetResizable(true);

    horLayout->addWidget(drawArea);

    w->setStyleSheet("QWidget{"
                     "   background-color:transparent;"
                     "};)");

    this->setStyleSheet("QScrollArea{"
                        "   background-color:transparent;"
                        "};)");
}

void ScrollMapWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    resized();
}
