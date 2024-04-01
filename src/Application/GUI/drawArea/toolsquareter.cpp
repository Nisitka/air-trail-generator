#include "toolsquareter.h"

ToolSquareTer::ToolSquareTer(areaDrawWidget* area, int id): drawAreaTool(area, id)
{
    setParButton(QPixmap(":/resurs/polygon"), "Площадь области");

    dTask = new drawTask<ToolSquareTer>(this, &ToolSquareTer::procDrawTask);
}

void ToolSquareTer::init()
{

}

void ToolSquareTer::mousePress(QMouseEvent *mouse)
{

}

void ToolSquareTer::mouseRelease(QMouseEvent *mouse)
{

}

void ToolSquareTer::mouseMove(QMouseEvent *mouse)
{

}

void ToolSquareTer::procDrawTask()
{

}

void ToolSquareTer::end()
{

}
