#ifndef PAINTERMAPIMAGE_H
#define PAINTERMAPIMAGE_H

#include "painterimage.h"

class painterMapImage : public painterImage
{
    Q_OBJECT
public slots:
    void run();

public:
    painterMapImage(Map*);

private:
    // вычислить цвет по высоте (т.е. номеру слоя)
    QColor colorHeight(int value);

    int dHeight;
    QVector <QColor> colors =
    {
        QColor(129, 203, 140), QColor(174, 225, 150), QColor(224, 245, 180),
        QColor(249, 244, 180), QColor(251, 228, 148), QColor(250, 216, 118),
        QColor(252, 189, 96),  QColor(254, 179, 96),  QColor(247, 153, 79),
        QColor(221, 128, 69),  QColor(209, 105, 54),  QColor(215, 92, 61),
        QColor(184, 40, 37),   QColor(169, 27, 27),   QColor(134, 21, 21),
    };

};

#endif // PAINTERMAPIMAGE_H
