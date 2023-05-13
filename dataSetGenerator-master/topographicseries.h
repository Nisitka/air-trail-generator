#ifndef TOPOGRAPHICSERIES_H
#define TOPOGRAPHICSERIES_H

#include <QtDataVisualization/QSurface3DSeries>

#include "map.h"

using namespace QtDataVisualization;

class TopographicSeries : public QSurface3DSeries
{
    Q_OBJECT
public:
    explicit TopographicSeries(Map* map_);
    ~TopographicSeries();

    float sampleCountX() { return m_sampleCountX; }
    float sampleCountZ() { return m_sampleCountZ; }

    void setTopography(int Xo, int Yo, int numW, int numL);

public Q_SLOTS:

private:
    Map* map;

    float m_sampleCountX;
    float m_sampleCountZ;

    float packingFactor;
};

#endif // TOPOGRAPHICSERIES_H
