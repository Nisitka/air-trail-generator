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

#include "highlightseries.h"

using namespace QtDataVisualization;

//! [2]

HighlightSeries::HighlightSeries()
    : m_width(100),
      m_height(100)
{
    setDrawMode(QSurface3DSeries::DrawSurface);
    setFlatShadingEnabled(true);
    setVisible(false);
}

HighlightSeries::~HighlightSeries()
{
}

//! [0]
void HighlightSeries::setTopographicSeries(TopographicSeries *series)
{
    m_topographicSeries = series;
    m_srcWidth = m_topographicSeries->dataProxy()->array()->at(0)->size();
    m_srcHeight = m_topographicSeries->dataProxy()->array()->size();

    QObject::connect(m_topographicSeries, &QSurface3DSeries::selectedPointChanged,
                     this, &HighlightSeries::handlePositionChange);
}
//! [0]

//! [1]
void HighlightSeries::handlePositionChange(const QPoint &position)
{
    m_position = position;

    if (position == invalidSelectionPosition()) {
        setVisible(false);

        return;
    }

    int halfWidth = m_width / 2;
    int halfHeight = m_height / 2;

    int startX = position.y() - halfWidth;
    if (startX < 0 )
        startX = 0;
    int endX = position.y() + halfWidth;
    if (endX > (m_srcWidth - 1))
        endX = m_srcWidth - 1;
    int startZ = position.x() - halfHeight;
    if (startZ < 0 )
        startZ = 0;
    int endZ = position.x() + halfHeight;
    if (endZ > (m_srcHeight - 1))
        endZ = m_srcHeight - 1;

    QSurfaceDataProxy *srcProxy = m_topographicSeries->dataProxy();
    const QSurfaceDataArray &srcArray = *srcProxy->array();

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    dataArray->reserve(endZ - startZ);
    for (int i = startZ; i < endZ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(endX - startX);
        QSurfaceDataRow *srcRow = srcArray.at(i);
        for (int j = startX, p = 0; j < endX; j++, p++) {
            QVector3D pos = srcRow->at(j).position();
            (*newRow)[p].setPosition(QVector3D(pos.x(), pos.y() + 0.1f, pos.z()));
        }
        *dataArray << newRow;
    }

    dataProxy()->resetArray(dataArray);
    setVisible(true);
}
//! [1]

//! [3]
void HighlightSeries::handleGradientChange(float value)
{
    float ratio = m_minHeight / value;

    QLinearGradient gr;
    gr.setColorAt(1.000f * ratio, QColor(134, 21, 21));
    gr.setColorAt(0.933f * ratio, QColor(169, 27, 27));
    gr.setColorAt(0.866f * ratio, QColor(184, 40, 37));
    gr.setColorAt(0.799f * ratio, QColor(215, 92, 61));
    gr.setColorAt(0.732f * ratio, QColor(209, 105, 54));
    gr.setColorAt(0.665f * ratio, QColor(221, 128, 69));
    gr.setColorAt(0.598f * ratio, QColor(247, 153, 79));
    gr.setColorAt(0.531f * ratio, QColor(254, 179, 96));
    gr.setColorAt(0.464f * ratio, QColor(252, 189, 96));
    gr.setColorAt(0.397f * ratio, QColor(250, 216, 118));
    gr.setColorAt(0.330f * ratio, QColor(251, 228, 148));
    gr.setColorAt(0.263f * ratio, QColor(249, 244, 180));
    gr.setColorAt(0.197f * ratio, QColor(224, 245, 180));
    gr.setColorAt(0.129f * ratio, QColor(174, 225, 150));
    gr.setColorAt(0.062f * ratio, QColor(129, 203, 140));

    setBaseGradient(gr);
    setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}
//! [3]
