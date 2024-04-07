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
#include "optdronewindow.h"
#include "backend/managerdrones.h"
#include "backend/managerrls.h"
#include "3DVisualization/map3dviswindow.h"
#include "dataaccessobjectwindow.h"
#include "backend/dao.h"
#include "GUI/algorithmPredict/setalgpredictwindow.h"


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

    //
    void connectDataBase(DAO* database);

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
    map3DVisWindow* map3DWin;

    // окно для работы с БД
    DataAccessObjectWindow* daoWin;

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
