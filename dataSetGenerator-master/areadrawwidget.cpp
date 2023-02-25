#include "areadrawwidget.h"

#include <QImage>
#include <QDebug>

areaDrawWidget::areaDrawWidget(QImage* mapImg,
                               QImage* netDataImg,
                               QImage* QFunImg)
{
    this->setFixedSize(width, length);

    // инициализация контейнера для изображений
    images = QVector <QImage*> (3);

    images[geoMap] = mapImg;
    images[netData] = netDataImg;
    images[QFunction] = QFunImg;

    //
    strFormatImg = QVector <const char*> (3);
    strFormatImg[jpg] = "JPG";
    strFormatImg[png] = "PNG";
    strFormatImg[bmp] = "BMP";

    updateSizeWidget(2);

    drawGeoMap();

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);
}

void areaDrawWidget::saveImage(const QString &dirName, formatImg fImg)
{
    // выбираем изображение которое будем сохранять
    QImage* saveImg;
    switch (curOptRepaint) {
    case geoMap:
        saveImg = images[geoMap];
        break;
    case netData:
        saveImg = images[netData];
        break;
    case QFunction:
        saveImg = images[QFunction];
        break;
    }

    // сохраняем
    saveImg->save(dirName,
                  strFormatImg[fImg],
                  100);
}

void areaDrawWidget::paintEvent(QPaintEvent *pEvent)
{
    //updateSizeWidget();

    QPainter painter;
    painter.begin(this);

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    QImage* drawImg;
    switch (curOptRepaint)
    {
        case geoMap:
            drawImg = images[geoMap];
            break;

        case netData:
            drawImg = images[netData];
            break;

        case QFunction:
            drawImg = images[QFunction];
            break;
    }
    painter.setBrush(QBrush(drawImg->scaled(width, length)));
    painter.drawRect(0, 0, width, length);

    if (isDrawPositionRLS)
    {
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
        painter.setBrush(QBrush(Qt::black));
        painter.drawEllipse(xPressMouse - 2, yPressMouse - 2, 4, 4);
    }

    painter.end();
}

void areaDrawWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    xMouse = mouseEvent->x();
    yMouse = mouseEvent->y();

    updateCoord((double)xMouse / lBlock, (double)yMouse/ lBlock);

    repaint();
}

void areaDrawWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    xPressMouse = mouseEvent->x();
    yPressMouse = mouseEvent->y();

    setCoordRLS(xPressMouse / lBlock, yPressMouse / lBlock);

    //if (isDrawPositionRLS) repaint();
}

void areaDrawWidget::updateSizeBlock(int countPix)
{
    double k = (double) countPix / lBlock;

    xPressMouse *= k;
    yPressMouse *= k;

    lBlock = countPix;
}

void areaDrawWidget::updateSizeWidget(int countPix)
{
    updateSizeBlock(countPix);

    int wMap = images[geoMap]->width();
    int lMap = images[geoMap]->height();

    length = lMap * lBlock;
    width = wMap * lBlock;

    setFixedSize(width, length);
}

void areaDrawWidget::drawGeoMap()
{
    isDrawPositionRLS = true;

    curOptRepaint = geoMap;
    repaint();
}

void areaDrawWidget::drawDataNet()
{
    isDrawPositionRLS = false;

    curOptRepaint = netData;
    repaint();
}

void areaDrawWidget::drawQFunction()
{
    isDrawPositionRLS = false;

    curOptRepaint = QFunction;
    repaint();
}
