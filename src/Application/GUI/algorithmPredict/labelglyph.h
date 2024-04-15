#ifndef LABELGLYPH_H
#define LABELGLYPH_H

#include <QPixmap>

#include "glyph.h"

class LabelGlyph: public Glyph
{
public:
    LabelGlyph(QWidget* parent,
               const QPoint& position, const QPixmap& icon);

protected:

    void draw(QPainter &painter);

    //
    void pressEvent(QMouseEvent* mouse) override;
    void releaseEvent(QMouseEvent* mouse) override;

    void missEvent() override;

    //
    void hoverEvent(QMouseEvent* mouse) override;

    //
    void moveEvent(QMouseEvent* mouse) override;

private:

    //
    QPixmap icon;
};

#endif // LABELGLYPH_H
