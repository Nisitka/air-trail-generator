#include "map3dviswindow.h"
#include "ui_map3dviswindow.h"

#include "GUI/designer.h"

#include <QDebug>

map3DVisWindow::map3DVisWindow(GISInformer* mapInformer):
    ui(new Ui::map3DVisWindow)
{
    ui->setupUi(this);

    //
    visMap = new mapOpenGLWidget(mapInformer);

    // Функциональные окна
    addFunWindow(new QTabWidget, QIcon(":/resurs/a"),"A",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    //
    //loadingLabel = new processTmpWidget(this);

    // 3D
    setCentralWidget(visMap);
    visMap->show();
}

mapOpenGLWidget* map3DVisWindow::getGraphicsWidget()
{
    return visMap;
}

void map3DVisWindow::updateMap3D(int idXo, int idYo, int W, int L)
{
    //visMap->updateTerrain(idXo, idYo, W, L);
}

void map3DVisWindow::updateMap3D()
{
    //visMap->updateTerrain();
}

void map3DVisWindow::updatePointsInterZD(QVector<QVector<QVector<QVector3D> > >* points,
                                      QList <QVector3D>* posRLS)
{
    //visMap->updatePosRLS(posRLS);
    //visMap->updateZD(points);
}

/// ************************************
void map3DVisWindow::setVisRectDef()
{
    visMap->initializeTerrain(0, 0,
                              300,
                              300);
}

void map3DVisWindow::setVisRect(int idXo, int idYo, int W, int L)
{
    //loadingLabel->Show();
    //visMap->initializeTerrain(idXo, idYo, W, L);
    //loadingLabel->Hide();
}

map3DVisWindow::~map3DVisWindow()
{
    delete ui;
}
