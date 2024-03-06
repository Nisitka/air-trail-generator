#ifndef TOOLVISMAP_H
#define TOOLVISMAP_H

#include "GUI/drawArea/drawareatool.h"

class ToolVisMap: public drawAreaTool
{
public:
    ToolVisMap(areaDrawWidget*);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void init() override;
    void end() override;

private:
    //
    int idXa;
    int idYa;

    int idXb;
    int idYb;
};

#endif // TOOLVISMAP_H
