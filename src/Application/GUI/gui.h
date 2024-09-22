#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QImage>


#include "backend/GIS/gis.h"

#include "gui/mainswitcherwindow.h"

#include "mainwindow.h"
#include "hellowindow.h"

#include "visualinfowidget.h"
#include "manrlswindow.h"
#include "backend/Trail/buildertraildrones.h"
#include "backend/RLS/managerrls.h"
#include "3DVisualization/map3dviswindow.h"
#include "GUI/algorithmPredict/setalgpredictwindow.h"

#include "GUI/createprojectwindow.h"

// Интерфейс всей программы
class GUI: public QObject
{
    Q_OBJECT

signals:

    //
    void openProject(const QString& dirName);

public:
    GUI(GISInformer* gisInformer,
        InformerRLS* infoRLS);

    //
    createProjectWindow* WindowCreateProject() const;

    //
    void connectGIS(GIS* gis);

    // присоединить к интерфейсу РЛС
    void connectMRLS(managerRLS*);

    //
    void connectBuilderTrail(builderTrailDrones*);


    void showMainWin();

private slots:

    //
    void showOpenProjectWindow();

private:

    // Окно инициализации проекта
    createProjectWindow* createProjWin;

    // Самое главное окно
    mainSwitcherWindow* switcherWindow;

    // Окно приветсвия
    helloWindow* helloWin;

    // Основное окно приложения
    mainWindow* mainWin;

    // Получаем необходимые данные об карте через него
    GISInformer* gisInformer;

    //
    visualInfoWidget* visInfoWin;

    //
    manRLSWindow* optRLSWin;

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
