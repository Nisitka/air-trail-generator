#include "geoarea.h"

#include <QDebug>

GeoArea::GeoArea(int W, int L)
{
    Columns = nullptr;

    //
    this->resize(W, L);
}

int GeoArea::getHeight(int idX, int idY) const
{
    return Columns[idX*Length + idY].getHeight();
}

void GeoArea::setHeight(int idX, int idY, int valH) const
{
    return Columns[idX*Length + idY].setHeight(valH);
}

void GeoArea::resize(int W, int L)
{
    qDebug() << "resize geo area...";

    // Если область не очищена, то сделать это
    if (Columns != nullptr) clear();

    // Новые размеры области
    Width = W; Length = L;

    //
    Columns = new GeoColumn [Width*Length];

    qDebug() << "size geo area: " << Width << Length;
}

GeoColumn* GeoArea::getColumn(int idX, int idY)
{
    return Columns + (idX*Length) + idY;
}

void GeoArea::clear()
{
    qDebug() << "clear geo area!";

    delete [] Columns;
}
