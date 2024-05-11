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
#include "backend/buildertraildrones.h"
#include "optdronewindow.h"
#include "backend/managerdrones.h"
#include "backend/managerrls.h"
#include "3DVisualization/map3dviswindow.h"
#include "dataaccessobjectwindow.h"
#include "backend/dao.h"
#include "GUI/algorithmPredict/setalgpredictwindow.h"
#include "backend/airobject.h"
#include "airobjectfunwindow.h"
#include "airwindow.h"
#include "airinfowindow.h"

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

    //
    void connectMDrones(managerDrones*);

    //
    void connectDataBase(DAO* database);

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

    // окно для 3D отображения рельефа
    map3DVisWindow* map3DWin;

    // окно для работы с БД
    DataAccessObjectWindow* daoWin;

    //
    setAlgPredictWindow* algPredWin;

    //ТТХ возудшных объектов
    AirObjectFunWindow* airObjWin;
    AirWindow *AirWin;
    AirInfoWindow *AirInfo;

    // Инструменты
    ToolPredTrail* toolPTrail;
    ToolPredRect*  toolPLine;
    ToolSetRLS*    toolRLS;
    ToolEditMap*   toolEditTer;
    ToolVisMap*    toolVisMap;

};

#endif // GUI_H
