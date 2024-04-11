#include "lineglyph.h"

#include <QDebug>

LineGlyph::LineGlyph(QWidget* parent, Glyph* pA, Glyph* pB):
    Glyph(parent), pA(pA), pB(pB)
{

}

void LineGlyph::draw(QPainter &painter)
{
    painter.setPen(borderColor);

    // Сама линия
    painter.drawLine(pA->center(), pB->center());

    // Чтоб линия была всегда под глифом
    pA->draw(painter);
    pB->draw(painter);
}

bool LineGlyph::intersects(const QPoint &mousePos) const
{
    int Xo = mousePos.x();
    int Yo = mousePos.y();

    int x1 = pA->center().x();
    int x2 = pB->center().x();

    int y1 = pA->center().y();
    int y2 = pB->center().y();

    // Если курсор не между точками
    if ((Xo < x1 && Xo < x2) |
        (Yo < y1 && Yo < y2) |
        (Xo > x1 && Xo > x2) |
        (Yo > y1 && Yo > y2)) return false;

    int dX = x2 - x1;
    int dY = y2 - y1;

    double d = ((double)(Xo - x1) / dX) - ((double)(Yo - y1) / dY);
    if (fabs(d) < 0.1)
        return true;

    return false;
}


