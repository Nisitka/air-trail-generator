#ifndef GLYPH_H
#define GLYPH_H

#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QMap>

#include <QMouseEvent>

class Glyph
{
public:
    Glyph(QWidget* parent,
          const QPoint& position = QPoint(0, 0),
          const QSize& size = QSize(1, 1),
          int t = def);

    // Типы глифов
    enum Type{conIn, conOut, label, def};

    // Отрисовать глиф
    virtual void draw(QPainter& painter);

    // Наведен ли курсор мыши на глиф
    virtual bool intersects(const QPoint& mousePos) const;

    // Добавить в глиф на позицию idPos другой глиф
    virtual void insert(Glyph* g, int idPos);

    // Добавить позицию для глифа
    void addPos(const QPoint& dXYpos, int idPos);

    // Вытащить глиф из розиции
    Glyph* pullGlyph(int idPos);

    //
    virtual void hoverEvent(QMouseEvent* mouse);
    virtual void missEvent();

    //
    virtual void pressEvent(QMouseEvent* mouse);

    //
    virtual void releaseEvent(QMouseEvent* mouse);

    //
    virtual void moveEvent(QMouseEvent* mouse);

    //
    void move(const QPoint& movePoint);

    //
    QPoint center() const;

protected:

    // Область, принадлежащая текущему глифу и глифам внутри него
    QRect belongRect;
    QSize size;

    // Глифы, принадлежащие этому глифу
    QMap <int, Glyph*> childGlyphs; //
    QMap <int, QPoint> posGlyphs;   // Позиция это относите-я точка

    // Виджет, на котором рисуем глифы
    QWidget* Parent;

    //
    QColor borderColor;

    // Точка, в которую нажали в глифе
    int Xpress, Ypress;

    //
    bool isHover;

private:

    int mType;

};

#endif // GLYPH_H
