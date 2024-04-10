#include "matchfunglyph.h"

matchFunGlyph::matchFunGlyph(QWidget* parent, const QPoint& position, const QSize& size):
    Glyph(parent, position, size)
{
    int W = size.width();
    int H = size.height();

    //
    addPos(QPoint(6, 10), A);
    insert(new glyphPoint(parent, position), A);

    addPos(QPoint(6, H - 10), B);
    insert(new glyphPoint(parent, position), B);

    addPos(QPoint(W - 3, 30), result);
    insert(new glyphPoint(parent, position), result);

    addPos(QPoint(W/2, H/2), oper);
    insert(new matchOperGlyph(parent, position), oper);

    //
    isHover = false;
}

void matchFunGlyph::draw(QPainter &painter)
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

    if (isHover)
    {
        painter.setPen(QColor(84,123,177,180));
        painter.setBrush(Qt::NoBrush);

        QPoint pos = belongRect.topLeft() - QPoint(3, 3);
        painter.drawRect(pos.x(), pos.y(),
                         belongRect.width() + 6, belongRect.height() + 6);
    }
}

void matchFunGlyph::hoverEvent(QMouseEvent* mouse)
{
    isHover = true;

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

void matchFunGlyph::pressEvent(QMouseEvent *mouse)
{
    Xpress = mouse->x() - belongRect.x();
    Ypress = mouse->y() - belongRect.y();

    int countChild = childGlyphs.size();
    Glyph* g;
    for (int i=0; i<countChild; i++)
    {
        g = childGlyphs[i];
        if (g->intersects(mouse->pos()))
            g->pressEvent(mouse);
    }
}

void matchFunGlyph::missEvent()
{
    isHover = false;
}


