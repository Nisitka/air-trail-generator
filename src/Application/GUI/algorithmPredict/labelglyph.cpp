#include "labelglyph.h"

LabelGlyph::LabelGlyph(QWidget* parent,
                       const QPoint& position,
                       const QPixmap& icon_):
    Glyph(parent, position, icon_.size()),
    icon(icon_)
{

}

void LabelGlyph::draw(QPainter &painter)
{
    painter.drawPixmap(belongRect, icon);
}

void LabelGlyph::pressEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void LabelGlyph::releaseEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void LabelGlyph::missEvent()
{
    /* ... */
}

void LabelGlyph::moveEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void LabelGlyph::hoverEvent(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}
