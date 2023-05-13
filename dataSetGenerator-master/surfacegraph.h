#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include "topographicseries.h"
#include "highlightseries.h"

#include "custominputhandler.h"

#include "map.h"

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
public:
    explicit SurfaceGraph(Q3DSurface *surface, int idXo, int idYo,
                          int numW, int numL, Map* map_);
    ~SurfaceGraph();

    void toggleSurfaceTexture(bool enable);

private:
    Q3DSurface *m_graph;

    TopographicSeries *m_topography;
    HighlightSeries *m_highlight;
    int m_highlightWidth;
    int m_highlightHeight;

    CustomInputHandler *m_inputHandler;
};

#endif // SURFACEGRAPH_H
