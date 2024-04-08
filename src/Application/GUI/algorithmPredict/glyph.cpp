#include "glyph.h"

#include <QDebug>

Glyph::Glyph(QWidget* parent, const QPoint& pos, const QSize& size):
    parent(parent)
{
    //
    belongRect = QRect(pos, size);


    borderColor = Qt::black;
}

bool Glyph::intersects(const QPoint &mousePos) const
{
    return belongRect.contains(mousePos);
}

void Glyph::insert(Glyph *g, int idPos)
{
    childGlyphs[idPos] = g;
}

void Glyph::draw(QPainter &painter)
{
    painter.setPen(borderColor);
    painter.setBrush(Qt::white);

    painter.drawRect(belongRect);

    // Рисуем всех свои остальные глифы
    int countChild = childGlyphs.size();
    for (int i=0; i<countChild; i++)
    {
        childGlyphs[i]->draw(painter);
    }
}

void Glyph::hoverEvent(QMouseEvent* mouse)
{
    borderColor = Qt::red;

    int countChild = childGlyphs.size();
    Glyph* g;
    for (int i=0; i<countChild; i++)
    {
        g = childGlyphs[i];
        if (g->intersects(mouse->pos()))
            g->hoverEvent(mouse);
        else
            g->missEvent();
    }
}

void Glyph::missEvent()
{
    borderColor = Qt::black;

    //
    int countChild = childGlyphs.size();
    for (int i=0; i<countChild; i++)
    {
        childGlyphs[i]->missEvent();
    }
}

void Glyph::pressEvent(QMouseEvent* mouse)
{
    Xpress = mouse->x() - belongRect.x();
    Ypress = mouse->y() - belongRect.y();
}

void Glyph::releaseEvent(QMouseEvent* mouse)
{
    int countChild = childGlyphs.size();
    for (int i=0; i<countChild; i++)
    {
        childGlyphs[i]->releaseEvent(mouse);
    }
}

void Glyph::moveEvent(QMouseEvent *mouse)
{
    int newX = mouse->x() - Xpress;
    int newY = mouse->y() - Ypress;

    belongRect.moveTo(newX, newY);

    //
    int countChild = childGlyphs.size();
    for (int i=0; i<countChild; i++)
    {
        childGlyphs[i]->move(QPoint(newX, newY) + posGlyphs[i]);
    }
}

void Glyph::move(const QPoint& p)
{
    belongRect.moveCenter(p);
}
