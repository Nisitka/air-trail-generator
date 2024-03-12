#include "drawareatool.h"

#include "areadrawwidget.h"

#include <QDebug>

int drawAreaTool::lastKeyMouse;
int drawAreaTool::statMouse;

int drawAreaTool::xPressMouse;
int drawAreaTool::yPressMouse;
int drawAreaTool::xMouse;
int drawAreaTool::yMouse;
int drawAreaTool::pXo;
int drawAreaTool::pYo;

drawAreaTool::drawAreaTool(areaDrawWidget* area, int id): drawArea(area), id(id)
{
    connect(this, SIGNAL(pickSignal(int)),
            drawArea, SLOT(setTool(int)));

    // По умолчанию стандартный курсор для всех инструментов
    cursor = Qt::ArrowCursor;
}

void drawAreaTool::addButton(const QPixmap &pixButton, const QString &nameButton)
{
    qDebug() << "ASAS";

    drawArea->getToolBar()->addAction(pixButton, nameButton,
                                      this,      SLOT(assign()));
}

void drawAreaTool::assign()
{
    pickSignal(id);
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

void drawAreaTool::getCoordID(int &idX, int &idY)
{
    /* ... */
}
