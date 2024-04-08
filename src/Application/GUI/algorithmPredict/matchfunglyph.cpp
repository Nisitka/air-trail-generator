#include "matchfunglyph.h"

matchFunGlyph::matchFunGlyph(QWidget* parent, const QPoint& position, const QSize& size):
    Glyph(parent, position, size)
{
    int W = size.width();
    int H = size.height();

    posGlyphs[A] = QPoint(6, 10);
    posGlyphs[B] = QPoint(6, H - 10);
    posGlyphs[result] = QPoint(W - 7, 30);

    Glyph* g;
    for (int i=0; i<posGlyphs.size(); i++)
    {
        g = new glyphPoint(parent, position);
        g->move(position + posGlyphs[i]);

        insert(g, i);
    }

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

void matchFunGlyph::missEvent()
{
    isHover = false;
}


