#ifndef TOOLMOVEMAP_H
#define TOOLMOVEMAP_H

#include "GUI/drawArea/drawareatool.h"

class ToolMoveMap: public drawAreaTool
{
public:
    ToolMoveMap(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void init() override;
    void end() override;
};

#endif // TOOLMOVEMAP_H
