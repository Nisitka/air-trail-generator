#include "matchfunglyph.h"

matchFunGlyph::matchFunGlyph(QWidget* parent, const QPoint& position, const QSize& size):
    Glyph(parent, position, size)
{
    int W = size.width();
    int H = size.height();

    Glyph* g;

    posGlyphs[A] = QPoint(6, 10);
    g = new glyphPoint(parent, position);
    g->move(position + posGlyphs[A]);
    insert(g, A);

    posGlyphs[B] = QPoint(6, H - 10);
    g = new glyphPoint(parent, position);
    g->move(position + posGlyphs[B]);
    insert(g, B);

    posGlyphs[result] = QPoint(W - 3, 30);
    g = new glyphPoint(parent, position);
    g->move(position + posGlyphs[result]);
    insert(g, result);

    posGlyphs[oper] = QPoint(W/2, H/2);
    g = new matchOperGlyph(parent, position);
    g->move(position + posGlyphs[oper]);
    insert(g, oper);

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


