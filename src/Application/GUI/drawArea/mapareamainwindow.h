#ifndef MAPAREAMAINWINDOW_H
#define MAPAREAMAINWINDOW_H

#include <QMainWindow>

#include <QSlider>

#include "../3DVisualization/map3dviswindow.h"

#include "../designer.h"
#include "areadrawwidget.h"
#include "scrollmapwidget.h"

#include "backend/GIS/gisinformer.h"

namespace Ui {
class mapAreaMainWindow;
}

class mapAreaMainWindow : public MultipleWindow/*public QMainWindow*/
{
    Q_OBJECT

signals:

    //
    void moveActionArea(int dX, int dY);

public:
    explicit mapAreaMainWindow(GISInformer* gis,
                               painterMapImage* mapImgGenerator,
                               QWidget *parent = 0);
    ~mapAreaMainWindow();

    areaDrawWidget* getDrawArea();

    //
    void setLockStatus();

    //
    void setDefStatus();

    // Добавить инструмент
    void appendTool(drawAreaTool* toolArea);
    // Добавить грппу инструментов
    void appendToolGroup(const QVector <drawAreaTool*>&,
                         const QString& nameGroup);

    // Инструменты
    int curTool();
    enum tools{moveImg, setRLS, zoomImg, predictRect, predictTrail,
               mapVis, editEarth, Ruler, squareTer, def};

    enum StyleButtonTool {on, off};

    //
    bool eventFilter(QObject* /*obj*/, QEvent* evt) override;

public slots:

    //
    void setNewActionArea(int idXo, int idYo);

    // Выбрать инструмент
    void setTool(int id);

    // Обновить все пар-ы изображения карты
    void updateGeoMapImage();

    //
    void repaintBackground();

protected:

    void paintEvent(QPaintEvent* event) override;

    // Переопределяем метод, чтоб не вылазило меню при нажатии лев.клавиши мыши
    void contextMenuEvent(QContextMenuEvent* event) override;

    //
    void wheelEvent(QWheelEvent* event) override;

    //
    void resizeEvent(QResizeEvent* event);

private slots:

    //
    void changeTool();
    void changeToolGroup();

    void updateStyleToolButtons(QToolButton* changeButton);

    //
    void updateCoord(const Coords coords);

private:

    //
    GISInformer* gis;

    //
    ScrollMapWidget* scrollArea;

    //
    CoordsInfoForm* coordLabel;

    //
    areaDrawWidget* area;

    //
    map3DVisWindow* map3DWin;

    QToolButton* lastToolButton;
    void setButtonStyle(QToolButton*, StyleButtonTool style);

    // Панель для инструментов
    QToolBar* toolBar;

    // Все инструменты
    QMap <int, drawAreaTool*> Tools;

    //
    QMap <QObject*, int> objToKeyTool;

    // Текущий инструмент
    drawAreaTool* Tool;
    int keyCurTool;
    int lastKeyTool;

    Ui::mapAreaMainWindow *ui;
};

#endif // MAPAREAMAINWINDOW_H
