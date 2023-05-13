#include "topographicseries.h"

#include <QDebug>

using namespace QtDataVisualization;

TopographicSeries::TopographicSeries(Map* map_)
{
    map = map_;

    setDrawMode(QSurface3DSeries::DrawSurface);
    setFlatShadingEnabled(true);
    setBaseColor(Qt::white);
}

void TopographicSeries::setTopography(int Xo, int Yo, int numW, int numL)
{
    float lenB = map->getLenBlock();

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(numW);
    for (int idX=Xo; idX < Xo + numW; idX++)
    {
        float x = idX * lenB;
        QSurfaceDataRow *newRow = new QSurfaceDataRow(numL);
        for (int idY=Yo; idY < Yo + numL; idY++)
        {
            float h = map->getHeight(idX, idY, Map::m);
            float y = idY * lenB;
            (*newRow)[idY - Yo].setPosition(QVector3D(y, h, x));
        }
        *dataArray << newRow;
    }

    dataProxy()->resetArray(dataArray);

    m_sampleCountX = float(numW);
    m_sampleCountZ = float(numL);
}

TopographicSeries::~TopographicSeries()
{

}
