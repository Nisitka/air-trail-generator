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
    mainWin->addTask(visInfoWin, QPixmap(":/resurs/imgIcon"),
                     "Визуализатор", "Графическое представление");

    //
    optGenMapWin = new optMapGeneratorWindow;
    mainWin->addTask(optGenMapWin, QPixmap(":/resurs/earchIcon"),
                     "Карта", "Карта");

    //
    optQFunWin = new optQFunWindow;
    mainWin->addTask(optQFunWin, QPixmap(":/resurs/qFunIcon.png"),
                     "Целевая функция", "Целевая функция");

    //
    optDNWin = new optDataNetWindow;
    mainWin->addTask(optDNWin, QPixmap(":/resurs/netIcon"),
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
    mainWin->addTask(optBuildDSWin, QPixmap(":/resurs/"),
                     "ОВ", "Генератор обучающей выборки");
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
    QObject::connect(mapBuilder,   SIGNAL(buildStart(int)),
                     visInfoWin,   SLOT(updateSizeDrawArea()));
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
    QObject::connect(optQFunWin, SIGNAL(runCalcQFun(double)),
                     calcQFun,   SLOT(calculate(double)));
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
}

void GUI::connectRLS(RLS* rls)
{
    //
    QObject::connect(optRLSWin, SIGNAL(signalRunRLS(int,int,int)),
                     rls,       SLOT(run(int,int,int)));
    //
    QObject::connect(rls,       SIGNAL(startGenerateZD(int)),
                     optRLSWin, SLOT(startGenerateZD(int)));
    //
    QObject::connect(rls,       SIGNAL(readyVector(int)),
                     optRLSWin, SLOT(readyVector(int)));
    //
    QObject::connect(rls,       SIGNAL(finishGenerateZD()),
                     optRLSWin, SLOT(finishGenerateZD()));
    // обмен данными для отрисовки графика ДН
    QObject::connect(optRLSWin, SIGNAL(getDataGraphic()),
                     rls,       SLOT(getDataGraphic()));
    QObject::connect(rls,       SIGNAL(exportGraphicData(double*, double*, int)),
                     optRLSWin, SLOT(repaintGraphic(double*, double*, int)));
    optRLSWin->getDataGraphic(); // сразу же отображаем ДН

    //
    QObject::connect(optRLSWin, SIGNAL(updateOptZDvert(int)),
                     rls,       SLOT(setOptZDvert(int)));
    //
    QObject::connect(rls,       SIGNAL(readyOptZDvert()),
                     optRLSWin, SLOT(readyOptZDvert()));
}

void GUI::connectMapPainter(painterMapImage* painterMap)
{
    QObject::connect(painterMap, SIGNAL(finish()),
                     visInfoWin, SLOT(updateImage()));
}

void GUI::connectPainterDataNet(painterDataNetImage* pDN)
{
    //
    QObject::connect(optDNWin, SIGNAL(generateImage()),
                     pDN,      SLOT(run()));
    //
    QObject::connect(pDN, SIGNAL(finish()),
                     visInfoWin, SLOT(updateImage()));
}

void GUI::showMainWin()
{
    mainWin->show();
}
