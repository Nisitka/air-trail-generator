#ifndef SCROLLMAPWIDGET_H
#define SCROLLMAPWIDGET_H

#include <QScrollArea>
#include <QSlider>
#include <QWidget>

#include "areadrawwidget.h"
#include "GUI/processtmpwidget.h"
#include "./DecktopItems/minimapwidget.h"

#include "./DecktopItems/scrolldirector.h"

#include <QPushButton>

class ScrollMapWidget: public QScrollArea, public ScrollDirector
{
    Q_OBJECT

signals:

    //
    void moveActionArea(int dX, int dY);

    //
    void movedLookArea(double dX, double dY);

    //
    void resized();

public slots:

    // Обновляем значения координат
    void updateCoord(const QString& coordsData);

    //
    void movePosLookMap(double dX, double dY); // в долях от макс.
    void setPosLookMap(double pX, double pY);

    // Проверить, надо ли изменить активную область
    void checkShowNewActionArea();

    //
    void setMoveMapEnabled(bool val = true);

public:
    //
    ScrollMapWidget(areaDrawWidget* drawArea);

    //
    void ItemChanged(ScrollItem* item) override final;

protected:

    //
    void resizeEvent(QResizeEvent* event) override final;

    //
    void CreateItems() override final;

private slots:

    //


    //
    void updatePosCoordLabel();

    //
    void updateMiniMap();

private:

    // Последние значения передвижения карты
    int lastCurY;
    int lastCurX;

    // Ползунки
    QScrollBar* verScroll;
    QScrollBar* horScroll;

    //
    bool readyActionArea;

    //
    areaDrawWidget* drawArea;

    //
    QSlider* zoomSlider;

    //
    QLabel* coordLabel;

    //
    miniMapWidget* miniMap;
    void updatePosMiniMap();

    QWidget* backWidget;

    //
    processTmpWidget* loadingWidget;

};

#endif // SCROLLMAPWIDGET_H
