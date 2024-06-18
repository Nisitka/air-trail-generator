#ifndef GEOAREA_H
#define GEOAREA_H

#include <QVector>

#include "./geocolumn.h"

// Область гео-пространства (совокупность дискрет-столбцов)
class GeoArea
{
public:
    GeoArea(int Width, int Length);

    // Высота в координатах X, Y
    int getHeight(int idX, int idY) const;
    void setHeight(int idX, int idY, int valH) const;

    // Сделать область размером WxL
    void resize(int W, int L);

private:

    // Удалить все дискреты
    void clear();

    // Дискреты
    QVector <QVector <GeoColumn*>> Columns;

    // Размеры области
    int Width;
    int Length;
};

#endif // GEOAREA_H
