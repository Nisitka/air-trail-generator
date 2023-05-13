#include "volumetric.h"
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtDataVisualization/qcustom3dlabel.h>
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/q3dinputhandler.h>
#include <QtCore/qmath.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtCore/QDebug>
#include <QtGui/QOpenGLContext>

using namespace QtDataVisualization;

const int mediumDetailSize(256);
const int highDetailSize(512);
const int layerDataSize(512);
const int mineShaftDiameter(1);

const int colorTableSize(256);

const int airColorIndex(1);
const int ZDColorIndex(0);
const int layerColorThickness(60);
const int heightToColorDiv(140);
const int magmaColorsMin(0);
const int magmaColorsMax(layerColorThickness);
const int aboveWaterGroundColorsMin(magmaColorsMax + 1);
const int aboveWaterGroundColorsMax(aboveWaterGroundColorsMin + layerColorThickness);
const int underWaterGroundColorsMin(aboveWaterGroundColorsMax + 1);
const int underWaterGroundColorsMax(underWaterGroundColorsMin + layerColorThickness);
const int waterColorsMin(underWaterGroundColorsMax + 1);
const int waterColorsMax(waterColorsMin + layerColorThickness);
const int terrainTransparency(12);

static bool isOpenGLES()
{
#if defined(QT_OPENGL_ES_2)
    return true;
#elif (QT_VERSION < QT_VERSION_CHECK(5, 3, 0))
    return false;
#else
    return QOpenGLContext::currentContext()->isOpenGLES();
#endif
}

VolumetricModifier::VolumetricModifier(Q3DScatter *scatter, Map* map_,
                                       int idXo_, int idYo_,
                                       int numW, int numL)
    : m_graph(scatter),
      m_volumeItem(0),
      m_slicingX(false),
      m_slicingY(false),
      m_slicingZ(false),
      m_mediumDetailRB(0),
      m_highDetailRB(0),
      m_lowDetailData(0),
      m_mediumDetailIndex(0),
      m_highDetailIndex(0),
      m_mediumDetailShaftIndex(0),
      m_highDetailShaftIndex(0),
      m_sliceSliderX(0),
      m_sliceSliderY(0),
      m_sliceSliderZ(0),
      m_usingPrimaryTable(true),
      m_sliceLabelX(0),
      m_sliceLabelY(0),
      m_sliceLabelZ(0)
{
    qDebug() << "A0";
    map = map_;

    H = map->getCountLayers();
    W = numW;
    L = numL;

    idXo = idXo_;
    idYo = idYo_;

    Hmap = H;

    m_sliceIndexX = L;
    m_sliceIndexY = H;
    m_sliceIndexZ = W;

    m_graph->activeTheme()->setType(Q3DTheme::ThemeQt);
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    //! [6]
    m_graph->setOrthoProjection(true);
    //! [6]
    m_graph->activeTheme()->setBackgroundEnabled(false);

    // Only allow zooming at the center and limit the zoom to 200% to avoid clipping issues
    static_cast<Q3DInputHandler *>(m_graph->activeInputHandler())->setZoomAtTargetEnabled(false);
    m_graph->scene()->activeCamera()->setMaxZoomLevel(200.0f);

    toggleAreaAll(true);

    if (!isOpenGLES()) {
        m_lowDetailData = new QVector<uchar>(W * H * L); //lowDetailSize

        setmapData(m_lowDetailData);

        //! [0]
        m_volumeItem = new QCustom3DVolume;
        // Adjust water level to zero with a minor tweak to y-coordinate position and scaling
        m_volumeItem->setScaling(
                    QVector3D(m_graph->axisX()->max() - m_graph->axisX()->min(),
                              (m_graph->axisY()->max() - m_graph->axisY()->min()) * 0.91f,
                              m_graph->axisZ()->max() - m_graph->axisZ()->min()));
        m_volumeItem->setPosition(
                    QVector3D((m_graph->axisX()->max() + m_graph->axisX()->min()) / 2.0f,
                              -0.045f * (m_graph->axisY()->max() - m_graph->axisY()->min()) +
                              (m_graph->axisY()->max() + m_graph->axisY()->min()) / 2.0f,
                              (m_graph->axisZ()->max() + m_graph->axisZ()->min()) / 2.0f));
        m_volumeItem->setScalingAbsolute(false);

        //! [0]
        //! [1]
        m_volumeItem->setTextureWidth(L);
        m_volumeItem->setTextureHeight(H);
        m_volumeItem->setTextureDepth(W);
        m_volumeItem->setTextureFormat(QImage::Format_Indexed8);
        m_volumeItem->setTextureData(new QVector<uchar>(*m_lowDetailData));
        //! [1]

        // Generate color tables.
        m_colorTable1.resize(202); // кол-во цветов в таблице цветов
        m_colorTable2.resize(202);

        int dH = Hmap / 200;
        for (int i=0; i<200; i++)
        {
            QColor c = colorHeight(i*dH);
            m_colorTable1[2+i] = qRgba(c.red(), c.green(), c.blue(), 255);
        }

        m_colorTable1[airColorIndex] = qRgba(0, 0, 0, 0);
        m_colorTable1[ZDColorIndex] = qRgba(0,0,255,50);

        m_colorTable2[airColorIndex] = qRgba(0, 0, 0, 0);
        m_colorTable2[ZDColorIndex] = qRgba(255, 255, 0, 255);

        //! [2]
        m_volumeItem->setColorTable(m_colorTable1);
        //! [2]

        //! [5]
        m_volumeItem->setSliceFrameGaps(QVector3D(0.01f, 0.02f, 0.01f));
        m_volumeItem->setSliceFrameThicknesses(QVector3D(0.0025f, 0.005f, 0.0025f));
        m_volumeItem->setSliceFrameWidths(QVector3D(0.0025f, 0.005f, 0.0025f));
        m_volumeItem->setDrawSliceFrames(false);
        //! [5]
        handleSlicingChanges();

        //! [3]
        m_graph->addCustomItem(m_volumeItem);

        //! [3]

        m_timer.start(0);
    } else {
        // OpenGL ES2 doesn't support 3D textures, so show a warning label instead
        QCustom3DLabel *warningLabel = new QCustom3DLabel(
                    "QCustom3DVolume is not supported with OpenGL ES2",
                    QFont(),
                    QVector3D(0.0f, 0.5f, 0.0f),
                    QVector3D(1.5f, 1.5f, 0.0f),
                    QQuaternion());
        warningLabel->setPositionAbsolute(true);
        warningLabel->setFacingCamera(true);
        m_graph->addCustomItem(warningLabel);
    }

    QObject::connect(m_graph, &QAbstract3DGraph::currentFpsChanged, this,
                     &VolumetricModifier::handleFpsChange);
}

QColor VolumetricModifier::colorHeight(int value)
{
    int r, g, b;

    dHeight = Hmap / colors.size();

    int id = value / dHeight;
    // если не предельный цвет
    if (id >= colors.size() - 1)
    {
        return colors[colors.size() - 1];
    }
    else
    {
        QColor currentColor = colors[id];
        QColor nextColor = colors[id + 1];

        double part = double(value%dHeight) / dHeight;

        r = currentColor.red();
        g = currentColor.green();
        b = currentColor.blue();

        r += (nextColor.red() - currentColor.red()) * part;
        g += (nextColor.green() - currentColor.green()) * part;
        b += (nextColor.blue() - currentColor.blue()) * part;

        return QColor(r, g, b);
    }
}

void VolumetricModifier::setFpsLabel(QLabel *fpsLabel)
{
    m_fpsLabel = fpsLabel;
}

void VolumetricModifier::setMediumDetailRB(QRadioButton *button)
{
    m_mediumDetailRB = button;
}

void VolumetricModifier::setHighDetailRB(QRadioButton *button)
{
    m_highDetailRB = button;
}

void VolumetricModifier::setSliceLabels(QLabel *xLabel, QLabel *yLabel, QLabel *zLabel)
{
    m_sliceLabelX = xLabel;
    m_sliceLabelY = yLabel;
    m_sliceLabelZ = zLabel;

    adjustSliceX(m_sliceSliderX->value());
    adjustSliceY(m_sliceSliderY->value());
    adjustSliceZ(m_sliceSliderZ->value());
}

void VolumetricModifier::setAlphaMultiplierLabel(QLabel *label)
{
    m_alphaMultiplierLabel = label;
}

void VolumetricModifier::sliceX(int enabled)
{
    m_slicingX = enabled;
    handleSlicingChanges();
}

void VolumetricModifier::sliceY(int enabled)
{
    m_slicingY = enabled;
    handleSlicingChanges();
}

void VolumetricModifier::sliceZ(int enabled)
{
    m_slicingZ = enabled;
    handleSlicingChanges();
}

void VolumetricModifier::adjustSliceX(int value)
{
    if (m_volumeItem) {
        m_sliceIndexX = value / (1024 / m_volumeItem->textureWidth());
        if (m_sliceIndexX == m_volumeItem->textureWidth())
            m_sliceIndexX--;
        if (m_volumeItem->sliceIndexX() != -1)
            //! [7]
            m_volumeItem->setSliceIndexX(m_sliceIndexX);
            //! [7]
        //! [9]
        m_sliceLabelX->setPixmap(
                    QPixmap::fromImage(m_volumeItem->renderSlice(Qt::XAxis, m_sliceIndexX)));
        //! [9]
    }
}

void VolumetricModifier::adjustSliceY(int value)
{
    if (m_volumeItem) {
        m_sliceIndexY = value / (1024 / m_volumeItem->textureHeight());
        if (m_sliceIndexY == m_volumeItem->textureHeight())
            m_sliceIndexY--;
        if (m_volumeItem->sliceIndexY() != -1)
            m_volumeItem->setSliceIndexY(m_sliceIndexY);
        m_sliceLabelY->setPixmap(
                    QPixmap::fromImage(m_volumeItem->renderSlice(Qt::YAxis, m_sliceIndexY)));
    }
}

void VolumetricModifier::adjustSliceZ(int value)
{
    if (m_volumeItem) {
        m_sliceIndexZ = value / (1024 / m_volumeItem->textureDepth());
        if (m_sliceIndexZ == m_volumeItem->textureDepth())
            m_sliceIndexZ--;
        if (m_volumeItem->sliceIndexZ() != -1)
            m_volumeItem->setSliceIndexZ(m_sliceIndexZ);
        m_sliceLabelZ->setPixmap(
                    QPixmap::fromImage(m_volumeItem->renderSlice(Qt::ZAxis, m_sliceIndexZ)));
    }
}

void VolumetricModifier::handleFpsChange(qreal fps)
{
    const QString fpsFormat = QStringLiteral("FPS: %1");
    int fps10 = int(fps * 10.0);
    m_fpsLabel->setText(fpsFormat.arg(qreal(fps10) / 10.0));
}

void VolumetricModifier::toggleLowDetail(bool enabled)
{
    if (enabled && m_volumeItem) {
        m_volumeItem->setTextureData(new QVector<uchar>(*m_lowDetailData));
        m_volumeItem->setTextureDimensions(L, H, W);
        adjustSliceX(m_sliceSliderX->value());
        adjustSliceY(m_sliceSliderY->value());
        adjustSliceZ(m_sliceSliderZ->value());
    }
}

void VolumetricModifier::setFpsMeasurement(bool enabled)
{
    m_graph->setMeasureFps(enabled);
    if (enabled)
        m_fpsLabel->setText(QStringLiteral("Загрузка..."));
    else
        m_fpsLabel->setText(QString());
}

void VolumetricModifier::setSliceSliders(QSlider *sliderX, QSlider *sliderY, QSlider *sliderZ)
{
    m_sliceSliderX = sliderX;
    m_sliceSliderY = sliderY;
    m_sliceSliderZ = sliderZ;

    // Set sliders to interesting values
    m_sliceSliderX->setValue(715);
    m_sliceSliderY->setValue(612);
    m_sliceSliderZ->setValue(715);
}

void VolumetricModifier::changeColorTable(int enabled)
{
    if (m_volumeItem) {
        if (enabled)
            m_volumeItem->setColorTable(m_colorTable2);
        else
            m_volumeItem->setColorTable(m_colorTable1);

        m_usingPrimaryTable = !enabled;

        // Rerender image labels
        adjustSliceX(m_sliceSliderX->value());
        adjustSliceY(m_sliceSliderY->value());
        adjustSliceZ(m_sliceSliderZ->value());
    }
}

void VolumetricModifier::setPreserveOpacity(bool enabled)
{

    if (m_volumeItem) {
        //! [10]
        m_volumeItem->setPreserveOpacity(!enabled);
        //! [10]

        // Rerender image labels
        adjustSliceX(m_sliceSliderX->value());
        adjustSliceY(m_sliceSliderY->value());
        adjustSliceZ(m_sliceSliderZ->value());
    }
}

void VolumetricModifier::setUseHighDefShader(bool enabled)
{
    if (m_volumeItem) {
        //! [13]
        m_volumeItem->setUseHighDefShader(enabled);
        //! [13]
    }
}

void VolumetricModifier::adjustAlphaMultiplier(int value)
{
    if (m_volumeItem) {
        float mult;
        if (value > 100)
            mult = float(value - 99) / 2.0f;
        else
            mult = float(value) / float(500 - value * 4);
        //! [11]
        m_volumeItem->setAlphaMultiplier(mult);
        //! [11]
        QString labelFormat = QStringLiteral("Доля прозрачности: %1");
        m_alphaMultiplierLabel->setText(labelFormat.arg(
                                            QString::number(m_volumeItem->alphaMultiplier(), 'f', 3)));

        // Rerender image labels
        adjustSliceX(m_sliceSliderX->value());
        adjustSliceY(m_sliceSliderY->value());
        adjustSliceZ(m_sliceSliderZ->value());
    }
}

// размеры осей графика
void VolumetricModifier::toggleAreaAll(bool enabled)
{
    if (enabled) {
        m_graph->axisX()->setRange(float(idYo), float(idYo+L)); //m_graph->axisX()->setRange(0.0f, float(map->getWidth()));
        m_graph->axisY()->setRange(0.0f, float(H));
        m_graph->axisZ()->setRange(float(idXo), float(idXo+W));
        m_graph->axisX()->setSegmentCount(5);
        m_graph->axisY()->setSegmentCount(6);
        m_graph->axisZ()->setSegmentCount(5);
    }
}

void VolumetricModifier::setDrawSliceFrames(int enabled)
{
    if (m_volumeItem)
        m_volumeItem->setDrawSliceFrames(enabled);
}

void VolumetricModifier::initHeightMap(QString fileName, QVector<uchar> &layerData)
{
    QImage heightImage(fileName);

    layerData.resize(layerDataSize * layerDataSize);
    const uchar *bits = heightImage.bits();
    int index = 0;
    QVector<QRgb> colorTable = heightImage.colorTable();
    for (int i = 0; i < layerDataSize; i++) {
        for (int j = 0; j < layerDataSize; j++) {
            layerData[index] = qRed(colorTable.at(bits[index]));
            index++;
        }
    }
}

void VolumetricModifier::setmapData(QVector<uchar> *textureData)
{
    int colorIndex, index;
    for (int h=0; h<H; h++)
    {
        for(int x=idXo; x<idXo+W; x++)
        {
            for(int y=idYo; y<idYo+L; y++)
            {
                colorIndex = airColorIndex;

                index = (x-idXo)*L*H + int((H-1-h)*L) + y - idYo;

                geoBlock* block = map->getBlock(x, y, h);
                if (block->isEarth())
                {
                    colorIndex = 200 * ((double)h/H) + 2;
                }
                else
                {
                    if (block->isZD()) colorIndex = ZDColorIndex;
                    else colorIndex = airColorIndex;
                }
                (*textureData)[index] = colorIndex;
            }
        }
    }

}

void VolumetricModifier::handleSlicingChanges()
{
    if (m_volumeItem) {
        if (m_slicingX || m_slicingY || m_slicingZ) {
            // Only show slices of selected dimensions
            //! [8]
            m_volumeItem->setDrawSlices(true);
            //! [8]
            m_volumeItem->setSliceIndexX(m_slicingX ? m_sliceIndexX : -1);
            m_volumeItem->setSliceIndexY(m_slicingY ? m_sliceIndexY : -1);
            m_volumeItem->setSliceIndexZ(m_slicingZ ? m_sliceIndexZ : -1);
        } else {
            // Show slice frames for all dimenstions when not actually slicing
            m_volumeItem->setDrawSlices(false);
            m_volumeItem->setSliceIndexX(m_sliceIndexX);
            m_volumeItem->setSliceIndexY(m_sliceIndexY);
            m_volumeItem->setSliceIndexZ(m_sliceIndexZ);
        }
    }
}

VolumetricModifier::~VolumetricModifier()
{
    delete m_graph;
}
