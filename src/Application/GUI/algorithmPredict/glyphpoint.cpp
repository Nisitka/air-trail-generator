#include "glyphpoint.h"

glyphPoint::glyphPoint(QWidget* parent, const QPoint& position, int R):
    Glyph(parent, position, QSize(R*2, R*2)), R(R)
{
    color = Qt::white;
}

void glyphPoint::draw(QPainter &painter)
{
    painter.setPen(borderColor);
    painter.setBrush(color);

    painter.drawEllipse(belongRect);

}

void glyphPoint::hoverEvent(QMouseEvent *mouse)
{
    color = QColor(193,254,255);
}

void glyphPoint::missEvent()
{
    color = Qt::white;
}
