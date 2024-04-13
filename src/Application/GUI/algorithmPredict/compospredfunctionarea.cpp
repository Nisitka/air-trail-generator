#include "compospredfunctionarea.h"

composPredFunctionArea::composPredFunctionArea()
{
    this->setStyleSheet("QWidget {"
                        "   background-color: rgb(255,255,255);"
                        "}");

    // Чтоб moveEvent работал без нажатия
    this->setMouseTracking(true);

    //
    glComposer = new GlyphComposer(this);

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

    // Композитор глифов рисует все необходимые глифы
    glComposer->drawEvent(painter);

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.end();
}

void composPredFunctionArea::mouseMoveEvent(QMouseEvent *mouse)
{
    glComposer->mouseMoveEvent(mouse);
}

void composPredFunctionArea::mousePressEvent(QMouseEvent *mouse)
{
    glComposer->mousePressEvent(mouse);
}

void composPredFunctionArea::mouseReleaseEvent(QMouseEvent *mouse)
{
    glComposer->mouseReleaseEvent(mouse);
}
