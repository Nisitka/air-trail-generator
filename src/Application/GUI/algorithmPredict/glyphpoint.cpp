#include "glyphpoint.h"

glyphPoint::glyphPoint(QWidget* parent,
                       const QPoint& position, int R):
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
    Q_UNUSED(mouse);

    color = QColor(193,254,255);
}

void glyphPoint::pressEvent(QMouseEvent *mouse)
{
    Xpress = mouse->x() - belongRect.x();
    Ypress = mouse->y() - belongRect.y();

    /// Для теста! (глиф удаляется из программы)
    //killMe(this);
}

void glyphPoint::missEvent()
{
    color = Qt::white;
}
