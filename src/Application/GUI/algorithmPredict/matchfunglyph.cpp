#include "matchfunglyph.h"

matchFunGlyph::matchFunGlyph(QWidget* parent,
                             const QPoint& position, const QSize& size):
    Glyph(parent, position, size)
{
    int W = size.width();
    int H = size.height();

    //
    addPos(QPoint(W - 15 - 30, H - 8), inA);
    insert(new glyphPoint(parent, position), inA);
    addPos(QPoint(W - 15 - 30, H/2-5), lA);
    insert(new LabelGlyph(parent, position, QPixmap(":/resurs/b").scaled(22, 20)), lA);

    addPos(QPoint(15, H - 8), inB);
    insert(new glyphPoint(parent, position), inB);
    addPos(QPoint(15, H/2-5), lB);
    insert(new LabelGlyph(parent, position, QPixmap(":/resurs/a").scaled(22, 20)), lB);

    addPos(QPoint(W - 10, H/2-5), outRes);
    insert(new glyphPoint(parent, position), outRes);
    addPos(QPoint(W - 26, H/2-5), lRes);
    insert(new LabelGlyph(parent, position, QPixmap(":/resurs/equal").scaled(16, 20)), lRes);

    addPos(QPoint((W-30)/2, H/2-5), oper);
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
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        it.value()->draw(painter);
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

    Glyph* g;
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        g = it.value();
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

    Glyph* g;
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        g = it.value();
        if (g->intersects(mouse->pos()))
            g->pressEvent(mouse);
    }
}

void matchFunGlyph::missEvent()
{
    isHover = false;
}


