#include "geoarea.h"

#include <QDebug>

GeoArea::GeoArea(int W, int L)
{
    //
    this->resize(W, L);
}

int GeoArea::getHeight(int idX, int idY) const
{
    return Columns[idX][idY]->getHeight();
}

void GeoArea::setHeight(int idX, int idY, int valH) const
{
    Columns[idX][idY]->setHeight(valH);
}

void GeoArea::resize(int W, int L)
{
    qDebug() << "resize geo area!";

    // Если область не очищена, то сделать это
    if (Columns.size() != 0) clear();

    // Новые размеры области
    Width = W; Length = L;

    //
    Columns.resize(Width);
    for (int x=0; x<Width; x++)
    {
        Columns[x].resize(Length);

        for (int y=0; y<Length; y++)
        {
            Columns[x][y] = new GeoColumn();
        }
    }
}

GeoColumn* GeoArea::getColumn(int idX, int idY)
{
    return Columns[idX][idY];
}

void GeoArea::clear()
{
    qDebug() << "clear geo area!";

    for (int x=0; x<Width; x++)
    {
        for (int y=0; y<Length; y++)
        {
            // Удаляем GeoColumn
            delete Columns[x][y];
        }

        // Очищаем контейнер, который их хранил
        Columns[x].clear();
    }

    Columns.clear();
}
