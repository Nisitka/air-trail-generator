#include "map3dviswindow.h"
#include "ui_map3dviswindow.h"

#include "GUI/designer.h"

#include <QDebug>

map3DVisWindow::map3DVisWindow(Map* map_, QImage* imgTex, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::map3DVisWindow)
{
    map = map_;

    ui->setupUi(this);

    visMap = new mapOpenGLWidget(map,
                                 imgTex);

    Designer::setGroupBox(ui->mainGroupBox);

    toolBar = new QToolBar();
    addToolBar(Qt::TopToolBarArea,toolBar);
    toolBar->setMovable(false);

    addFunWindow(new QTabWidget, QIcon(":/resurs/a"),"A",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    addFunWindow(new QTabWidget, QIcon(":/resurs/b"),"B",Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);

    // 3D
    ui->mainLayout->addWidget(visMap);
    visMap->show();
}

mapOpenGLWidget* map3DVisWindow::getGraphicsWidget()
{
    return visMap;
}

void map3DVisWindow::addFunWindow(QWidget *window, const QIcon &iconButton, const QString &nameWin,
                                  Qt::DockWidgetAreas typeMoved, Qt::DockWidgetArea initShow)
{
    //
    QToolButton* button = new QToolButton;
    button->setIcon(iconButton);
    button->setToolTip(nameWin);
    //setButtonStyle(button, on);

    toolBar->addWidget(button);

    //
    QDockWidget* dock = new QDockWidget(nameWin);
    this->addDockWidget(initShow, dock);
    dock->setWidget(window);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(typeMoved);
    dock->hide();

    //
    connect(button, SIGNAL(clicked(bool)),
            this,   SLOT(showFunWindow()));

    windows[button] = dock;
}

void map3DVisWindow::showFunWindow()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());

    QDockWidget* dock = windows[button];
    if (dock->isVisible())
    {
        dock->hide();
    }
    else
    {
        dock->show();
    }
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
