#ifndef GLYPH_H
#define GLYPH_H

#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QVector>

#include <QMouseEvent>

class Glyph
{
public:
    Glyph(QWidget* parent, const QPoint& position, const QSize& size);

    // Отрисовать глиф
    virtual void draw(QPainter& painter);

    // Наведен ли курсор мыши на глиф
    virtual bool intersects(const QPoint& mousePos) const;

    // Добавить в глиф на позицию idPos другой глиф
    virtual void insert(Glyph* g, int idPos);

    //
    virtual void hoverEvent();
    virtual void missEvent();

    //
    virtual void pressEvent(QMouseEvent* mouse);

    //
    virtual void releaseEvent(QMouseEvent* mouse);

    //
    virtual void moveEvent(QMouseEvent* mouse);

protected:

    // Область, принадлежащая текущему глифу и глифам внутри него
    QRect belongRect;

    // Глифы, принадлежащие этому глифу
    QVector <Glyph*> childGlyphs;

    // Виджет, на котором рисуем глифы
    QWidget* parent;

    //
    QColor borderColor;

    // Точка, в которую нажали в глифе
    int Xpress, Ypress;

    QSize sizeRect;
};

#endif // GLYPH_H
