#ifndef COMPOSPREDFUNCTIONAREA_H
#define COMPOSPREDFUNCTIONAREA_H

#include <QWidget>

#include <QEvent>
#include <QWheelEvent>
#include <QPaintEvent>

#include "glyph.h"
#include "glyphpoint.h"
#include "matchfunglyph.h"
#include "operationglyph.h"

class composPredFunctionArea: public QWidget
{
    Q_OBJECT
public:
    composPredFunctionArea();

    //
    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};

protected:

    //
    void paintEvent(QPaintEvent* event) override;

    //
    void mouseMoveEvent(QMouseEvent* mouse) override;

    //
    void mousePressEvent(QMouseEvent* mouse) override;

    //
    void mouseReleaseEvent(QMouseEvent* mouse) override;

private:

    // Состояние мыши
    int statMouse;

    // Все глифы
    QVector <Glyph*> glyphs;

    // Выбраный глиф (наведены на него)
    Glyph* curGlyph;

    // Выбран ли какой-нибудь глиф
    bool selectGlyph;
};

#endif // COMPOSPREDFUNCTIONAREA_H
