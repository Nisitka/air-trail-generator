#ifndef TOOLSQUARETER_H
#define TOOLSQUARETER_H

#include "GUI/drawArea/drawareatool.h"

class ToolSquareTer: public drawAreaTool
{
    Q_OBJECT
public:
    ToolSquareTer(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

private:
    //
    drawTask<ToolSquareTer>* dTask;

};

#endif // TOOLSQUARETER_H
