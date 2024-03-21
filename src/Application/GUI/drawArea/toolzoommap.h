#ifndef TOOLZOOMMAP_H
#define TOOLZOOMMAP_H

#include "GUI/drawArea/drawareatool.h"

class ToolZoomMap: public drawAreaTool
{
public:
    ToolZoomMap(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void drawTask(QPainter& painter) override;

    void init() override;
    void end() override;

private:
    //
    const double dK = 0.2;
};

#endif // TOOLZOOMMAP_H
