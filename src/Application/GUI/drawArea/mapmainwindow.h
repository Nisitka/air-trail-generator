#ifndef MAPMAINWINDOW_H
#define MAPMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>

#include "../designer.h"

#include "areadrawwidget.h"

class mapMainWindow: public QMainWindow
{
    Q_OBJECT
public:
    mapMainWindow(QImage* mapImg, Map* map);

    areaDrawWidget* getDrawArea();

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

    // Выбрать инструмент
    void setTool(int id);

    //
    void movePosLookMap(double dX, double dY);

protected:

    // Переопределяем метод, чтоб не вылазило меню при нажатии лев.клавиши мыши
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:

    //
    void updateCoord(const QString& coordsData);

    //
    void changeTool();
    void changeToolGroup();

    void updateStyleToolButtons(QToolButton* changeButton);

private:

    //
    QStatusBar* statusBar;
    QLabel* coordLabel;

    //
    QScrollArea* scrollArea;

    //
    QMap <QObject*, int> objToKeyTool;

    areaDrawWidget* area;

    QToolButton* lastToolButton;
    void setButtonStyle(QToolButton*, StyleButtonTool style);

    // Панель для инструментов
    QToolBar* toolBar;

    // Все инструменты
    QMap <int, drawAreaTool*> Tools;

    // Текущий инструмент
    drawAreaTool* Tool;
    int keyCurTool;
    int lastKeyTool;
};

#endif // MAPMAINWINDOW_H
