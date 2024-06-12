#include "gui.h"

#include <QApplication>

#include "drawArea/mapareamainwindow.h"

GUI::GUI(GISInformer* gis):
    gisInformer(gis)
{
    mainWin = new mainWindow;

    // Задача для работы с графической информацией
    visInfoWin = new visualInfoWidget(gisInformer);

    //
    mapAreaMainWindow* manDrawArea = visInfoWin->getManDrawArea();

    // Инструменты для граф.области(какая область, приоритет-ключ задач отрисовки)
    toolPTrail  = new ToolPredTrail(mapAreaMainWindow::predictTrail);
    toolPLine   = new ToolPredRect (mapAreaMainWindow::predictRect);
    toolRLS     = new ToolSetRLS(   mapAreaMainWindow::setRLS, gis);
    toolEditTer = new ToolEditMap(  mapAreaMainWindow::editEarth);
    toolVisMap  = new ToolVisMap(   mapAreaMainWindow::mapVis);
    ToolRuler* toolRuler = new ToolRuler(mapAreaMainWindow::Ruler);
    ToolSquareTer* toolSqTer = new ToolSquareTer(mapAreaMainWindow::squareTer);

    QVector <drawAreaTool*> predTools = {toolPTrail, toolPLine};
    manDrawArea->appendToolGroup(predTools, "Прогноз");

    QVector <drawAreaTool*> rulersTools = {toolRuler, toolSqTer};
    manDrawArea->appendToolGroup(rulersTools, "Измерения");

    manDrawArea->appendTool(toolRLS);
    manDrawArea->appendTool(toolEditTer);
    manDrawArea->appendTool(toolVisMap);

    //
    mainWin->addTask(visInfoWin, QIcon(":/resurs/imgIcon"),
                     "Визуализатор", "Графическое представление");

    //
    optGenMapWin = new optMapGeneratorWindow;
    mainWin->addTask(optGenMapWin, QIcon(":/resurs/earchIcon"),
                     "Карта", "Карта");

    //
    optRLSWin = new optRLSwindow();
    QObject::connect(toolRLS,   SIGNAL(setCoordRLS(Coords)),
                     optRLSWin, SLOT(updateCoordRLS(Coords)));
    mainWin->addTask(optRLSWin, QIcon(":/resurs/rlsIcon"),
                     "РЛС", "Радиолокационная станция");

    //
    droneWin = new optDroneWindow;
    mainWin->addTask(droneWin, QIcon(":/resurs/plane"),
                     "БПЛА", "Беспилотный летательный аппарат");

    //
    QObject::connect(toolPTrail, SIGNAL(sendPointsTrail(int,int,int,int)),
                     droneWin,   SLOT(setPredictPoints(int,int,int,int)));
    QObject::connect(droneWin,   SIGNAL(runPredictTrail(int,int,int,int)),
                     toolPTrail, SLOT(startPredictTrail()));

    //
    map3DWin = new map3DVisWindow();
    mainWin->addTask(map3DWin, QPixmap(":/resurs/icon3D"),
                     "3D", "Детальная визуализация рельефа");
    QObject::connect(toolVisMap, SIGNAL(updateRect3D(int,int,int,int)),
                     map3DWin,   SLOT(setVisRect(int,int,int,int)));

    // Окно по работе с функцией прогноза
    algPredWin = new setAlgPredictWindow;
    mainWin->addTask(algPredWin,         QPixmap(":/resurs/qFunIcon"),
                     "Функция прогноза", "Функция прогноза");
}

void GUI::connectBuilderTrail(builderTrailDrones* builderTrail)
{
    // Инструменты
    QObject::connect(toolPLine,    SIGNAL(setRpred(int)),
                     builderTrail, SLOT(setRpredict(int)));
    QObject::connect(toolPTrail,   SIGNAL(setRpred(int)),
                     builderTrail, SLOT(setRpredict(int)));

    //
    QObject::connect(droneWin,     SIGNAL(runPredictTrail(int,int,int,int)),
                     builderTrail, SLOT(startPredictTrail(int,int,int,int)));
    QObject::connect(builderTrail, SIGNAL(nextPointTrail(int,int,int)),
                     toolPTrail,   SLOT(addPointTrail(int,int,int)));

    //
    QObject::connect(droneWin,                      SIGNAL(runPredictTrail(int,int,int,int)),
                     map3DWin->getGraphicsWidget(), SLOT(startPredictTrail()));
    QObject::connect(builderTrail,                  SIGNAL(nextPointTrail(int,int,int)),
                     map3DWin->getGraphicsWidget(), SLOT(addTrailPoint(int,int,int)));

    //
    QObject::connect(builderTrail, SIGNAL(startSetOptPredict()),
                     droneWin,     SLOT(startSetOptPredict()));
    QObject::connect(builderTrail, SIGNAL(finishSetOptPredict()),
                     droneWin,     SLOT(finishSetOptPredict()));
    QObject::connect(builderTrail, SIGNAL(procSetOptPred(int)),
                     droneWin,     SLOT(updateProgSetOptPred(int)));
}

void GUI::connectGIS(GIS *gis)
{
    // Изменяем подгруженную область
    QObject::connect(visInfoWin->getManDrawArea(), SIGNAL(moveActionArea(int,int)),
                     gis,                          SLOT(movePosActionArea(int,int)));
    QObject::connect(gis,                          SIGNAL(changedActionArea(int,int)),
                     visInfoWin->getManDrawArea(), SLOT(setNewActionArea(int,int)));

    // Ручное редактирование рельефа
    QObject::connect(toolEditTer, SIGNAL(upEarth(int,int,int)),
                     gis,         SLOT(upEarth(int,int,int)));
    QObject::connect(toolEditTer, SIGNAL(downEarth(int,int,int)),
                     gis,         SLOT(downEarth(int,int,int)));

    // Реакция интерфейса на изменения подложки
    QObject::connect(gis,                          SIGNAL(changedMap()),
                     visInfoWin->getManDrawArea(), SLOT(repaintBackground()));
    QObject::connect(gis,                          SIGNAL(changedMap(int,int,int,int)),
                     visInfoWin->getManDrawArea(), SLOT(repaintBackground()));
    QObject::connect(gis,                          SIGNAL(finishBuildMap(int,int,int)),
                     visInfoWin->getManDrawArea(), SLOT(updateGeoMapImage()));

    // Отображение в 3D
    QObject::connect(gis,      SIGNAL(finishBuildMap(int,int,int)),
                     map3DWin, SLOT(setVisRectDef()));
    QObject::connect(gis,      SIGNAL(changedMap(int,int,int,int)),
                     map3DWin, SLOT(updateMap3D(int,int,int,int)));
}

void GUI::connectMRLS(managerRLS* mRLS)
{
    //
    QObject::connect(mRLS,      SIGNAL(createReadyRLS()),
                     optRLSWin, SLOT(buildNewRLSready()));
    //
    QObject::connect(optRLSWin, SIGNAL(signalOffRLS()),
                     mRLS,      SLOT(offRLS()));
    //
    QObject::connect(optRLSWin, SIGNAL(setPositionRLS(int,int)),
                     mRLS,      SLOT(setPositionRLS(int,int)));
    //
    QObject::connect(mRLS,      SIGNAL(updateOptGui(int,int,int,int,bool)),
                     optRLSWin, SLOT(setOptRLS(int,int,int,int,bool)));

    // добавление/удаление РЛС
    QObject::connect(optRLSWin,  SIGNAL(createRLS(QPoint*,const QString&)),
                     toolRLS,    SLOT(addRLS(QPoint*,const QString&)));
    QObject::connect(optRLSWin,  SIGNAL(delRLS(int)),
                     toolRLS,    SLOT(delRLS(int)));

    //
    QObject::connect(optRLSWin, SIGNAL(createRLS(QPoint*,const QString&)),
                     mRLS,      SLOT(addRLS(QPoint*,const QString&)));
    //
    QObject::connect(optRLSWin, SIGNAL(delRLS(int)),
                     mRLS,      SLOT(delRLS(int)));

    // установка выбранной РЛС
    QObject::connect(optRLSWin, SIGNAL(setRLS(int)),
                     mRLS,      SLOT(setRLS(int)));
    QObject::connect(optRLSWin,  SIGNAL(setRLS(int)),
                     toolRLS,    SLOT(setCurRLS(int)));

    //
    QObject::connect(optRLSWin,  SIGNAL(signalRunRLS()),
                     mRLS,       SLOT(runRLS()));
    //
    QObject::connect(mRLS,       SIGNAL(startEmitSignal()),
                     optRLSWin,  SLOT(startProcessing()));
    //
    QObject::connect(mRLS,       SIGNAL(finishGenerateZD()),
                     optRLSWin,  SLOT(finishProcessing()));
    // обмен данными для отрисовки графика ДН
    QObject::connect(optRLSWin,  SIGNAL(getDataGraphic()),
                     mRLS,       SLOT(getDataGraphic()));
    QObject::connect(mRLS,       SIGNAL(exportGraphicData(double*, double*, int)),
                     optRLSWin,  SLOT(repaintGraphic(double*, double*, int)));

    // Установка пар-ов сигнала и его моделирования в пространстве
    QObject::connect(optRLSWin,  SIGNAL(updateOptZDvert(int,int,int)),
                     mRLS,       SLOT(setOptZDvert(int,int,int)));
    //
    QObject::connect(mRLS,       SIGNAL(readyOptZDvert()),
                     optRLSWin,  SLOT(finishProcessing()));

    //
    QObject::connect(mRLS,      SIGNAL(startClearZD()),
                     optRLSWin, SLOT(startProcessing()));
    QObject::connect(mRLS,      SIGNAL(clearZD()),
                     optRLSWin, SLOT(finishProcessing()));

    //
    QObject::connect(mRLS,       SIGNAL(startSetOpt()),
                     optRLSWin,  SLOT(startProcessing()));
    //
    QObject::connect(mRLS,       SIGNAL(changeStatProcessing(int)),
                     optRLSWin,  SLOT(updateStatProcessing(int)));

    /// !!!!!!!!!!!!!!!!!!!!!!!!!!
    QObject::connect(visInfoWin->getManDrawArea()->getDrawArea(), SIGNAL(updateSignals()),
                     mRLS, SLOT(updateSignals()));

    // Обновление визуализации сигнала
    QObject::connect(mRLS,     SIGNAL(sendPointsInterZD(QVector<QVector<QVector<QVector3D>>>*, QList <QVector3D>*)),
                     map3DWin, SLOT(updatePointsInterZD(QVector<QVector<QVector<QVector3D>>>*, QList <QVector3D>*)));
}

void GUI::showMainWin()
{
    mainWin->show();
}
