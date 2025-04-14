#ifndef GIS_H
#define GIS_H

#include <QObject>

#include <QImage>
#include <QVector>

#include "paintermapimage.h"
#include "geogenerator.h"

#include "gisinformer.h"

#include "../MapFile/mapmanager.h"

// Геоинформационная система
class GIS: public QObject, public GISInformer
{
    Q_OBJECT
signals:

    // Земля отредактирована:
    //  в области
    void changedMap(int idXo, int idYo, // Левый верхний угол области
                    int dX, int dY);    // Размеры области
    //  полностью
    void changedMap();

public slots:

    // Редактирование рельефа
    void upEarth(int idX, int idY, int R);   // Поднять землю
    void downEarth(int idX, int idY, int R); // Опустить землю

    //
    void loadTerrain(const QString& dirNameFile);

public:

    //
    HeightMeter* getHeightMeter() const;

    // Получить интерфейс
    GISInformer* Informer() /* const */;

    // Методы-интерфейс по работе с ГИС:
    int getH(int idX, int idY, Coords::units = Coords::m) const override final;
    Coords getCoords(int idX, int idY) const override final;

    // При инициализации ГИС системы
    GIS(mapManager* mapsInfo);

private:

    //
    bool Enabled;

    //
    geoGenerator* geoBuilder;
};

#endif // GIS_H
