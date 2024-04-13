#include "matchoperglyph.h"

matchOperGlyph::matchOperGlyph(QWidget* parent,
                               const QPoint& position):
    operationGlyph(parent, position)
{
    addOperation(sum, QIcon(":/resurs/plus"));
    addOperation(min, QIcon(":/resurs/minus"));
    addOperation(div, QIcon(":/resurs/division"));
    addOperation(mul, QIcon(":/resurs/multiplication-sign"));

    selectOperation(sum);
}
