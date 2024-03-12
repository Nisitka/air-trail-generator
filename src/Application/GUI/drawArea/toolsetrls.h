#ifndef TOOLSETRLS_H
#define TOOLSETRLS_H

#include "GUI/drawArea/drawareatool.h"

class ToolSetRLS: public drawAreaTool
{
public:
    ToolSetRLS(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void init() override;
    void end() override;
};

#endif // TOOLSETRLS_H
