#include "mapmanager.h"

#include <QDebug>

mapManager::mapManager()
{

}

int mapManager::count() const
{
    return maps.count();
}

/// НУЖЕН РЕФАКТОРИНГ MapFile
bool mapManager::createMap(MapData data, const QString &path)
{
    bool result = false;

    if (!maps.contains(path))
    {
        maps[path] = new MapFile(path, data);
        result = true;
    }

    return result;
}

/// НУЖЕН РЕФАКТОРИНГ MapFile
bool mapManager::openMap(const QString &path)
{
    bool result = false;

    if (!maps.contains(path))
    {
        maps[path] = new MapFile(path);
        result = true;
    }

    return result;
}

bool mapManager::removeMap(const QString &path)
{
    bool result = false;

    if (maps.contains(path))
    {
        // Удаляем файл по его адрессу
        delete maps[path];

        // Удаляем из списков
        maps.remove(path);
        result = true;
    }

    return result;
}

bool mapManager::setCurrentMap(const QString &pathMap)
{
    bool result = false;

    if (maps.size() > 1)
        maps[currentMap]->close();

    currentMap = pathMap;
    maps[currentMap]->reopen();

    qDebug() << "current map: " + currentMap;

    return result;
}

MapFile* mapManager::getCurrentMap() const
{
    return maps.value(currentMap);
}
