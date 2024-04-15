#ifndef MATCHFUNGLYPH_H
#define MATCHFUNGLYPH_H

#include "glyphpoint.h"
#include "matchoperglyph.h"
#include "labelglyph.h"



class matchFunGlyph: public Glyph
{
public:
    matchFunGlyph(QWidget* parent,
                  const QPoint& position, const QSize& size = QSize(110, 40));

    enum pos{inA, oper, inB,
             lA, lB,
             lRes, outRes};

protected:

    void draw(QPainter &painter) override;

    void hoverEvent(QMouseEvent* mouse) override;
    void pressEvent(QMouseEvent* mouse) override;

    void missEvent() override;

private:

    bool isHover;

};

#endif // MATCHFUNGLYPH_H
