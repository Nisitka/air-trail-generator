#ifndef SCROLLMAPWIDGET_H
#define SCROLLMAPWIDGET_H

#include <QScrollArea>
#include <QSlider>
#include <QWidget>

#include "areadrawwidget.h"

class ScrollMapWidget: public QScrollArea
{
    Q_OBJECT
signals:

    //
    void resized();

public slots:

    // Обновляем значения координат
    void updateCoord(const QString& coordsData);

    //
    void movePosLookMap(double dX, double dY);

public:
    ScrollMapWidget(areaDrawWidget* drawArea);

protected:

    //
    void resizeEvent(QResizeEvent* event) override final;

private slots:

    //
    void updatePosCoordLabel();

private:

    //
    areaDrawWidget* drawArea;

    //
    QSlider* zoomSlider;

    //
    QLabel* coordLabel;


    QWidget* backWidget;

};

#endif // SCROLLMAPWIDGET_H
