#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QImage>

#include "geogenerator.h"
#include "calcqfunction.h"
#include "rls.h"

#include "mainwindow.h"

#include "visualinfowidget.h"
#include "optmapgeneratorwindow.h"
#include "optqfunwindow.h"
#include "optrlswindow.h"
#include "paintermapimage.h"
#include "optdatanetwindow.h"
#include "painterdatanetimage.h"
#include "optbuilddatasetwindow.h"

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
    void connectRLS(RLS*);

    //
    void connectPainterDataNet(painterDataNetImage*);

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
};

#endif // GUI_H
