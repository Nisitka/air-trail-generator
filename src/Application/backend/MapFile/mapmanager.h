#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QMap>

#include "./mapfile.h"
#include "./mapcreator.h"

// Управляем картами
class mapManager:
        public MapCreator
{
public:
    mapManager();

    //
    void create(const QString& path, MapData data) override final;
    void open(const QString &path) override final;

private:

    // Все карты
    QMap <QString, MapFile*> maps;
};

#endif // MAPMANAGER_H
