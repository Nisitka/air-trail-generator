/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "surfacegraph.h"
#include "topographicseries.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>

#include <QApplication>

#include "map.h"

#include <QDebug>

using namespace QtDataVisualization;

const float aspectRatio = 1.0; //0.1389f;

SurfaceGraph::SurfaceGraph(Q3DSurface *surface,int idXo, int idYo,
                           int numW, int numL , Map* map_)
    : m_graph(surface)
{
    float lenB = map_->getLenBlock();

    float areaWidth = numW * lenB;
    float areaLenght = numL * lenB;
    float areaHeight = map_->getMaxH();

    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);
    m_graph->axisX()->setLabelFormat("%i");
    m_graph->axisZ()->setLabelFormat("%i");
    m_graph->axisZ()->setRange(float(idXo)*lenB, idXo*lenB + areaWidth);
    m_graph->axisY()->setRange(0.0f, areaHeight); /*areaWidth * aspectRatio*/
    m_graph->axisX()->setRange(float(idYo)*lenB, idYo*lenB + areaLenght);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);
    m_graph->activeTheme()->setType(Q3DTheme::ThemePrimaryColors);

    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(20);
    m_graph->activeTheme()->setFont(font);

    m_topography = new TopographicSeries(map_);
    m_topography->setTopography(idXo, idYo, numW, numL);

    m_topography->setItemLabelFormat(QStringLiteral("@yLabel m"));

    m_highlight = new HighlightSeries();
    m_highlight->setTopographicSeries(m_topography);
    m_highlight->setMinHeight(areaHeight);/*minRange * aspectRatio*/
    m_highlight->handleGradientChange(areaHeight);/*areaWidth * aspectRatio*/
//! [1]
    QObject::connect(m_graph->axisY(), &QValue3DAxis::maxChanged,
                     m_highlight, &HighlightSeries::handleGradientChange);

    m_graph->addSeries(m_topography);
    //m_graph->addSeries(m_highlight); // подцветка рельефа вокруг точки

    m_inputHandler = new CustomInputHandler(m_graph);
    m_inputHandler->setHighlightSeries(m_highlight);
    m_inputHandler->setAxes(m_graph->axisX(), m_graph->axisY(), m_graph->axisZ());

    //m_inputHandler->setLimits(0.0f, maxSize, minRange); ///!!!!!!!!!!!!!!!!!
    m_inputHandler->setAspectRatio(aspectRatio);

    m_graph->setActiveInputHandler(m_inputHandler);
}

SurfaceGraph::~SurfaceGraph()
{
    delete m_graph;
}

//! [0]
void SurfaceGraph::toggleSurfaceTexture(bool enable)
{
    if (enable)
        m_topography->setTextureFile(QApplication::applicationDirPath() + "\\texture.jpg");
    else
        m_topography->setTextureFile("");
}
//! [0]
