#include "map3dviswindow.h"
#include "ui_map3dviswindow.h"

#include "GUI/designer.h"

#include <QDebug>

map3DVisWindow::map3DVisWindow(Map* map_, QImage* imgTex):
    ui(new Ui::map3DVisWindow)
{
    map = map_;

    ui->setupUi(this);

    //
    visMap = new mapOpenGLWidget(map, imgTex);

    addFunWindow(new QTabWidget, QIcon(":/resurs/a"),"A",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    // 3D
    setCentralWidget(visMap);
    visMap->show();
}

mapOpenGLWidget* map3DVisWindow::getGraphicsWidget()
{
    return visMap;
}

void map3DVisWindow::updateMap3D(int idXo, int idYo, int size)
{
    visMap->updateTerrain(idXo, idYo, size);
}

void map3DVisWindow::updateMap3D()
{
    visMap->updateTerrain();
}

void map3DVisWindow::updatePointsInterZD(QVector<QVector<QVector<QVector3D> > >* points,
                                      QList <QVector3D>* posRLS)
{
    visMap->updatePosRLS(posRLS);
    visMap->updateZD(points);
}

void map3DVisWindow::finishBuildMap(int idXo, int idYo, int numW, int numL)
{
    setMap(idXo, idYo, numW, numL);
}

void map3DVisWindow::setMap(int idXo, int idYo, int numW, int numL)
{
    setAreaZD(idXo, idYo, numW, numL);
}

void map3DVisWindow::setAreaZD(int idXo, int idYo, int numW, int numL)
{
    visMap->initializeTerrain(idXo, idYo, numW, numL);
}

map3DVisWindow::~map3DVisWindow()
{
    delete ui;
}
