#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QImage>


//#include "backend/gis/geogenerator.h"
//#include "backend/gis/paintermapimage.h"
#include "backend/GIS/gis.h"

#include "mainwindow.h"

#include "visualinfowidget.h"
#include "optmapgeneratorwindow.h"
#include "optrlswindow.h"
#include "backend/Trail/buildertraildrones.h"
#include "optdronewindow.h"
#include "backend/RLS/managerrls.h"
#include "3DVisualization/map3dviswindow.h"
#include "GUI/algorithmPredict/setalgpredictwindow.h"

// Интерфейс всей программы
class GUI
{
public:
    GUI(GISInformer* gisInformer); // установить карту

    //
    void connectGIS(GIS* gis);

    // присоединить к интерфейсу РЛС
    void connectMRLS(managerRLS*);

    //
    void connectBuilderTrail(builderTrailDrones*);


    void showMainWin();

private:

    // Получаем необходимые данные об карте через него
    GISInformer* gisInformer;

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

    // Окно для 3D отображения рельефа
    map3DVisWindow* map3DWin;

    //
    setAlgPredictWindow* algPredWin;

    // Инструменты
    ToolPredTrail* toolPTrail;
    ToolPredRect*  toolPLine;
    ToolSetRLS*    toolRLS;
    ToolEditMap*   toolEditTer;
    ToolVisMap*    toolVisMap;

};

#endif // GUI_H
