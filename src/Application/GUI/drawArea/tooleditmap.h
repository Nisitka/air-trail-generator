#ifndef TOOLEDITMAP_H
#define TOOLEDITMAP_H

#include "GUI/drawArea/drawareatool.h"

class ToolEditMap: public drawAreaTool
{
public:
    ToolEditMap(areaDrawWidget*);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void init() override;
    void end() override;

private:
    //
    void editEarth();

    //
    int r;
};

#endif // TOOLEDITMAP_H
