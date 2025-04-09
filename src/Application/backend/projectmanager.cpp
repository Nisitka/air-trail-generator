#include "projectmanager.h"

ProjectManager::ProjectManager()
{
    proFile = nullptr;

    //
    mapCreator = new MapCreator;
    connect(mapCreator, SIGNAL(append(QString)),
            this,       SLOT(addMap(QString)));
    connect(mapCreator, SIGNAL(create(MapData,QString)),
            this,       SLOT(createMap(MapData,QString)));

    //
    mapEvents = new EventsMapManager;

    //
    managerMaps = new mapManager;
}

void ProjectManager::createMap(MapData data, const QString &pathNewFile)
{
    // Предупреждаем кому это интересно о том, что начали создавать карту
    mapEvents->startCreateMap();

    // Пробуем создать карту через менеджер
    if (managerMaps->createMap(data, pathNewFile))
        mapEvents->finishCreateMap();
    else
        mapEvents->error(EventsMapManager::create);
}

void ProjectManager::addMap(const QString &dirNameMap)
{
    mapEvents->startOpenMap();

    // Пробуем открыть карту через менеджер
    if(managerMaps->openMap(dirNameMap))
    {
        // Если открыли то добавляем в файл проекта
        if (proFile->addData(ProjectFile::map, dirNameMap))
        {
            appendObject(ProjectFile::map);
            mapEvents->finishOpenMap();
        }
        else
        {
            // Сообщаем что неудалось добавить сущность в файл проекта
            error(addObj);

            // Исключаем файл-карту из менеджера обратно
            if(managerMaps->removeMap(dirNameMap))
                mapEvents->error(EventsMapManager::open);
            else
                mapEvents->error(EventsMapManager::fatal);
        }
    }
    else
        mapEvents->error(EventsMapManager::open);
}

void ProjectManager::removeMap(const QString &nameMap)
{
    if (managerMaps->removeMap(nameMap))
        mapEvents->removeMap(nameMap);
    else
        mapEvents->error(EventsMapManager::remove);
}

MapCreator* ProjectManager::CreatorMaps()
{
    return mapCreator;
}

MapInformer* ProjectManager::InfoMaps()
{
    return (MapInformer*)managerMaps;
}

EventsMapManager* ProjectManager::EventsMaps()
{
    return mapEvents;
}

void ProjectManager::closeProject()
{
    if (proFile->close())
        closedProjectFile();
    else
        error(closeFile);
}

void ProjectManager::createProject(const QString &dirNameNewProject)
{
    if (proFile->create(dirNameNewProject))
        createdProjectFile();
    else
        error(createFile);
}

void ProjectManager::openProject(const QString &dirNameProject)
{
    if (proFile->open(dirNameProject))
        openedProjectFile();
    else
        error(openFile);
}

void ProjectManager::addRLS(const QString &dirNameRLS)
{
    if(proFile->addData(ProjectFile::RLS, dirNameRLS))
        appendObject(ProjectFile::RLS);
    else
        error(addObj);
}

void ProjectManager::removeRLS(const QString &dirNameRLS)
{
    if (proFile->deleteData(ProjectFile::RLS, dirNameRLS))
        removedObject(ProjectFile::RLS);
    else
        error(removeObj);
}
