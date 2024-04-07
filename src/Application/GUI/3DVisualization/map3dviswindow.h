#ifndef MAP3DVISWINDOW_H
#define MAP3DVISWINDOW_H

#include <QMainWindow>
#include <QVector3D>

#include "backend/map.h"
#include "mapopenglwidget.h"

namespace Ui {
class map3DVisWindow;
}

class map3DVisWindow : public QMainWindow
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
    explicit map3DVisWindow(Map* map_, QImage* imgTex, QWidget *parent = 0);
    ~map3DVisWindow();

    mapOpenGLWidget* getGraphicsWidget();

private slots:


private:
    void setMap(int idXo, int idYo, int numW, int numL);

    void setAreaZD(int idXo, int idYo, int numW, int numL);

    const int maxValueSliders = 1000;

    //
    Map* map;
    mapOpenGLWidget* visMap;

    Ui::map3DVisWindow *ui;
};

#endif // MAP3DVISWINDOW_H
