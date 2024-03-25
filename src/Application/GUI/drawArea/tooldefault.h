#ifndef TOOLDEFAULT_H
#define TOOLDEFAULT_H

#include "GUI/drawArea/drawareatool.h"

class toolDefault: public drawAreaTool
{
public:
    toolDefault(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask(QPainter& painter) override;

    void end() override;
};

#endif // TOOLDEFAULT_H
