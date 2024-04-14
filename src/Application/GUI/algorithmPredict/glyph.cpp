#include "glyph.h"

#include <QDebug>

Glyph::Glyph(QWidget* parent,
             const QPoint& pos, const QSize& s, int t):
    Parent(parent),
    mType(t), size(s), isHover(false)
{
    //
    belongRect = QRect(pos, size);


    borderColor = Qt::black;
}

Glyph::~Glyph()
{
    // Удаляем все свои глифы
    int countChild = childGlyphs.size();
    for (int i=0; i<countChild; i++)
    {
        delete childGlyphs[i];
    }

    qDebug() << "delete" << id << "glyph";

    dead();
}

void Glyph::setID(int id_)
{
    id = id_;
}

int Glyph::getID() const
{
    return id;
}

bool Glyph::intersects(const QPoint &mousePos) const
{
    return belongRect.contains(mousePos);
}

void Glyph::addPos(const QPoint& dXYpos, int idPos)
{
    if (!posGlyphs.contains(idPos))
        posGlyphs[idPos] = dXYpos;
}

void Glyph::insert(Glyph *g, int idPos)
{
    childGlyphs[idPos] = g;
    g->move(belongRect.topLeft() + posGlyphs[idPos]);
}

Glyph* Glyph::pullGlyph(int idPos)
{
    if (childGlyphs.contains(idPos))
        return childGlyphs[idPos];
    else return nullptr;
}

QPoint Glyph::center() const
{
    return belongRect.center();
}

void Glyph::draw(QPainter &painter)
{
    /* По умолчанию глиф никак не рисуется,
     * а рисуются только его составные глифы */

    // Рисуем всех свои остальные глифы
    int countChild = childGlyphs.size();
    for (int i=0; i<countChild; i++)
    {
        childGlyphs[i]->draw(painter);
    }
}

void Glyph::hoverEvent(QMouseEvent* mouse)
{
    borderColor = Qt::red;

    Glyph* g;
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        g = it.value();
        if (g->intersects(mouse->pos()))
            g->hoverEvent(mouse);
        else
            g->missEvent();
    }
}

void Glyph::missEvent()
{
    borderColor = Qt::black;

    //
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        it.value()->missEvent();
    }
}

void Glyph::pressEvent(QMouseEvent* mouse)
{
    Xpress = mouse->x() - belongRect.x();
    Ypress = mouse->y() - belongRect.y();
}

void Glyph::releaseEvent(QMouseEvent* mouse)
{
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        if (it.value()->intersects(mouse->pos()))
            it.value()->releaseEvent(mouse);
    }
}

void Glyph::moveEvent(QMouseEvent *mouse)
{
    int newX = mouse->x() - Xpress;
    int newY = mouse->y() - Ypress;

    belongRect.moveTo(newX, newY);

    //
    for (auto it = childGlyphs.begin(); it != childGlyphs.end(); ++it)
    {
        it.value()->move(QPoint(newX, newY) + posGlyphs[it.key()]);
    }
}

void Glyph::move(const QPoint& p)
{
    belongRect.moveCenter(p);
}
