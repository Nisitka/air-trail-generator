#ifndef TOOLSQUARETER_H
#define TOOLSQUARETER_H

#include "GUI/drawArea/drawareatool.h"

class ToolSquareTer: public drawAreaTool
{
    Q_OBJECT
public:
    ToolSquareTer(int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

private:
    //
    drawTask<ToolSquareTer>* dTask;

    float squarePolygon();
    float checkLine(const QPoint &p1, const QPoint &p2);

    QPolygon polygon;

};

#endif // TOOLSQUARETER_H
