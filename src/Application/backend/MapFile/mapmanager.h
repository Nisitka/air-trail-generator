#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QMap>

#include "./mapfile.h"
#include "backend/mapinformer.h"

#include <QMutexLocker>

// Управляем картами (с какой сейчас работаем и т.д.)
class mapManager: public QObject,
        public MapInformer
{
    Q_OBJECT

public:
    mapManager();

    /// Интерфес общих сведений
    // Кол-во карт
    int count() const override final;

    //
    bool createMap(MapData data, const QString& path);
    bool openMap(const QString &path);
    bool removeMap(const QString &path);

    //
    bool setCurrentMap(const QString& pathMap);

    //
    MapFile* getCurrentMap() const;

private:

    // Все карты
    QMap <QString, MapFile*> maps;

    //
    QString currentMap;
};

#endif // MAPMANAGER_H
