#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QVector2D>

class plotWidget: public QWidget
{

public slots:
    //
    void setData(QVector<float> X, QVector<float> Y);

public:
    plotWidget();

    void clear();

protected:

    //
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void pVal(float& Xmin, float& Xmax,
              float& Ymin, float& Ymax);

    bool isData = {false};

    float Xmin, Xmax, Ymin, Ymax;
    float dW, dH;

    //
    int dPartX = 80;
    int dPartY = 50;

    // Отступ зоны отрисовки графика
    int pixMarginL = 50;
    int pixMargin  = 15;
    int pixMarginU = 20;

    //
    QPointF* points;
    int countPoint;

    //
    QPointF* drawPoints;
};

#endif // PLOTWIDGET_H
