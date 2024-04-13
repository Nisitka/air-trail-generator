#include "operationglyph.h"

#include <QDebug>

operationGlyph::operationGlyph(QWidget* parent,
                               const QPoint& position, const QSize& size):
    Glyph(parent, position, size)
{
    //
    countOper = 0;

    //
    checkListWindow = new QComboBox(parent);
    connect(checkListWindow, SIGNAL(currentIndexChanged(int)),
            this,            SLOT(selectOperation(int)));

    checkListWindow->setWindowFlags(Qt::FramelessWindowHint);
    checkListWindow->setFixedWidth(size.width()*2);
    checkListWindow->setFixedHeight(size.height()+4);
    checkListWindow->hide();
}

int operationGlyph::currentOperation() const
{
    return curOperKey;
}

void operationGlyph::addOperation(int key, const QIcon& icon)
{
    countOper++;

    operPixIcons[key] = icon.pixmap(size).scaled(size).toImage();
    idToKey[countOper-1] = key;

    checkListWindow->addItem(icon, nullptr);
}

void operationGlyph::draw(QPainter &painter)
{
    if (isHover) painter.setPen(QColor(84,123,177,150));
    else painter.setPen(Qt::NoPen);

    painter.setBrush(Qt::NoBrush);
    painter.drawImage(belongRect, curOperIcon);

    painter.drawRect(belongRect);
}

void operationGlyph::hoverEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    isHover = true;
}

void operationGlyph::selectOperation(int id)
{
    checkListWindow->hide();

    curOperKey = idToKey[id];
    curOperIcon = operPixIcons[curOperKey];

    missEvent();
    Parent->repaint();
}

void operationGlyph::pressEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    checkListWindow->hide();
}

void operationGlyph::releaseEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);

    checkListWindow->move(belongRect.topLeft());
    checkListWindow->show();
}

void operationGlyph::moveEvent(QMouseEvent *mouse)
{
    int newX = mouse->x() - Xpress;
    int newY = mouse->y() - Ypress;

    belongRect.moveTo(newX, newY);
}

void operationGlyph::missEvent()
{
    isHover = false;

    borderColor = Qt::black;

    checkListWindow->hide();
}
