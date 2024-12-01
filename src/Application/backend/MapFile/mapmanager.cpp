#include "mapmanager.h"

mapManager::mapManager()
{

}

void mapManager::create(const QString &path, MapData data)
{
    maps[path] = new MapFile(path, data);
}

void mapManager::open(const QString &path)
{
    maps[path] = new MapFile(path);
}
