#ifndef DRAWAREATOOL_H
#define DRAWAREATOOL_H

#include <QMouseEvent>

class drawAreaTool
{
public:
    drawAreaTool();

    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};

    virtual void mousePress(QMouseEvent* mouse) = 0;
    virtual void mouseRelease(QMouseEvent* mouse) = 0;
    virtual void mouseMove(QMouseEvent* mouse) = 0;

private:
    // кнопки
    static int lastKeyMouse;
    static int statMouse;

    // курсор
    static int xPressMouse; // последние координаты нажатия
    static int yPressMouse;
    static int xMouse;      // последние координаты
    static int yMouse;
};

#endif // DRAWAREATOOL_H
