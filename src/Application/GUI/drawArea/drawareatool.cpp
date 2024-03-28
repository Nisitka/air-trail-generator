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

QToolButton* drawAreaTool::getButton()
{
    return button;
}

void drawAreaTool::setButton(const QPixmap &pixButton, const QString &nameButton)
{
    button = new QToolButton;
    button->setIcon(pixButton);
    button->setToolTip(nameButton);
    button->setIconSize(QSize(23, 23));
    button->setFixedSize(QSize(29, 29));

    connect(button, SIGNAL(clicked()),
            this,   SLOT(assign()));
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
