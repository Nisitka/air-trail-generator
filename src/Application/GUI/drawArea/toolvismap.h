#ifndef TOOLVISMAP_H
#define TOOLVISMAP_H

#include "GUI/drawArea/drawareatool.h"

class ToolVisMap: public drawAreaTool
{
    Q_OBJECT
signals:
    // обновить данные об области 3D визуализации
    void updateRect3D(int idXo, int idYo, int numW, int numL);

public:
    ToolVisMap(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask(QPainter& painter) override;

    void init() override;
    void end() override;

private:

    drawTask <ToolVisMap>* dTask;
    //
    int idXa;
    int idYa;

    int idXb;
    int idYb;
};

#endif // TOOLVISMAP_H
