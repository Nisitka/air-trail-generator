#include "visualmap3d.h"

#include "designer.h"

visualMap3D::visualMap3D(QWidget* widget_,
                         int idXo, int idYo,
                         int numW, int numL, Map* map_)
{
    map = map_;

    int height = 400;
    int width = 100;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, QColor(129, 203, 140));
    gr.setColorAt(0.933f, QColor(174, 225, 150));
    gr.setColorAt(0.866f, QColor(224, 245, 180));
    gr.setColorAt(0.799f, QColor(249, 244, 180));
    gr.setColorAt(0.732f, QColor(251, 228, 148));
    gr.setColorAt(0.665f, QColor(250, 216, 118));
    gr.setColorAt(0.598f, QColor(252, 189, 96));
    gr.setColorAt(0.531f, QColor(254, 179, 96));
    gr.setColorAt(0.464f, QColor(247, 153, 79));
    gr.setColorAt(0.397f, QColor(221, 128, 69));
    gr.setColorAt(0.330f, QColor(209, 105, 54));
    gr.setColorAt(0.263f, QColor(215, 92, 61));
    gr.setColorAt(0.197f, QColor(184, 40, 37));
    gr.setColorAt(0.129f, QColor(169, 27, 27));
    gr.setColorAt(0.062f, QColor(134, 21, 21));

    int maxH = map->getMaxH();
    int countS = 6;
    int dH = maxH / (countS - 1);

    /*
    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 5;
    for (int i = 0; i < countS; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 м").arg(maxH - (i * dH)));
    }*/
}

visualMap3D::~visualMap3D()
{

}
