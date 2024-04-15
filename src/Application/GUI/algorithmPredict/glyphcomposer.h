#ifndef GLYPHCOMPOSER_H
#define GLYPHCOMPOSER_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>

#include "glyph.h"

#include "glyphpoint.h"
#include "matchfunglyph.h"
#include "operationglyph.h"
#include "lineglyph.h"
#include "labelglyph.h"

class GlyphComposer: public QObject
{
    Q_OBJECT
public:
    GlyphComposer(QWidget* area);

    //
    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};

    //
    void drawEvent(QPainter& painter);

    //
    void mouseMoveEvent(QMouseEvent* mouse);

    //
    void mousePressEvent(QMouseEvent* mouse);

    //
    void mouseReleaseEvent(QMouseEvent* mouse);

public slots:

    // Отдать глиф на управление
    void addGlyph(Glyph* newGlyph);

private slots:

    // Удалить глиф
    void delGlyph(Glyph* deadGlyph);

    //
    void addGlyphAction();

    //
    void delGlyphAction();

    // Перейти в состояние по умолчанию
    void toDefStatus();

private:

    // Кому принадлежат глифы, которыми управляем
    QWidget* area;

    // Меню для добавления глифов
    QMenu* actionArea;
    QPoint posActArea; // Относительно area

    // Меню по работе с глифом
    QMenu* actionGlyph;

    // Состояние мыши
    int statMouse;

    // Все глифы
    QMap <int, Glyph*> glyphs;
    int nextKey;

    // Выбраный глиф (наведены на него)
    Glyph* curGlyph;

    // Выбран ли какой-нибудь глиф
    bool selectGlyph;
};

#endif // GLYPHCOMPOSER_H
