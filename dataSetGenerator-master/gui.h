#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QImage>

#include "geogenerator.h"
#include "calcqfunction.h"

#include "mainwindow.h"

#include "visualinfowidget.h"
#include "optmapgeneratorwindow.h"
#include "optqfunwindow.h"
#include "optrlswindow.h"
#include "paintermapimage.h"
#include "optdatanetwindow.h"
#include "painterdatanetimage.h"
#include "optbuilddatasetwindow.h"
#include "builderdataset.h"
#include "buildertraildrones.h"
#include "neuronnetworkwindow.h"
#include "optdronewindow.h"
#include "drone.h"
#include "trainernetwork.h"
#include "managerrls.h"
#include "map3dwindow.h"

class GUI
{
public:
    GUI(QImage* geoMap,
        QImage* dataNet,
        QImage* QFun,
        Map* map); // установить карту

    // присоеденить к интерфейсу генератор рельефа
    void connectMapGenerator(geoGenerator*);

    // присоеденить отрисовщика карты к GUI
    void connectMapPainter(painterMapImage*);

    // присоеденить к интерфейсу калькулятор Q функции
    void connectCalcQFun(calcQFunction*);

    // присоединить к интерфейсу РЛС
    void connectMRLS(managerRLS*);

    //
    void connectPainterDataNet(painterDataNetImage*);

    //
    void connectBuilderDS(builderDataSet*);

    //
    void connectBuilderTrail(builderTrailDrones*);

    //
    void connectDrone(Drone*);

    //
    void connectTrainerNet(trainerNetwork*);

    void showMainWin();

private:
    //
    Map* map;

    // основное окно приложения
    mainWindow* mainWin;
    //
    visualInfoWidget* visInfoWin;
    //
    optMapGeneratorWindow* optGenMapWin;
    //
    optQFunWindow* optQFunWin;
    //
    optRLSwindow* optRLSWin;
    //
    optDataNetWindow* optDNWin;
    //
    optBuildDataSetWindow* optBuildDSWin;
    //
    neuronNetworkWindow* netWin;
    //
    optDroneWindow* droneWin;
    // окно для 3D отображения рельефа
    map3DWindow* map3DWin;
};

#endif // GUI_H
