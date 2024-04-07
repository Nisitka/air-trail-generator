#include "compospredfunctionarea.h"

#include <QDebug>

composPredFunctionArea::composPredFunctionArea()
{
    // Чтоб moveEvent работал без нажатия
    this->setMouseTracking(true);

    //
    selectGlyph = false;
    statMouse = release;

    /* Тестовые глифы */
    glyphs.append(new Glyph(this, QPoint(10, 10), QSize(100, 60)));
    glyphs.append(new Glyph(this, QPoint(60, 90), QSize(50, 50)));
}

void composPredFunctionArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Отрисовка подложки
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
    painter.drawRect(0, 0,
                      this->geometry().width(),
                      this->geometry().height());

    // Рисуем глифы
    for (int i=0; i<glyphs.size(); i++)
    {
        glyphs.at(i)->draw(painter);
    }
    // Выбранный глиф рисуем сверху
    if (selectGlyph)
        curGlyph->draw(painter);

    painter.end();
}

void composPredFunctionArea::mouseMoveEvent(QMouseEvent *mouse)
{
    if (selectGlyph && statMouse == press)
    {
        curGlyph->moveEvent(mouse);
    }
    else
    {
        selectGlyph = false;

        //
        int countGlyphs = glyphs.size();
        Glyph* g;
        for (int i=0; i<countGlyphs; i++)
        {
            g = glyphs.at(i);

            // Если еще не выбран глиф и мышь навелась на глиф
            if (g->intersects(mouse->pos()) && !selectGlyph)
            {
                curGlyph = g;
                selectGlyph = true;

                if (statMouse == release)
                {
                    curGlyph->hoverEvent();
                }
                else
                {
                    curGlyph->moveEvent(mouse);
                }
            }
            else
            {
                g->missEvent();
            }
        }
    }

    repaint();
}

void composPredFunctionArea::mousePressEvent(QMouseEvent *mouse)
{
    statMouse = press;

    if (selectGlyph)
        curGlyph->pressEvent(mouse);
}

void composPredFunctionArea::mouseReleaseEvent(QMouseEvent *mouse)
{
    statMouse = release;

    if (selectGlyph)
    {
        curGlyph->releaseEvent(mouse);
    }
}
