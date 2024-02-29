#ifndef TOOLPREDTRAIL_H
#define TOOLPREDTRAIL_H

#include "GUI/drawArea/drawareatool.h"

class ToolPredTrail: public drawAreaTool
{
public:
    ToolPredTrail(areaDrawWidget*);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void init() override;
    void end() override;
};

#endif // TOOLPREDTRAIL_H
