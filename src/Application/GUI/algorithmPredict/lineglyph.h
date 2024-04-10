#ifndef LINEGLYPH_H
#define LINEGLYPH_H

#include "glyph.h"
#include <QList>

class LineGlyph: public Glyph
{
public:
    LineGlyph(QWidget* parent, Glyph* pA, Glyph* pB);

protected:

    void draw(QPainter &painter) override;
    bool intersects(const QPoint &mousePos) const override;

private:

    // Глифы, между которыми рисуется линия
    Glyph* pA;
    Glyph* pB;

    /// На будущее!
    //QList <QPoint> knots;

};

#endif // LINEGLYPH_H
