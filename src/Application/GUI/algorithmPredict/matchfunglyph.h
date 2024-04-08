#ifndef MATCHFUNGLYPH_H
#define MATCHFUNGLYPH_H

#include "glyphpoint.h"

class matchFunGlyph: public Glyph
{
public:
    matchFunGlyph(QWidget* parent,
                  const QPoint& position, const QSize& size = QSize(40, 60));

    enum pos{A, B, result};

protected:

    void draw(QPainter &painter) override;

    void hoverEvent(QMouseEvent* mouse) override;
    void missEvent() override;

private:

    bool isHover;

};

#endif // MATCHFUNGLYPH_H
