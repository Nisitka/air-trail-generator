#ifndef MAP3DVISWINDOW_H
#define MAP3DVISWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector3D>
#include <QDockWidget>

#include "backend/map.h"
#include "mapopenglwidget.h"

#include <QToolButton>
#include "GUI/designer.h"

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
    explicit map3DVisWindow(Map* map_, QImage* imgTex, QWidget *parent = nullptr);
    ~map3DVisWindow();

    mapOpenGLWidget* getGraphicsWidget();

    enum StyleButtonTool {on, off};

private slots:

    void addFunWindow(QWidget* window, const QIcon& iconButton, const QString& nameWin = nullptr,
                   Qt::DockWidgetAreas typeMoved = Qt::LeftDockWidgetArea,
                   Qt::DockWidgetArea initShow = Qt::LeftDockWidgetArea);

    //void addGroupFunWindow(const QList <QDockWidget*>);

    void showFunWindow();

private:
    void setMap(int idXo, int idYo, int numW, int numL);

    void setAreaZD(int idXo, int idYo, int numW, int numL);

    const int maxValueSliders = 1000;

    //
    Map* map;
    mapOpenGLWidget* visMap;
    QToolBar *toolBar;
    QDockWidget *dockWidget;

    QMap <QToolButton*, QDockWidget*> windows;

    Ui::map3DVisWindow *ui;
};

#endif // MAP3DVISWINDOW_H
