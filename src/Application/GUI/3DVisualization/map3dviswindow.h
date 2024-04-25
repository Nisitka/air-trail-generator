#ifndef MAP3DVISWINDOW_H
#define MAP3DVISWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector3D>
#include <QDockWidget>

#include "backend/map.h"
#include "mapopenglwidget.h"

#include <QToolButton>

namespace Ui {
class map3DVisWindow;
}

class map3DVisWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void generateMap3D();
    void openToolWidget(QWidget*,QPixmap,QString,Qt::DockWidgetAreas, Qt::DockWidgetArea);

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

    void addFunWindow(QWidget* window, const QIcon& iconButton, const QString& nameWin = nullptr,
                   Qt::DockWidgetAreas typeMoved = Qt::LeftDockWidgetArea,
                   Qt::DockWidgetArea initShow = Qt::LeftDockWidgetArea);

    //void addGroupFunWindow(const QList <QDockWidget*>);

    void showFunWindow();

    void clickProcessing();
    void workTools(QWidget*, QPixmap, QString, Qt::DockWidgetAreas, Qt::DockWidgetArea);

private:
    void setMap(int idXo, int idYo, int numW, int numL);

    void setAreaZD(int idXo, int idYo, int numW, int numL);

    const int maxValueSliders = 1000;

    //
    Map* map;
    mapOpenGLWidget* visMap;
    QToolBar *toolBar;
    QPushButton *toolButton_1, *toolButton_2, *toolButton_3;
    QDockWidget *dockWidget;

    QMap <QToolButton*, QDockWidget*> windows;

    Ui::map3DVisWindow *ui;
};

#endif // MAP3DVISWINDOW_H
