#ifndef VISUALINFOWIDGET_H
#define VISUALINFOWIDGET_H

#include <QWidget>

#include <QPushButton>

#include "drawArea/areadrawwidget.h"
//#include "backend/map.h"

namespace Ui {
class visualInfoWidget;
}

class visualInfoWidget : public QWidget
{
    Q_OBJECT
signals:  
    void saveMap_signal(const QString& dirFile);

    void setRectPredict(int idXo, int idYo); // дискрета левого верхнего угла

    void setPointsTrail(QPoint begin, QPoint last);

public slots:
    // установить выбранную РЛС
    void setCurRLS(int idRLS);

    // добавить РЛС для отрисовки на карте
    void addRLS(QPoint* posRLS, const QString& nameNewRLS);

    // удалить РЛС с отрисовки
    void delRLS(int indexRLS);

    //
    void updateImage();

public:
    explicit visualInfoWidget(QImage* geoMap,
                              Map* map,
                              QWidget *parent = 0);

    areaDrawWidget* getDrawArea();

    ~visualInfoWidget();

private slots:

    //
    void switchVisual(int idType);

private:
    // настройка визуала
    void setDesine();

    // прогнозируется ли сейчас траектория
    bool isPredictTrail;
    //
    int sizeFilter = 2;
    int numCurPoint;

    // карта (рельеф)
    Map* map;

    // виджет, на котором будет происходить отрисовка изоб.
    areaDrawWidget* drawArea;

    // типы изображений
    QStringList strTypeVisual = {"Физическая",
                                 "Спутниковый снимок",
                                 "Схематичная"};

    Ui::visualInfoWidget *ui;
};

#endif // VISUALINFOWIDGET_H
