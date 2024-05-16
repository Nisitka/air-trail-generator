#ifndef MINIMAPWIDGET_H
#define MINIMAPWIDGET_H

#include <QLabel>

#include <QMouseEvent>

class miniMapWidget: private QLabel
{
    Q_OBJECT

signals:

public slots:

    //
    void setPosLookArea(int idX, int idY);
    void setSizeLookArea(int W, int H);

public:
    explicit miniMapWidget(QWidget* parent,
                           int H = 300, int W = 400);

    //
    void setSizeActionArea(const QSize& sizeMap);

    //
    void setMaxSize(int W, int H);

protected:

    //
    void paintEvent(QPaintEvent* event) override final;

    //
    void mousePressEvent(QMouseEvent* mouse) override final;

    //
    void mouseMoveEvent(QMouseEvent* mouse) override final;

    //
    void mouseReleaseEvent(QMouseEvent* mouse) override final;

private:

    //
    enum statusMouse{press, release};
    statusMouse statMouse;

    //
    QPoint posMouse;

    //
    QPoint posCursor;

    //
    QPoint pointPress;

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
