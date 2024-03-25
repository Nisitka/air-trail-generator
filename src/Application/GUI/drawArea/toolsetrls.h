#ifndef TOOLSETRLS_H
#define TOOLSETRLS_H

#include "GUI/drawArea/drawareatool.h"

class ToolSetRLS: public drawAreaTool
{
    Q_OBJECT
signals:

    // Установить РЛС
    void setCoordRLS(int x, int y);

public:
    ToolSetRLS(areaDrawWidget*, int id);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask(QPainter& painter) override;

    void init() override;
    void end() override;

    // изменить точку постановки РЛС
    void setMarkCoordRLS();

private:
    //
    drawTask<ToolSetRLS>* dTask;

    // позиция РЛС на окне
    int xPosRLS;
    int yPosRLS;
};

#endif // TOOLSETRLS_H
