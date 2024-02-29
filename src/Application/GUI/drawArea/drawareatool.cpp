#include "drawareatool.h"

#include "areadrawwidget.h"

int drawAreaTool::lastKeyMouse;
int drawAreaTool::statMouse;

int drawAreaTool::xPressMouse;
int drawAreaTool::yPressMouse;
int drawAreaTool::xMouse;
int drawAreaTool::yMouse;
int drawAreaTool::pXo;
int drawAreaTool::pYo;

drawAreaTool::drawAreaTool(areaDrawWidget* area): drawArea(area)
{
    // По умолчанию стандартный курсор для всех инструментов
    cursor = Qt::ArrowCursor;
}

void drawAreaTool::getCoordMouse(int &idX, int &idY)
{
    idX = xMouse;
    idY = yMouse;
}

int drawAreaTool::getStatMouse()
{
    return statMouse;
}

int drawAreaTool::getLastKeyMouse()
{
    return lastKeyMouse;
}

void drawAreaTool::init()
{
    drawArea->setCursor(cursor);
}
