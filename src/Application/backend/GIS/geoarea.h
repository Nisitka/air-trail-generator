#ifndef GEOAREA_H
#define GEOAREA_H

#include <QVector>

#include "./geocolumn.h"

// Область гео-пространства (совокупность дискрет-столбцов)
class GeoArea
{
public:
    GeoArea(int Width, int Length, int Height,
            int lenBlock = 20, int heightBlock = 25);

    // Высота в координатах X, Y
    enum units{m, id};
    int getHeight(int X, int Y, int type = id) const;
    void setHeight(int idX, int idY, int valH);

    // Ширина/Длина блоков в столбцах
    void setLenBlock(int);
    int getLenBlock() const;

    // Высота блоков в столбцах
    void setHeightBlock(int); // в метрах
    int getHeightBlock() const;

private:

    // Дискреты
    QVector <QVector <GeoColumn*>*> Columns;

    // Размеры области
    int Height;
    int Width;
    int Length;

    // Размеры блоков в метрах
    int lenBlock;
    int heightBlock;
};

#endif // GEOAREA_H
