#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

#include "drawArea/mapareamainwindow.h"
//#include "backend/map.h"
#include "multiplewindow.h"

namespace Ui {
class visualInfoWidget;
}

class visualInfoWidget : public MultipleWindow
{
    Q_OBJECT
signals:  

    //
    void setRectPredict(int idXo, int idYo); // дискрета левого верхнего угла

    //
    void setPointsTrail(QPoint begin, QPoint last);

public slots:

    //
    void updateImage();

public:
    explicit visualInfoWidget(QImage* geoMap,
                              Map* map);

    mapAreaMainWindow* getManDrawArea();

    ~visualInfoWidget();

private slots:

    //
    void switchVisual(int idType);

private:
    //
    mapAreaMainWindow* manDrawArea;

    Ui::visualInfoWidget *ui;
};

#endif // VISUALINFOWIDGET_H
