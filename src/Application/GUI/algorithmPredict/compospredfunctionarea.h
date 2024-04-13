#ifndef COMPOSPREDFUNCTIONAREA_H
#define COMPOSPREDFUNCTIONAREA_H

#include <QWidget>

#include <QEvent>
#include <QWheelEvent>
#include <QPaintEvent>

#include "glyphcomposer.h"

class composPredFunctionArea: public QWidget
{
    Q_OBJECT
public:
    composPredFunctionArea();

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

    // Управление глифами через него
    GlyphComposer* glComposer;
};

#endif // COMPOSPREDFUNCTIONAREA_H
