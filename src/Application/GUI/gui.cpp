#include "gui.h"

#include <QApplication>

#include "drawArea/mapareamainwindow.h"

#include <QFileDialog>

GUI::GUI(GISInformer* gis,
         InformerRLS* infoRLS): QObject(nullptr),
    gisInformer(gis)
{
    //
    mainWin = new mainWindow;

    // Задача для работы с графической информацией
    visInfoWin = new visualInfoWidget(gisInformer);

    //
    mapAreaMainWindow* manDrawArea = visInfoWin->getManDrawArea();

    // Инструменты для граф.области(какая область, приоритет-ключ задач отрисовки)
    toolPTrail  = new ToolPredTrail(mapAreaMainWindow::predictTrail);
    toolPLine   = new ToolPredRect (mapAreaMainWindow::predictRect);
    toolRLS     = new ToolSetRLS(   mapAreaMainWindow::setRLS, gis, infoRLS);
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

    // Окно управления РЛС
    manRLSWin = new manRLSWindow(infoRLS);
    mainWin->addTask(manRLSWin, QIcon(":/resurs/rlsIcon"),
                     "РЛС", "Радиолокационная станция");

    // Окно по работе с функцией прогноза
    algPredWin = new setAlgPredictWindow;
    mainWin->addTask(algPredWin,         QPixmap(":/resurs/qFunIcon"),
                     "Функция прогноза", "Функция прогноза");

    //
    helloWin = new helloWindow;
    connect(helloWin, SIGNAL(choiceProjectFile()),
            this,     SLOT(showOpenProjectWindow()));

    //
    switcherWindow = new mainSwitcherWindow;
    connect(switcherWindow, SIGNAL(choiceProjectFile()),
            this,           SLOT(showOpenProjectWindow()));

    //
    createProjWin = new createProjectWindow(switcherWindow);
    connect(helloWin,      SIGNAL(showMasterBuildProject()),
            createProjWin, SLOT(exec()));
    connect(switcherWindow, SIGNAL(showMasterBuildProject()),
            createProjWin,  SLOT(exec()));

        /*       */
    //
    switcherWindow->addWindow(helloWin,
                              QIcon(":/resurs/home"),
                              "Начало");
    //
    switcherWindow->addWindow(mainWin,
                              QIcon(":/resurs/earchIcon"),
                              "Редактор", true); //  Главное окно
}

createProjectWindow* GUI::WindowCreateProject() const
{
    return createProjWin;
}

void GUI::showOpenProjectWindow()
{
    //
    QString dirName = QFileDialog::getOpenFileName(nullptr, "Открыть файл проекта",
                                                   QApplication::applicationDirPath(),
                                                   "*.map");

    if (dirName.size() > 0)
        openProject(dirName);
}

void GUI::connectBuilderTrail(BuilderTrail* builderTrail)
{
    // Инструменты
    QObject::connect(toolPLine,    SIGNAL(setRpred(int)),
                     builderTrail, SLOT(setRpredict(int)));
    QObject::connect(toolPTrail,   SIGNAL(setRpred(int)),
                     builderTrail, SLOT(setRpredict(int)));

    //
    QObject::connect(builderTrail, SIGNAL(nextPointTrail(int,int,int)),
                     toolPTrail,   SLOT(addPointTrail(int,int,int)));
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

    //
    QObject::connect(gis,            SIGNAL(finishBuildMap(int,int,int)),
                     switcherWindow, SLOT(showMainWindow()));

    // Открыть файл-проект
    QObject::connect(this,  SIGNAL(openProject(QString)),
                     gis,   SLOT(openMap(QString)));

    // При завершении подготовки карты - инициализировать визуальную часть проекта
    QObject::connect(gis,        SIGNAL(finishBuildMap(int,int,int)),
                     visInfoWin, SLOT(initProject()));
}

void GUI::connectMRLS(managerRLS* mRLS)
{
    // Окно добавления РЛС
    addRLSWin = new addRLSWindow((CreatorRLS*)mRLS, gisInformer);
    connect(manRLSWin, SIGNAL(addRLS()),
            addRLSWin, SLOT(exec()));

    //
    QObject::connect(mRLS,      SIGNAL(createReadyRLS()),
                     manRLSWin, SLOT(updateListRLS()));
    QObject::connect(mRLS,      SIGNAL(deleteReadyRLS()),
                     manRLSWin, SLOT(updateListRLS()));

    //
    QObject::connect(mRLS, SIGNAL(changeDataRLS(int)),
                     manRLSWin, SLOT(updateDataRLS(int)));

    //
    QObject::connect(manRLSWin, SIGNAL(offRLS()),
                     mRLS,      SLOT(offRLS()));
    //
    QObject::connect(manRLSWin, SIGNAL(setPositionRLS(int,int)),
                     mRLS,      SLOT(setPositionRLS(int,int)));

    // добавление/удаление РЛС
    QObject::connect(mRLS,    SIGNAL(createReadyRLS()),
                     toolRLS, SLOT(updateInfoRLS()));
    QObject::connect(mRLS,    SIGNAL(deleteReadyRLS()),
                     toolRLS, SLOT(updateInfoRLS()));
    //
    QObject::connect(manRLSWin, SIGNAL(delRLS(int)),
                     mRLS,      SLOT(delRLS(int)));

    // установка выбранной РЛС
    QObject::connect(manRLSWin, SIGNAL(setCurrentRLS(int)),
                     mRLS,      SLOT(setCurrentRLS(int)));
    QObject::connect(mRLS,    SIGNAL(changeCurrentRLS()),
                     toolRLS, SLOT(updateInfoRLS()));
    QObject::connect(mRLS, SIGNAL(changeCurrentRLS()),
                     manRLSWin, SLOT(showInfoCurRLS()));

    //
    QObject::connect(manRLSWin,  SIGNAL(runRLS()),
                     mRLS,       SLOT(runRLS()));
}

void GUI::showMainWin()
{
    switcherWindow->setCurrentWindow(helloWin);
    switcherWindow->show();
}
