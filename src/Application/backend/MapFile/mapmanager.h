#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QMap>

#include "./mapfile.h"

#include <QMutexLocker>

// Управляем картами
class mapManager: public QObject
{
    Q_OBJECT

signals:

    //
    void changedCurrentMap();

    //
    void startCreateMap();
    void finishCreateMap();

    //
    void startOpenMap();
    void finishOpenMap();

public slots:

    //
    void createMap(MapData data, const QString& path);
    void openMap(const QString &path);

    //
    void setCurrentMap(const QString& pathMap);

public:
    mapManager();

    //
    MapFile* getCurrentMap() const;

private:

    // Все карты
    QMap <QString, MapFile*> maps;

    //
    QString currentMap;
};

#endif // MAPMANAGER_H
