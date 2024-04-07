#include "gui.h"

#include <QApplication>

GUI::GUI(QImage* geoMap,
         Map* map_): map(map_)
{
    mainWin = new mainWindow;

    // Задача для работы с графической информацией
    visInfoWin = new visualInfoWidget(geoMap,
                                      map);

    //
    areaDrawWidget* drawArea = visInfoWin->getDrawArea();
    drawArea->setBlockSize(map->getLenBlock());

    // Инструменты для граф.области(какая область, приоритет-ключ задач отрисовки)
    toolPTrail  = new ToolPredTrail(drawArea, areaDrawWidget::predictTrail);
    toolPLine   = new ToolPredRect (drawArea, areaDrawWidget::predictRect);
    toolRLS     = new ToolSetRLS(   drawArea, areaDrawWidget::setRLS);
    toolEditTer = new ToolEditMap(  drawArea, areaDrawWidget::editEarth);
    toolVisMap  = new ToolVisMap(   drawArea, areaDrawWidget::mapVis);
    ToolRuler* toolRuler = new ToolRuler(drawArea, areaDrawWidget::Ruler);
    ToolSquareTer* toolSqTer = new ToolSquareTer(drawArea, areaDrawWidget::squareTer);

    QVector <drawAreaTool*> predTools = {toolPTrail, toolPLine};
    drawArea->appendToolGroup(predTools, "Прогноз");

    QVector <drawAreaTool*> rulersTools = {toolRuler, toolSqTer};
    drawArea->appendToolGroup(rulersTools, "Измерения");

    drawArea->appendTool(toolRLS);
    drawArea->appendTool(toolEditTer);
    drawArea->appendTool(toolVisMap);

    //
    QObject::connect(visInfoWin, SIGNAL(saveMap_signal(QString)),
                     map,        SLOT(save(QString)));
    mainWin->addTask(visInfoWin, QPixmap(":/resurs/imgIcon"),
                     "Визуализатор", "Графическое представление");

    //
    optGenMapWin = new optMapGeneratorWindow;
    QObject::connect(optGenMapWin, SIGNAL(openMap_signal(QString)),
                     map,          SLOT(open(QString)));
    mainWin->addTask(optGenMapWin, QPixmap(":/resurs/earchIcon"),
                     "Карта", "Карта");

    //
    optRLSWin = new optRLSwindow(map_);
    //
    QObject::connect(toolRLS,   SIGNAL(setCoordRLS(int,int)),
                     optRLSWin, SLOT(updateCoordRLS(int,int)));
    mainWin->addTask(optRLSWin, QPixmap(":/resurs/rlsIcon"),
                     "РЛС", "Радиолокационная станция");

    //
    droneWin = new optDroneWindow;
    mainWin->addTask(droneWin, QPixmap(":/resurs/plane"),
                     "БПЛА", "Беспилотный летательный аппарат");

    //
    QObject::connect(toolPTrail, SIGNAL(sendPointsTrail(int,int,int,int)),
                     droneWin,   SLOT(setPredictPoints(int,int,int,int)));
    QObject::connect(droneWin,   SIGNAL(runPredictTrail(int,int,int,int)),
                     toolPTrail, SLOT(startPredictTrail()));

    //
    map3DWin = new map3DVisWindow(map, geoMap);
    mainWin->addTask(map3DWin, QPixmap(":/resurs/icon3D"),
                     "3D", "Детальная визуализация рельефа");


    //
    daoWin = new DataAccessObjectWindow;
    mainWin->addTask(daoWin,        QPixmap(":/resurs/base1"),
                     "База данных", "Подключение базы данных");

    // Окно по работе с функцией прогноза
    algPredWin = new setAlgPredictWindow;
    mainWin->addTask(algPredWin,         QPixmap(":/resurs/qFunIcon"),
                     "Функция прогноза", "Функция прогноза");
}

void GUI::connectMDrones(managerDrones* mDrones)
{

}

void GUI::connectDataBase(DAO *database)
{
    QObject::connect(daoWin,   SIGNAL(connection(QString)),
                     database, SLOT(test_query(QString))
            );
    QObject::connect(database, SIGNAL(update_status(bool)),
                     daoWin, SLOT(status_connect(bool))
            );
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

void GUI::connectMapGenerator(geoGenerator* mapBuilder)
{
    //
    QObject::connect(optGenMapWin, SIGNAL(runGenerateMap(double,int,int,int,int, double)),
                     mapBuilder,   SLOT(run(double,int,int,int,int, double)));
    //
    QObject::connect(mapBuilder,   SIGNAL(buildStart(int)),
                     optGenMapWin, SLOT(setProgressBar(int)));
    //
    QObject::connect(mapBuilder,   SIGNAL(readyLayer(int)),
                     optGenMapWin, SLOT(updateProgressBar(int)));
    //
    QObject::connect(mapBuilder,   SIGNAL(buildFinish()),
                     optGenMapWin, SLOT(finishGenerateMap()));

    QObject::connect(mapBuilder, SIGNAL(readyLayer(int)),
                     map3DWin,   SLOT(updateMap3D()));
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
                     visInfoWin, SLOT(addRLS(QPoint*,const QString&)));
    QObject::connect(optRLSWin,  SIGNAL(delRLS(int)),
                     visInfoWin, SLOT(delRLS(int)));

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
                     visInfoWin, SLOT(setCurRLS(int)));

    //
    QObject::connect(optRLSWin,  SIGNAL(signalRunRLS(int)),
                     mRLS,       SLOT(runRLS(int)));
    //
    QObject::connect(mRLS,       SIGNAL(startGenerateZD(int)),
                     optRLSWin,  SLOT(startGenerateZD(int)));
    //
    QObject::connect(mRLS,       SIGNAL(readyVector(int)),
                     optRLSWin,  SLOT(readyVector(int)));
    //
    QObject::connect(mRLS,       SIGNAL(finishGenerateZD()),
                     optRLSWin,  SLOT(finishGenerateZD()));
    // обмен данными для отрисовки графика ДН
    QObject::connect(optRLSWin,  SIGNAL(getDataGraphic()),
                     mRLS,       SLOT(getDataGraphic()));
    QObject::connect(mRLS,       SIGNAL(exportGraphicData(double*, double*, int)),
                     optRLSWin,  SLOT(repaintGraphic(double*, double*, int)));
    //optRLSWin->getDataGraphic(); // сразу же отображаем ДН

    // установка пар-ов сигнала и его моделирования в пространстве
    QObject::connect(optRLSWin,  SIGNAL(updateOptZDvert(int,int,int)),
                     mRLS,       SLOT(setOptZDvert(int,int,int)));
    //
    QObject::connect(mRLS,       SIGNAL(readyOptZDvert()),
                     optRLSWin,  SLOT(readyOptZDvert()));

    //
    QObject::connect(mRLS,       SIGNAL(startSetOpt(int)),
                     optRLSWin,  SLOT(startSetOptRLS(int)));
    //
    QObject::connect(mRLS,       SIGNAL(readySetRay(int)),
                     optRLSWin,  SLOT(updateProgressSetOptRLS(int)));

    //
    QObject::connect(visInfoWin->getDrawArea(), SIGNAL(updateSignals()),
                     mRLS,                      SLOT(updateSignals()));

    // обновление визуализации сигнала
    QObject::connect(mRLS, SIGNAL(sendPointsInterZD(QVector<QVector<QVector<QVector3D>>>*, QList <QVector3D>*)),
                     map3DWin, SLOT(updatePointsInterZD(QVector<QVector<QVector<QVector3D>>>*, QList <QVector3D>*)));
}

void GUI::connectMapPainter(painterMapImage* painterMap)
{
    // Ручное редактирование рельефа
    QObject::connect(toolEditTer, SIGNAL(upEarth(int,int,int)),
                     painterMap,  SLOT(upEarth(int,int,int)));
    QObject::connect(toolEditTer, SIGNAL(downEarth(int,int,int)),
                     painterMap,  SLOT(downEarth(int,int,int)));

    QObject::connect(painterMap, SIGNAL(readyEditEarth(int,int,int)),
                     map3DWin,   SLOT(updateMap3D(int,int,int)));
    QObject::connect(map3DWin,   SIGNAL(generateMap3D()),
                     painterMap, SLOT(buildTexture()));
    QObject::connect(toolVisMap, SIGNAL(updateRect3D(int,int,int,int)),
                     painterMap, SLOT(setRectTexture(int,int,int,int)));
    QObject::connect(painterMap, SIGNAL(readyTexture(int,int,int,int)),
                     map3DWin,   SLOT(finishBuildMap(int,int,int,int)));
    map3DWin->generateMap3D(); // сразу же отображаем то что есть

    QObject::connect(painterMap, SIGNAL(finish()),
                     visInfoWin, SLOT(updateImage()));
    QObject::connect(optRLSWin,  SIGNAL(getColorHeight(QColor*,int)),
                     painterMap, SLOT(heightToColor(QColor*,int)));
}

void GUI::showMainWin()
{
    mainWin->show();
}
