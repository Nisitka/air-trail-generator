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

    toolBar = new QToolBar(tr("&Файл"));
    addToolBar(Qt::TopToolBarArea,toolBar);

    toolButton_1 = new QPushButton(tr("Кнопка 1"));
    toolButton_2 = new QPushButton(tr("Кнопка 2"));
    toolButton_3 = new QPushButton(tr("Кнопка 3"));

    toolButton_1->setIcon(QPixmap(":/resurs/a"));
    toolButton_2->setIcon(QPixmap(":/resurs/b"));
    toolButton_3->setIcon(QPixmap(":/resurs/base1"));

    toolBar->setAllowedAreas(Qt::TopToolBarArea);
    toolBar->setMovable(false);
    toolBar->addWidget(toolButton_1);
    toolBar->addWidget(toolButton_2);
    toolBar->addWidget(toolButton_3);

    connect(toolButton_1, SIGNAL(clicked(bool)),
            SLOT(clickProcessing())
            );
    connect(toolButton_2, SIGNAL(clicked(bool)),
            SLOT(clickProcessing())
            );
    connect(toolButton_3, SIGNAL(clicked(bool)),
            SLOT(clickProcessing())
            );
    connect(this, SIGNAL(openToolWidget(QWidget*,QPixmap,QString,Qt::DockWidgetAreas, Qt::DockWidgetArea)),
            SLOT(workTools(QWidget*, QPixmap, QString, Qt::DockWidgetAreas, Qt::DockWidgetArea))
            );


    ui->mainLayout->addWidget(visMap);
    visMap->show();
}

mapOpenGLWidget* map3DVisWindow::getGraphicsWidget()
{
    return visMap;
}

void map3DVisWindow::clickProcessing()
{
    if(sender() == toolButton_1)
    {
        openToolWidget(toolButton_1, toolButton_1->icon().name(), toolButton_1->text(),Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    }
    if(sender() == toolButton_2)
    {
        openToolWidget(toolButton_2, toolButton_2->icon().name(), toolButton_2->text(),Qt::RightDockWidgetArea,Qt::RightDockWidgetArea);
    }
    if(sender() == toolButton_3)
    {
        openToolWidget(toolButton_3, toolButton_3->icon().name(), toolButton_3->text(),Qt::LeftDockWidgetArea,Qt::LeftDockWidgetArea);
    }
}

void map3DVisWindow::workTools(QWidget *widget, QPixmap pix, QString str, Qt::DockWidgetAreas allowedDockArea, Qt::DockWidgetArea initDockArea)
{

    QList<QDockWidget *> dockWidgets = findChildren<QDockWidget *>();
    if(dockWidgets.size() != 0){

        for (int var = 0; var < dockWidgets.size(); var++){

            if(dockWidgets[var]->objectName() == str){

                if(dockWidgets[var]->isVisible() == true)
                {
                    dockWidgets[var]->hide();
                    return;
                }else if(dockWidgets[var]->isVisible() == false)
                {
                    dockWidgets[var]->show();
                    return;
                }
            }
        }
    }

    dockWidget = new QDockWidget(str);
    dockWidget->setObjectName(str);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    dockWidget->setAllowedAreas(allowedDockArea);
    addDockWidget(initDockArea,dockWidget);



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
