#include "gui.h"

#include <QApplication>

GUI::GUI(QImage* geoMap,
         QImage* dataNet,
         QImage* QFun,
         Map* map_)
{
    mainWin = new mainWindow;

    // карта
    map = map_;

    // Задача для работы с графической информацией
    visInfoWin = new visualInfoWidget(geoMap,
                                      dataNet,
                                      QFun,
                                      map_);
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
    optQFunWin = new optQFunWindow;
    mainWin->addTask(optQFunWin, QPixmap(":/resurs/qFunIcon.png"),
                     "Целевая функция", "Целевая функция");

    //
    optDNWin = new optDataNetWindow;
    mainWin->addTask(optDNWin, QPixmap(":/resurs/new"),
                     "Образ нейронной сети", "Генератор образа");

    //
    optRLSWin = new optRLSwindow(map_);
    //
    QObject::connect(visInfoWin, SIGNAL(updateCoordRLS(int,int)),
                     optRLSWin,  SLOT(updateCoordRLS(int,int)));
    mainWin->addTask(optRLSWin, QPixmap(":/resurs/rlsIcon"),
                     "РЛС", "Радиолокационная станция");

    //
    optBuildDSWin = new optBuildDataSetWindow;
    mainWin->addTask(optBuildDSWin, QPixmap(":/resurs/copy"),
                     "Обучающая выборка", "Генератор обучающей выборки");
    //
    netWin = new neuronNetworkWindow;
    mainWin->addTask(netWin, QPixmap(":/resurs/netIcon"),
                     "Нейронная сеть", "Нейронная сеть", mainWindow::usedNet);
    QObject::connect(visInfoWin, SIGNAL(setPointsTrail(QPoint,QPoint)),
                     netWin,     SLOT(setPointsPredictTrail(QPoint,QPoint)));
    QObject::connect(netWin,     SIGNAL(predictTrail(QString,int,int,int,int)),
                     visInfoWin, SLOT(startPredictTrail()));
    //
    droneWin = new optDroneWindow;
    mainWin->addTask(droneWin, QPixmap(":/resurs/plane"),
                     "БПЛА", "Беспилотный летательный аппарат", mainWindow::usedNet);

    //
    map3DWin = new map3DWindow(map);
    mainWin->addTask(map3DWin, QPixmap(":/resurs/icon3D"),
                     "3D", "Детальная визуализация рельефа");
}

void GUI::connectDrone(Drone* drone)
{
    //
    QObject::connect(droneWin,            SIGNAL(setAngleE(double)),
                     drone->getTracker(), SLOT(setE(double)));
}

void GUI::connectTrainerNet(trainerNetwork *trainer)
{
    //
    QObject::connect(netWin,  SIGNAL(trainNet(QString,QString,int,QString)),
                     trainer, SLOT(run(QString,QString,int,QString)));
    //
    QObject::connect(trainer, SIGNAL(updateListModels()),
                     netWin,  SLOT(updateModelsList()));
}

void GUI::connectBuilderTrail(builderTrailDrones* builderTrail)
{
    //
    QObject::connect(netWin,       SIGNAL(predictToRect(QString)),
                     builderTrail, SLOT(predictToRect(QString)));
    //
    QObject::connect(builderTrail, SIGNAL(resultPredictRect(int,int)),
                     netWin,       SLOT(finishRectPredict(int,int)));
    //
    QObject::connect(builderTrail, SIGNAL(setRect(int,int,int)),
                     visInfoWin,   SLOT(setIdCoordsRectPredict(int,int,int)));
    //
    QObject::connect(builderTrail, SIGNAL(resultPredictRect(int,int)),
                     visInfoWin,   SLOT(setResultPredictRect(int,int)));
    //
    QObject::connect(netWin, SIGNAL(predictTrail(QString,int,int,int,int)),
                     builderTrail, SLOT(startPredictTrail(QString,int,int,int,int)));
    //
    QObject::connect(builderTrail, SIGNAL(finishPredictTrail()),
                     visInfoWin,   SLOT(readyPredictTrail()));
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
}

void GUI::connectCalcQFun(calcQFunction* calcQFun)
{
    //
    QObject::connect(optQFunWin, SIGNAL(runCalcQFun()),
                     calcQFun,   SLOT(calculate()));
    //
    QObject::connect(calcQFun,   SIGNAL(calcStart(int)),
                     optQFunWin, SLOT(startGenImage(int)));
    //
    QObject::connect(calcQFun,   SIGNAL(readySigment(int)),
                     optQFunWin, SLOT(updateProgressGenImage(int)));
    //
    QObject::connect(calcQFun,   SIGNAL(readySigment(int)),
                     visInfoWin, SLOT(updateImage()));
    //
    QObject::connect(calcQFun,   SIGNAL(finish()),
                     optQFunWin, SLOT(finishGenImage()));
    //
    QObject::connect(visInfoWin, SIGNAL(setRectPredict(int,int)),
                     calcQFun,   SLOT(setRect(int,int)));
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
    QObject::connect(optRLSWin,  SIGNAL(createRLS(QPoint*)),
                     visInfoWin, SLOT(addRLS(QPoint*)));
    QObject::connect(optRLSWin,  SIGNAL(delRLS(int)),
                     visInfoWin, SLOT(delRLS(int)));

    //
    QObject::connect(optRLSWin, SIGNAL(createRLS(QPoint*)),
                     mRLS,      SLOT(addRLS(QPoint*)));
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
}

void GUI::connectMapPainter(painterMapImage* painterMap)
{
    QObject::connect(visInfoWin->getDrawArea(), SIGNAL(upEarth(int,int,int)),
                     painterMap,                SLOT(upEarth(int,int,int)));
    QObject::connect(visInfoWin->getDrawArea(), SIGNAL(downEarth(int,int,int)),
                     painterMap,                SLOT(downEarth(int,int,int)));
    QObject::connect(painterMap,                SIGNAL(readyEditEarth()),
                     visInfoWin->getDrawArea(), SLOT(readyEditEarth()));

    QObject::connect(map3DWin,   SIGNAL(generateMap3D()),
                     painterMap, SLOT(buildTexture()));
    QObject::connect(visInfoWin->getDrawArea(), SIGNAL(updateRect3D(int,int,int,int)),
                     painterMap,                SLOT(setRectTexture(int,int,int,int)));
    QObject::connect(painterMap, SIGNAL(readyTexture(int,int,int,int)),
                     map3DWin,   SLOT(finishBuildMap(int,int,int,int)));
    map3DWin->generateMap3D(); // сразу же отображаем то что есть

    QObject::connect(painterMap, SIGNAL(finish()),
                     visInfoWin, SLOT(updateImage()));
    QObject::connect(optRLSWin,  SIGNAL(getColorHeight(QColor*,int)),
                     painterMap, SLOT(heightToColor(QColor*,int)));
}

void GUI::connectPainterDataNet(painterDataNetImage* pDN)
{
    //
    QObject::connect(optDNWin, SIGNAL(generateImage()),
                     pDN,      SLOT(run()));
    //
    QObject::connect(pDN,        SIGNAL(finish()),
                     visInfoWin, SLOT(updateImage()));
    //
    QObject::connect(optDNWin, SIGNAL(updateKrgb(double,double,double,double,double)),
                     pDN,      SLOT(updateKrgb(double,double,double,double,double)));
    optDNWin->setDefaultK(); // сразу же устанавливаем значения по умолчанию
    //
    QObject::connect(visInfoWin, SIGNAL(setRectPredict(int,int)),
                     pDN,        SLOT(setRect(int,int)));

    // полоска прогресса
    QObject::connect(pDN,      SIGNAL(startGenerateImg(int)),
                     optDNWin, SLOT(startGenerateImg(int)));
    QObject::connect(pDN,      SIGNAL(readyStringDataNet(int)),
                     optDNWin, SLOT(updateProgressGenDN(int)));
    QObject::connect(pDN,      SIGNAL(finish()),
                     optDNWin, SLOT(finishGenerateImg()));
}

void GUI::connectBuilderDS(builderDataSet* builder)
{
    //
    QObject::connect(optBuildDSWin, SIGNAL(startGenerateDataSet(int,const QString&,const QString&,int)),
                     builder,       SLOT(run(int,const QString&,const QString&,int)));
    //
    QObject::connect(builder,      SIGNAL(buildNewMap()),
                     optGenMapWin, SLOT(startGenerateMap()));
    //
    QObject::connect(builder,       SIGNAL(readyData()),
                     optBuildDSWin, SLOT(readyPart()));
    // установка случайного квадрата прогноза
    QObject::connect(builder,    SIGNAL(setCoordRect(int,int,int)),
                     visInfoWin, SLOT(setIdCoordsRectPredict(int,int,int)));
}

void GUI::showMainWin()
{
    mainWin->show();
}
