#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>

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

public slots:
    void updateImage();

    // обновить размеры окна для отрисовки
    void updateSizeDrawArea();

public:
    explicit visualInfoWidget(QImage* geoMap,
                              QImage* dataNet,
                              QImage* QFun,
                              Map* map,
                              QWidget *parent = 0);

    ~visualInfoWidget();

private slots:
    void showInfoCoord(double x, double y);
    void switchVisual(int idType);

    void saveImage();

    void setDirImg();

private:
    // названия форматов изображений
    QString formatsImg = "*.png ;; *.jpg ;; *.bmp";

    // выбранный формат для сохранения
    QString curFormat;

    // карта (рельеф)
    Map* map;

    // виджет, на котором будет происходить отрисовка изоб.
    areaDrawWidget* drawArea;

    // типы изображений
    QStringList strTypeVisual = {"Исходные данные",
                                 "Образ нейронной сети",
                                 "Целевую функцию"};

    Ui::visualInfoWidget *ui;
};

#endif // VISUALINFOWIDGET_H
