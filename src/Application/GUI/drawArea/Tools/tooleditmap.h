#ifndef TOOLEDITMAP_H
#define TOOLEDITMAP_H

#include "GUI/drawArea/Tools/drawareatool.h"

#include <QWheelEvent>
#include <QPixmap>

#include <QTimer>

class ToolEditMap: public drawAreaTool
{
    Q_OBJECT
signals:
    // Поднять землю в указанной области
    void upEarth(int idX, int idY, int R);

    // Опустить землю в указанной области
    void downEarth(int idX, int idY, int R);

public:
    ToolEditMap(int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;
    void wheelEvent(QWheelEvent *event) override;

    void init() override;
    void end() override;

private slots:
    //
    void editEarth();

private:

    //
    void updateSizeCursor();

    QPixmap upCurPixmap;
    QPixmap downCurPixmap;
    QPixmap moveCurPixmap;

    //
    QTimer* timer;

    // Размер кисти
    int r;
    int R; // размер курсора инструмента

    int const minSIZE = 4;
    int const maxSIZE = 40;
};

#endif // TOOLEDITMAP_H
