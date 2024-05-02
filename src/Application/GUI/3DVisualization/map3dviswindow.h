#ifndef MAP3DVISWINDOW_H
#define MAP3DVISWINDOW_H

#include <QPushButton>
#include <QVector3D>

#include "backend/gis/map.h"
#include "mapopenglwidget.h"

#include "GUI/designer.h"
#include "GUI/processtmpwidget.h"
#include "GUI/multiplewindow.h"

namespace Ui {
class map3DVisWindow;
}

class map3DVisWindow : public MultipleWindow
{
    Q_OBJECT
signals:
    void generateMap3D();

public slots:
    // Установить зону отображения по умолчанию
    void setVisRectDef();

    // Установить зону отображения
    void setVisRect(int idXo, int idYo,
                    int W,    int L);

    // Обновить данные по рельефу и отредерить по новой
    void updateMap3D(int idXo, int idYo,
                     int W,    int L); //
    void updateMap3D(); // обновить все

    //
    void updatePointsInterZD(QVector <QVector <QVector <QVector3D>>>* pZD, QList <QVector3D>* posRLS);

public:
    explicit map3DVisWindow(QImage* imgTex);
    ~map3DVisWindow();

    mapOpenGLWidget* getGraphicsWidget();

    enum StyleButtonTool {on, off};

private slots:

private:

    // Виджет загрузки
    processTmpWidget* loadingLabel;

    //
    Map* map;
    mapOpenGLWidget* visMap;

    Ui::map3DVisWindow *ui;
};

#endif // MAP3DVISWINDOW_H
