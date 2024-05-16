#include "drawareatool.h"

#include "../areadrawwidget.h"

#include <QDebug>

int drawAreaTool::lastKeyMouse;
int drawAreaTool::statMouse;

int drawAreaTool::xPressMouse;
int drawAreaTool::yPressMouse;
int drawAreaTool::xMouse;
int drawAreaTool::yMouse;
int drawAreaTool::xIdMouse;
int drawAreaTool::yIdMouse;
int drawAreaTool::pXo;
int drawAreaTool::pYo;

drawAreaTool::drawAreaTool(int id, QObject *parent): id(id), QObject(parent)
{
    // По умолчанию стандартный курсор для всех инструментов
    cursor = Qt::ArrowCursor;

    //
    selected = false;
}

void drawAreaTool::setDrawArea(areaDrawWidget *area)
{
    drawArea = area;
}

void drawAreaTool::setCursor()
{
    drawArea->setCursor(cursor);
}

int drawAreaTool::getId() const
{
    return id;
}

void drawAreaTool::setParButton(const QPixmap &pixButton, const QString &nButton)
{
    imgButton = pixButton;
    nameTool = nButton;
}

QPixmap drawAreaTool::getImgButton() const
{
    return imgButton;
}

QString drawAreaTool::getNameTool() const
{
    return nameTool;
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

void drawAreaTool::wheelEvent(QWheelEvent *event)
{
    /* По умолчанию ничего не делаем */
}
