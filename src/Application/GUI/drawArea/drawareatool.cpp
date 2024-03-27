#include "drawareatool.h"

#include "areadrawwidget.h"

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

drawAreaTool::drawAreaTool(areaDrawWidget* area, int id, QObject *parent): drawArea(area), id(id), QObject(parent)
{
    connect(this, SIGNAL(pickSignal(int)),
            drawArea, SLOT(setTool(int)));

    // По умолчанию стандартный курсор для всех инструментов
    cursor = Qt::ArrowCursor;

    button = nullptr;
}

int drawAreaTool::getId() const
{
    return id;
}

QPushButton* drawAreaTool::getButton()
{
    return button;
}

void drawAreaTool::setButton(const QPixmap &pixButton, const QString &nameButton)
{
    button = new QPushButton(pixButton, "");
    button->setToolTip(nameButton);
    button->setIconSize(QSize(23, 23));
    button->setFixedSize(QSize(29, 29));

    connect(button, SIGNAL(clicked()),
            this,   SLOT(assign()));

    offButton();
}

void drawAreaTool::onButton()
{
    button->setStyleSheet("QPushButton{"
                          "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                          "    border-color: rgb(0,0,0);"
                          "    border-style: outset;"
                          "    border-radius: 3px;"
                          "    border-width: 1px;"
                          "}"
                          "QPushButton:hover{"
                          "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                          "    border-color: rgb(0,0,0);"
                          "    border-radius: 3px;"
                          "    border-width: 1px;"
                          "    border-color: rgb(0,0,0);"
                          "}"
                          "QPushButton:pressed{"
                          "    background-color : rgb(143,204,205); color: rgb(0,0,0);;"
                          "};");
}

void drawAreaTool::offButton()
{
    button->setStyleSheet("QPushButton{"
                          "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                          "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                          "    border-style: outset;"
                          "}"
                          "QPushButton:hover{"
                          "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                          "    border-color: rgb(0,0,0);"
                          "    border-style: outset;"
                          "    border-radius: 3px;"
                          "    border-width: 1px;"
                          "    border-color: rgb(0,0,0);"
                          "}"
                          "QPushButton:pressed{"
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
