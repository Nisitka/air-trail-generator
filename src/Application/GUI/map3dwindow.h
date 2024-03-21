#ifndef MAP3DWINDOW_H
#define MAP3DWINDOW_H

#include <QWidget>
#include <QVector3D>


#include "visualmap3d.h"
#include "backend/map.h"
#include "mapopenglwidget.h"

namespace Ui {
class map3DWindow;
}

class map3DWindow : public QWidget
{
    Q_OBJECT
signals:
    void generateMap3D();

public slots:
    // завершение подготовки данных для отображения 3D карты
    void finishBuildMap(int idXo, int idYo, int numW, int numL);

    // Обновить данные по рельеф и отрндерить по новой
    void updateMap3D(int idXo, int idYo, int size); // в каком квадрате
    void updateMap3D(); // обновить все

    //
    void updatePointsInterZD(QVector <QVector <QVector <QVector3D>>>* pZD, QList <QVector3D>* posRLS);

public:
    explicit map3DWindow(Map* map_, QWidget *parent = 0);
    ~map3DWindow();

    mapOpenGLWidget* getGraphicsWidget();

private slots:

    // для слайдеров
    void moveFrameOX(int pos);
    void moveFrameOY(int pos);
    void moveFrameXY(int pos);

    // для спинбоксов
    void clickFrameOX(double part);
    void clickFrameOY(double part);
    void clickFrameXY(double part);


private:
    void setMap(int idXo, int idYo, int numW, int numL);

    void setAreaZD(int idXo, int idYo, int numW, int numL);

    const int maxValueSliders = 1000;

    Map* map;

    Ui::map3DWindow *ui;

    mapOpenGLWidget* visMap;
};

#endif // MAP3DWINDOW_H
