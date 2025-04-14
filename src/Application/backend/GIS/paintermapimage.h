#ifndef PAINTERMAPIMAGE_H
#define PAINTERMAPIMAGE_H

#include <QObject>
#include <QImage>
#include <QColor>

#include "heightmeter.h"

class painterMapImage: public QObject
{
    Q_OBJECT
public:

    //
    painterMapImage(HeightMeter* Heigt); // Для расчета цвета

    //
    void getMapImage(int idXo, int idYo, // Левый верхний угол
                     int W, int H,       // Размеры
                     QImage& img);       // Куда поместить результат
    void getMapImage(const QRect& area,  // Область карты
                     QImage& img);       // Куда поместить результат


private:

    // Высота точек на карте известна ему
    HeightMeter* Height;

    // вычислить цвет по высоте (т.е. номеру слоя)
    QColor colorHeight(int numLayer);
    int dHeight;
    const QVector <QColor> colors =
    {
        QColor(129, 203, 140), QColor(174, 225, 150), QColor(224, 245, 180),
        QColor(249, 244, 180), QColor(251, 228, 148), QColor(250, 216, 118),
        QColor(252, 189, 96),  QColor(254, 179, 96),  QColor(247, 153, 79),
        QColor(221, 128, 69),  QColor(209, 105, 54),  QColor(215, 92, 61),
        QColor(184, 40, 37),   QColor(169, 27, 27),   QColor(134, 21, 21),
    };

};

#endif // PAINTERMAPIMAGE_H
