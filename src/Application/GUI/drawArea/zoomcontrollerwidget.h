#ifndef ZOOMCONTROLLERWIDGET_H
#define ZOOMCONTROLLERWIDGET_H

#include <QWidget>

namespace Ui {
class ZoomControllerWidget;
}

class ZoomControllerWidget : public QWidget
{
    Q_OBJECT

signals:

    //
    void zoomChanged(double val); // В долях

public slots:

    //
    void setZoomVal(int p); // в процентах

public:
    explicit ZoomControllerWidget(QWidget *parent = 0);
    ~ZoomControllerWidget();

    //
    void setValSlider(int p); //

    void setRangeValues(int minPer = 5, int maxPer = 1000); // в процентах

private slots:

    //
    void addZoom();
    void reduceZoom();

private:

    //
    void setDesine();

    const int dZoom = 15;

    //
    int curValue;
    int minVal;
    int maxVal;

    Ui::ZoomControllerWidget *ui;
};

#endif // ZOOMCONTROLLERWIDGET_H
