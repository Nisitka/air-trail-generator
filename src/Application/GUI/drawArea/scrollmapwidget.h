#ifndef SCROLLMAPWIDGET_H
#define SCROLLMAPWIDGET_H

#include <QScrollArea>
#include <QWidget>

#include "areadrawwidget.h"

class ScrollMapWidget: public QScrollArea
{
    Q_OBJECT
signals:

    //
    void resized();

public:
    ScrollMapWidget(areaDrawWidget* drawArea);

protected:

    //
    void resizeEvent(QResizeEvent* event) override;

private:

    QWidget* w;

};

#endif // SCROLLMAPWIDGET_H
