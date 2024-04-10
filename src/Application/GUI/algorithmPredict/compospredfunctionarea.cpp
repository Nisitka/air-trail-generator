#include "compospredfunctionarea.h"

#include <QDebug>

composPredFunctionArea::composPredFunctionArea()
{
    this->setStyleSheet("QWidget {"
                        "   background-color: rgb(255,255,255);"
                        "}");

    // Чтоб moveEvent работал без нажатия
    this->setMouseTracking(true);

    //
    selectGlyph = false;
    statMouse = release;

    /* Тестовые глифы */
    glyphs.append(new glyphPoint(this, QPoint(30, 30)));
    glyphs.append(new glyphPoint(this, QPoint(40, 40)));
    glyphs.append(new glyphPoint(this, QPoint(75, 60)));
    glyphs.append(new matchFunGlyph(this, QPoint(80, 80)));
    glyphs.append(new matchFunGlyph(this, QPoint(140, 140)));

    glyphs.append(new LineGlyph(this,
                                glyphs[0],
                                glyphs[1]));
    glyphs.append(new LineGlyph(this,
                                glyphs[1],
                                glyphs[2]));
    glyphs.append(new LineGlyph(this,
                                glyphs[3],
                                glyphs[4]));

    repaint();
}

void composPredFunctionArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Отрисовка подложки
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white, Qt::Dense7Pattern));
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

    painter.setRenderHint(QPainter::Antialiasing, false);
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
                    curGlyph->hoverEvent(mouse);
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
