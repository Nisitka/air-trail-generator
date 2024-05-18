#ifndef TOOLMOVEMAP_H
#define TOOLMOVEMAP_H

#include "GUI/drawArea/Tools/drawareatool.h"

class ToolMoveMap: public drawAreaTool
{
    Q_OBJECT
signals:

    //
    void movedLookArea(double dX, double dY);

public:
    ToolMoveMap(int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void init() override;
    void end() override;

private:

    int dX, dY;
};

#endif // TOOLMOVEMAP_H
