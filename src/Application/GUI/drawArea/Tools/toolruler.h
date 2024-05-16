#ifndef TOOLRULER_H
#define TOOLRULER_H

#include "GUI/drawArea/Tools/drawareatool.h"

class ToolRuler: public drawAreaTool
{
    Q_OBJECT
public:
    ToolRuler(int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

private:
    //
    drawTask<ToolRuler>* dTask;

    float distance(int Xa, int Ya, int Xb, int Yb);

    bool checkDraw = false;

    // Координаты измерения (в pix)
    int Xb, Yb;       // начало
    int Xmeas, Ymeas; // конец


};

#endif // TOOLRULER_H
