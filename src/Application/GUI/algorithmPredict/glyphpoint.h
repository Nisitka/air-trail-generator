#ifndef GLYPHPOINT_H
#define GLYPHPOINT_H

#include "glyph.h"

class glyphPoint: public Glyph
{
public:
    glyphPoint(QWidget* parent,
               const QPoint& position, int R = 5);

protected:

    void draw(QPainter &painter) override;

    void hoverEvent(QMouseEvent* mouse) override;

    void pressEvent(QMouseEvent* mouse) override;

    void missEvent() override;

private:

    //
    QColor color;

    //
    int R;
};

#endif // GLYPHPOINT_H
