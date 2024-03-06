#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QImage>


#include "backend/geogenerator.h"

#include "mainwindow.h"

#include "visualinfowidget.h"
#include "optmapgeneratorwindow.h"
#include "optrlswindow.h"
#include "paintermapimage.h"
#include "backend/buildertraildrones.h"
#include "neuronnetworkwindow.h"
#include "optdronewindow.h"
#include "backend/managerdrones.h"
#include "backend/managerrls.h"
#include "map3dwindow.h"

class GUI
{
public:
    GUI(QImage* geoMap,
        Map* map); // установить карту

    // присоеденить к интерфейсу генератор рельефа
    void connectMapGenerator(geoGenerator*);

    // присоеденить отрисовщика карты к GUI
    void connectMapPainter(painterMapImage*);

    // присоединить к интерфейсу РЛС
    void connectMRLS(managerRLS*);

    //
    void connectBuilderTrail(builderTrailDrones*);

    //
    void connectMDrones(managerDrones*);

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
    optRLSwindow* optRLSWin;

    //
    optDroneWindow* droneWin;

    // окно для 3D отображения рельефа
    map3DWindow* map3DWin;
};

#endif // GUI_H
