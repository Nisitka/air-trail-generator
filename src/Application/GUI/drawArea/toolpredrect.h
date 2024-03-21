#ifndef TOOLPREDRECT_H
#define TOOLPREDRECT_H

#include "GUI/drawArea/drawareatool.h"

class ToolPredRect: public drawAreaTool
{
public:
    ToolPredRect(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void drawTask(QPainter& painter) override;

    void init() override;
    void end() override;
};

#endif // TOOLPREDRECT_H
