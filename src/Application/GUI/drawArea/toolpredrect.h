#ifndef TOOLPREDRECT_H
#define TOOLPREDRECT_H

#include "GUI/drawArea/drawareatool.h"

class ToolPredRect: public drawAreaTool
{
public:
    ToolPredRect(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask(QPainter& painter) override;

    void init() override;
    void end() override;

private:

    // Индексы левого верхнего угла квадрата прогноза
    int idXoPredict;
    int idYoPredict;

    // Индексы дискрет центра квадрата прогноза
    int idXRect;
    int idYRect;

    // Результаты прогноза в квадрате
    int idPRectX;
    int idPRectY;

    // Рисовать ли сейчас прогноз
    bool drawLineRect = false;

    drawTask <ToolPredRect>* dTask;
};

#endif // TOOLPREDRECT_H
