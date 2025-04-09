#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <QObject>

#include "backend/GIS/mapdata.h"

// Класс-интерфейс для создания и удаления карт
class MapCreator: public QObject
{
    Q_OBJECT
signals:

    // Создать карту
    void create(MapData data, const QString& pathNewFile);

    // Добавить карту к себе в проект
    void append(const QString &pathFile);

public:
    MapCreator() {}
};

#endif // MAPCREATOR_H
