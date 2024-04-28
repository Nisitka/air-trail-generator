#ifndef TOOLVISMAP_H
#define TOOLVISMAP_H

#include "GUI/drawArea/drawareatool.h"

class ToolVisMap: public drawAreaTool
{
    Q_OBJECT
signals:
    // Обновить данные об области 3D визуализации
    void updateRect3D(int idXo, int idYo, int numW, int numL);

public:
    ToolVisMap(int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

private:

    drawTask <ToolVisMap>* dTask;
    //
    int idXa = 0;
    int idYa = 0;

    int idXb = 0;
    int idYb = 0;
};

#endif // TOOLVISMAP_H
