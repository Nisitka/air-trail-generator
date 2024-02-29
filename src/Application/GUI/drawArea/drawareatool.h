#ifndef DRAWAREATOOL_H
#define DRAWAREATOOL_H

#include <QMouseEvent>
#include <QCursor>

class areaDrawWidget;

class drawAreaTool
{
public:
    drawAreaTool(areaDrawWidget*);

    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};

    virtual void mousePress(QMouseEvent* mouse) = 0;
    virtual void mouseRelease(QMouseEvent* mouse) = 0;
    virtual void mouseMove(QMouseEvent* mouse) = 0;

    virtual void init();
    virtual void end() = 0;

    void getCoordMouse(int& idX, int& idY);

    int getStatMouse();
    int getLastKeyMouse();

protected:
    // кнопки
    static int lastKeyMouse;
    static int statMouse;

    // курсор
    static int xPressMouse; // последние координаты нажатия
    static int yPressMouse;
    static int xMouse;      // последние координаты
    static int yMouse;
    static int pXo;         // левый верх-й угол карты при нажатии/отпускании мыши
    static int pYo;

    // к чему принадлежат инструменты
    areaDrawWidget* drawArea;

    //
    QCursor cursor;

private:

};

#endif // DRAWAREATOOL_H
