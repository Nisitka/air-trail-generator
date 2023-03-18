#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>

#include <QPushButton>

#include "areadrawwidget.h"
#include "map.h"

namespace Ui {
class visualInfoWidget;
}

class visualInfoWidget : public QWidget
{
    Q_OBJECT
signals:
    void updateCoordRLS(int x, int y);

    void saveMap_signal(const QString& dirFile);

    void setRectPredict(int idXo, int idYo); // дискрета левого верхнего угла

    void setPointsTrail(QPoint begin, QPoint last);

public slots:
    void updateImage();

    //
    void setResultPredictRect(int idX, int idY);

    // обновить размеры окна для отрисовки
    void updateSizeDrawArea();

    // вычисляем координаты левего верхнего угла квадрата для прогнозирования
    // и информируем об этом объекты (которым эта инфо. нужна)
    void setIdCoordsRectPredict(int idX, int idY);

    // начать прогноз траектории
    void startPredictTrail();

    // завершение прогноза траектории
    void readyPredictTrail();

public:
    explicit visualInfoWidget(QImage* geoMap,
                              QImage* dataNet,
                              QImage* QFun,
                              Map* map,
                              QWidget *parent = 0);

    ~visualInfoWidget();

protected:
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent);

private slots:
    void saveMap();

    void showInfoCoord(double x, double y);
    void switchVisual(int idType);

    void saveImage();

    void setDirImg();

    // установка инструментов
    void setToolRLS();
    void setToolMoveImg();
    void setToolZoom();
    void setToolPredictRect();
    void setToolPredictTrail();

private:
    //
    bool isPredictTrail;

    // опции сохранения изображения
    enum optSaveImg{screen, full, curRect}; // скирншот, всю карту, выделенную область
    QStringList typeSaveImg = {"сриншот", "всю карту", "выд. область"};

    // названия форматов изображений
    QString formatsImg = "*.png ;; *.jpg ;; *.bmp";

    // выбранный формат для сохранения
    QString curFormat;

    // карта (рельеф)
    Map* map;

    // виджет, на котором будет происходить отрисовка изоб.
    areaDrawWidget* drawArea;

    // типы изображений
    QStringList strTypeVisual = {"Рельеф",
                                 "Образ нейронной сети",
                                 "Целевую функцию"};

    QPushButton* lastButtonTool;

    Ui::visualInfoWidget *ui;
};

#endif // VISUALINFOWIDGET_H
