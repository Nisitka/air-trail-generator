#include "geoarea.h"

GeoArea::GeoArea(int Width_, int Length_, int Height_,
                 int lenBlock_, int heightBlock_):
    Width(Width_), Length(Length_), Height(Height_),
    lenBlock(lenBlock_), heightBlock(heightBlock_)
{

    //
    for (int i=0; i<Length; i++)
    {
        Columns.append(new QVector<GeoColumn*>);

        for (int j=0; j<Width; j++)
        {
            Columns.last()->append(new GeoColumn(Height));
        }
    }
}
