#ifndef MINIMAPWIDGET_H
#define MINIMAPWIDGET_H

#include <QLabel>

#include <QMouseEvent>

class miniMapWidget: public QLabel
{
    Q_OBJECT

signals:

    //
    void movedLookArea(double dX, double dY);

public slots:

    //
    void setPosLookArea(int idX, int idY);
    void setSizeLookArea(int W, int H);

public:
    enum Alignment{topLeft, topRight, bottomLeft, bottomRight};

    explicit miniMapWidget(QWidget* parent,
                           int W = 400, int H= 300,
                           Alignment pos = miniMapWidget::bottomRight);

    //
    void setSizeActionArea(const QSize& sizeMap);

    //
    void setMaxSize(int W, int H);

    //
    void updatePos();
    void setDistEdge(int dXpx, int dYpx);

    //
    void Show();
    void Hide();

protected:

    //
    void paintEvent(QPaintEvent* event) override final;

    //
    void mousePressEvent(QMouseEvent* mouse) override final;

    //
    void mouseMoveEvent(QMouseEvent* mouse) override final;

    //
    void mouseReleaseEvent(QMouseEvent* mouse) override final;

private slots:



private:

    //
    QPoint dAlign;

    //
    Alignment typePos;

    //
    QWidget* Parent;

    //
    enum statusMouse{press, release};
    statusMouse statMouse;

    //
    QPoint posMouse;

    //
    QPoint posCursor;

    //
    QPoint pointPressArea;

    //
    QSize sizeActionArea;

    //
    QRect* lookArea;

    //
    bool inLookRect;

    //
    int maxW;
    int maxH;
    double kSize;


};

#endif // MINIMAPWIDGET_H
