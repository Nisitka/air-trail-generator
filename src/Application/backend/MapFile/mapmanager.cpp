#include "mapmanager.h"

#include <QDebug>

mapManager::mapManager()
{

}

void mapManager::createMap(MapData data, const QString &path)
{
    startCreateMap();
    maps[path] = new MapFile(path, data);

    //
    setCurrentMap(path);

    finishCreateMap();
}

void mapManager::openMap(const QString &path)
{
    startOpenMap();
    maps[path] = new MapFile(path);

    //
    setCurrentMap(path);

    finishOpenMap();
}

void mapManager::setCurrentMap(const QString &pathMap)
{
    if (maps.size() > 1)
        maps[currentMap]->close();

    currentMap = pathMap;
    maps[currentMap]->reopen();

    qDebug() << "current map: " + currentMap;
    changedCurrentMap();
}

MapFile* mapManager::getCurrentMap() const
{
    return maps.value(currentMap);
}
