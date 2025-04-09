#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>

#include "./projectfile.h"

#include "./mapcreator.h"
#include "eventsmapmanager.h"

#include "./mapinformer.h"

#include "./MapFile/mapmanager.h"

// Класс управляющий проектом
class ProjectManager: public QObject
{
    Q_OBJECT

signals:

    //
    void createdProjectFile();
    void openedProjectFile();
    void closedProjectFile();

    //
    void appendObject(int typeObj);
    void removedObject(int typeObj);

    //
    void error(int codeError);

public slots:

    /// Работа с проектом
    // Создать новый проект
    void createProject(const QString& dirNameNewProject);

    // Открыть сущесвующий проект
    void openProject(const QString& dirNameProject);

private slots:

    /// Карты
    // Добавить карту в проект
    void addMap(const QString& dirNameMap);

    // Удалить карту из проекта
    void removeMap(const QString& nameMap);

    // Создать карту с нуля
    void createMap(MapData data, const QString& pathNewFile);


    /// РЛС
    // Добавть РЛС в проект
    void addRLS(const QString& dirNameRLS);

    // Удалить РЛС из проекта
    void removeRLS(const QString& nameRLS);

public:
    ProjectManager();

    enum errors{openFile, closeFile, createFile,
                addObj, removeObj,
                readFile, writeFile};

    //
    MapCreator* CreatorMaps();

    //
    MapInformer* InfoMaps();

    //
    EventsMapManager* EventsMaps();

private:

    // Интерфейс по работе с картами
    MapCreator* mapCreator;
    // Отображает все события связанные с картами
    EventsMapManager* mapEvents;

    // Тот, кто непосредственно управляет ими
    mapManager* managerMaps;

    // Закрыть текущий проект
    void closeProject();

    // pro файл проекта
    ProjectFile* proFile;
};

#endif // PROJECTMANAGER_H
