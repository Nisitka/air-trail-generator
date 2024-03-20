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
    QAction* action = drawArea->getToolBar()->addAction(pixButton, nameButton,
                                      this,      SLOT(assign()));

    button = drawArea->getToolBar()->widgetForAction(action);
    offButton();
}

void drawAreaTool::onButton()
{
    button->setStyleSheet("QToolButton{"
                          "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                          "    border-color: rgb(0,0,0);"
                          "    border-style: outset;"
                          "    border-radius: 3px;"
                          "    border-width: 1px;"
                          "    border-color: rgb(0,0,0);"
                          "}"
                          "QToolButton:hover{"
                          "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                          "    border-color: rgb(0,0,0);"
                          "    border-radius: 3px;"
                          "    border-width: 1px;"
                          "    border-color: rgb(0,0,0);"
                          "}"
                          "QToolButton:pressed{"
                          "    background-color : rgb(143,204,205); color: rgb(0,0,0);;"
                          "};");
}

void drawAreaTool::offButton()
{
    button->setStyleSheet("QToolButton{"
                          "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                          "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                          "}"
                          "QToolButton:hover{"
                          "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                          "    border-color: rgb(0,0,0);"
                          "    border-style: outset;"
                          "    border-radius: 3px;"
                          "    border-width: 1px;"
                          "    border-color: rgb(0,0,0);"
                          "}"
                          "QToolButton:pressed{"
                          "    background-color : rgb(143,204,205); color: rgb(0,0,0);;"
                          "};");
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
