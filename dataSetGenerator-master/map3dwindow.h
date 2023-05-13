#ifndef MAP3DWINDOW_H
#define MAP3DWINDOW_H

#include <QWidget>

#include "visualmap3d.h"
#include "volumetric.h"

#include "map.h"

namespace Ui {
class map3DWindow;
}

class map3DWindow : public QWidget
{
    Q_OBJECT
signals:
    void generateMap3D();

public slots:
    // завершение подготовки данных для отображения 3D карты
    void finishBuildMap(int idXo, int idYo, int numW, int numL);

public:
    explicit map3DWindow(Map* map_, QWidget *parent = 0);
    ~map3DWindow();

private:
    void setMap(int idXo, int idYo, int numW, int numL);

    void setAreaZD(int idXo, int idYo, int numW, int numL);

    Map* map;

    Ui::map3DWindow *ui;

    visualMap3D* visMap;
    VolumetricModifier* modifier;

    QLabel* colorLabel;
    QWidget* widgetArea1;
    QCheckBox* textureCheckBox;

    QWidget* widgetArea2;
};

#endif // MAP3DWINDOW_H
