#include "glyph.h"

#include <QDebug>

Glyph::Glyph(QWidget* parent, const QPoint& pos, const QSize& size):
    parent(parent)
{
    //
    belongRect = QRect(pos, size);

    sizeRect = size;

    borderColor = Qt::black;
}

bool Glyph::intersects(const QPoint &mousePos) const
{
    return belongRect.contains(mousePos);
}

void Glyph::insert(Glyph *g, int idPos)
{
    childGlyphs.append(g);
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
        childGlyphs.at(i)->draw(painter);
    }
}

void Glyph::hoverEvent()
{
    borderColor = Qt::red;
}

void Glyph::missEvent()
{
    borderColor = Qt::black;
}

void Glyph::pressEvent(QMouseEvent* mouse)
{
    Xpress = mouse->x() - belongRect.x();
    Ypress = mouse->y() - belongRect.y();
}

void Glyph::releaseEvent(QMouseEvent* mouse)
{

}

void Glyph::moveEvent(QMouseEvent *mouse)
{
    belongRect.moveTo(mouse->x() - Xpress,
                      mouse->y() - Ypress);
}
