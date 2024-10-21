#ifndef GIS_H
#define GIS_H

#include <QObject>

#include <QImage>
#include <QVector>

#include "paintermapimage.h"
#include "geogenerator.h"

#include "gisinformer.h"

// Геоинформационная система
class GIS: public QObject, public GISInformer
{
    Q_OBJECT
signals:

    // Сигнализируем об готовности новой области
    void changedActionArea(int idXo, int idYo); // Левый верхний уг. об.

    // Земля отредактирована:
    //  в области
    void changedMap(int idXo, int idYo, // Левый верхний угол области
                    int dX, int dY);    // Размеры области
    //  полностью
    void changedMap();

    // Процесс про инициализации рельефа
    void startBuildMap();                           // Начался
    void changedProgressBuildMap(int countPercent); // в %
    void finishBuildMap(int W, int L, int H);       // Завершился

public slots:

    // Создать карту
    void initMap(const MapData DataMap,
                 const QString& dirName); //

    // Изменить активную область
    void setPosActionArea(int idXmap, int idYmap); // центр области
    void movePosActionArea(int dX, int dY); // в дискретах карты

    // Актуализировать данные в
    void updateFromRect(int idX, int idY, int w, int h); // Прямоугольнике
    void updateFromRect(const QRect& rect);
    void updateFromRects(QRect* rects, int countS);      // Прямоугольниках

    // Редактирование рельефа
    void upEarth(int idX, int idY, int R);   // Поднять землю
    void downEarth(int idX, int idY, int R); // Опустить землю

    //
    void loadTerrain(const QString& dirNameFile);

    //
    void openMap(const QString& dirNameFile);

public:

    //
    HeightMeter* getHeightMeter() const;

    // Получить интерфейс
    GISInformer* Informer() /* const */;

    // Методы-интерфейс по работе с ГИС:
    int getH(int idX, int idY, Coords::units = Coords::m) const override final;
    Coords getCoords(int idX, int idY) const override final;
    const QImage& getGeoImage() const override final;
    void getIdActionArea(int& idXo, int& idYo) const override final;

    // При инициализации ГИС системы
    GIS();

    //
    ///void setDefaultMap();

private slots:

    //
    void setPosActionAreaDefult();

private:

    //
    bool Enabled;

    //
    void initActionArea(int posX, int posY);

    // Точка, относительно которой формируется
    //  область, не требующая загрузки
    int idXpos, idYpos;       // Левый верхний угол
    const int currentW = 300; // Размеры области
    const int currentH = 300; //  в дискретах

    //
    geoGenerator* geoBuilder;

    //
    painterMapImage* backPainter;
};

#endif // GIS_H
