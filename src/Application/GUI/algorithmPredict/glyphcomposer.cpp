#include "glyphcomposer.h"

#include <QDebug>

GlyphComposer::GlyphComposer(QWidget* area_): area(area_)
{
    actionArea = new QMenu(area);
    QList <QAction*> actions = {new QAction("Добавить"),
                                new QAction("Вставить")};
    actionArea->addActions(actions);

    //
    nextKey = 0;

    //
    selectGlyph = false;
    statMouse = release;

    /* Тестовые глифы */
    addGlyph(new glyphPoint(area, QPoint(30, 30)));
    addGlyph(new glyphPoint(area, QPoint(40, 40)));
    addGlyph(new glyphPoint(area, QPoint(75, 60)));

    addGlyph(new matchFunGlyph(area, QPoint(80, 80)));
    addGlyph(new matchFunGlyph(area, QPoint(140, 140)));

    addGlyph(new LineGlyph(area,
                                glyphs[0],
                                glyphs[1]));
    addGlyph(new LineGlyph(area,
                                glyphs[1],
                                glyphs[2]));
    addGlyph(new LineGlyph(area,
                                glyphs[3],
                                glyphs[4]));

    //delGlyph(glyphs.last());

    area->repaint();
}

void GlyphComposer::addGlyph(Glyph *newGlyph)
{
    glyphs[nextKey] = newGlyph;

    newGlyph->setID(nextKey);
    nextKey++;

    connect(newGlyph, SIGNAL(killMe(Glyph*)),
            this,     SLOT(delGlyph(Glyph*)));
}

void GlyphComposer::delGlyph(Glyph *glyph)
{
    if (curGlyph == glyph)
        curGlyph = nullptr;

    glyphs.remove(glyph->getID());
    delete glyph;

    qDebug() << "count glyps: " << glyphs.size();
}

void GlyphComposer::drawEvent(QPainter& painter)
{
    // Рисуем глифы
    for (auto it = glyphs.begin(); it != glyphs.end(); ++it)
    {
        it.value()->draw(painter);
    }

    // Выбранный глиф рисуем сверху
    if (selectGlyph && curGlyph != nullptr)
        curGlyph->draw(painter);
}

void GlyphComposer::mousePressEvent(QMouseEvent *mouse)
{
    statMouse = press;

    int button = mouse->button();
    if (selectGlyph && curGlyph != nullptr)
    {
        if (button == Qt::MouseButton::LeftButton)
        {
            curGlyph->pressEvent(mouse);
        }
        else
        {
            qDebug() << "Menu!";
        }
    }
    else    // Нажатие на пустую область
    {
        if (button == Qt::MouseButton::LeftButton)
        {
            actionArea->hide();
        }
        else
        {
            actionArea->move(mouse->globalPos());
            actionArea->show();
        }
    }
}

void GlyphComposer::mouseReleaseEvent(QMouseEvent *mouse)
{
    statMouse = release;

    if (selectGlyph && curGlyph != nullptr)
    {
        curGlyph->releaseEvent(mouse);
    }
}

void GlyphComposer::mouseMoveEvent(QMouseEvent *mouse)
{
    if (selectGlyph && curGlyph != nullptr &&
        statMouse == press)
    {
        curGlyph->moveEvent(mouse);
    }
    else
    {
        selectGlyph = false;

        //
        Glyph* g;
        for (auto it = glyphs.begin(); it != glyphs.end(); ++it)
        {
            g = it.value();

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

    area->repaint();
}
