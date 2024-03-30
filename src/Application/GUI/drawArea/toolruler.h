#ifndef TOOLRULER_H
#define TOOLRULER_H

#include "GUI/drawArea/drawareatool.h"

class ToolRuler: public drawAreaTool
{
    Q_OBJECT
public:
    ToolRuler(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

private:
    //
    drawTask<ToolRuler>* dTask;

    int Xmeas, Ymeas;
};

#endif // TOOLRULER_H
