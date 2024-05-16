#ifndef TOOLDEFAULT_H
#define TOOLDEFAULT_H

#include "GUI/drawArea/Tools/drawareatool.h"

class toolDefault: public drawAreaTool
{
public:
    toolDefault(int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void end() override;
};

#endif // TOOLDEFAULT_H
