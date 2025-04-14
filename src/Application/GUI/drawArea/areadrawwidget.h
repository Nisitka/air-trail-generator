#ifndef AREADRAWWIDGET_H
#define AREADRAWWIDGET_H

#include <QMainWindow>

#include <QImage>

#include <QEvent>

#include <QWheelEvent>

#include <QPaintEvent>
#include <QPainter>

#include <QVector>

#include <QToolBar>
#include <QStatusBar>

#include <QLabel>

#include "./Tools/tooldefault.h"
#include "./Tools/tooleditmap.h"
#include "./Tools/toolmovemap.h"
#include "./Tools/toolpredrect.h"
#include "./Tools/toolpredtrail.h"
#include "./Tools/toolsetrls.h"
#include "./Tools/toolvismap.h"
#include "./Tools/toolzoommap.h"
#include "./Tools/toolruler.h"
#include "./Tools/toolsquareter.h"

#include "drawtask.h"

#include "backend/GIS/gisinformer.h"
#include "backend/GIS/paintermapimage.h"

class areaDrawWidget: public QWidget
{
    Q_OBJECT
signals:

    // Обновить информацию об координатах курсора
    void changedCurrentCoords(const Coords coords);

    // Изменился размер
    void resized();

public slots:

    //
    void setZoom(double k);

public:
    //
    areaDrawWidget(GISInformer* gis,
                   painterMapImage* mapImageGenerator);

    //
    void updateMapImage();

    //
    void setAngleRotate(qreal Angle);
    void changeAngleRotate(qreal dAngle);

    //
    void rotate(qreal a);

    //
    bool eventFilter(QObject *watched, QEvent *event);

    enum unit{pix, idMap};

    //
    void setDrawEnabled(bool isDrawEvent = true);

    //
    void initActionArea(int idXo, int idYo);

    //
    QPainter& getPainter();

    //
    void setTool(drawAreaTool* tool);

    // Добавить задачу для отрисовки
    void appendDrawTask(int priorityKey, taskPainter*);

    // Снять задачу с отрисовки
    void delDrawTask(int priorityKey);

    // узнать размеры карты
    void getSizePixMap(int& W, int& H); // в пикселях

    //
    double getValZoom();

    //
    int curTool();

    // Изменить коофициент приближения на dK
    void zoom(double dK);


    void drawGeoMap();
    void drawDataNet();
    void drawQFunction();

    //
    void toIdMapCoords(int& Xpix, int& Ypix);
    void toPixDrawArea(int& Xid,  int& Yid);

    // изображения для отображения
    enum showImages{geoMap, netData, QFunction};

    // задачи отрисовки (В порядке отрисовки)
    enum drawTasksID{background, terImg,
                     iconRLS, toolVis,   toolPredRect, toolPredTrail,
                     toolRLS, toolRuler, toolSquarTer,
                     border};

    // Методы для задач отрисовки
    void drawBackground();
    void drawBorder();
    void drawMap();

    //
    void setPen(const QPen&);
    void setBrush(const QBrush&);

    //
    void drawLine(int x1, int y1, int x2, int y2, unit uPoints = idMap);
    void drawCircle(int x, int y, int R, unit uR = idMap, unit uCoords = idMap);
    void drawPixmap(int x, int y, int dX, int dY, const QPixmap& pix);
    void drawRect(int x1, int y1, int x2, int y2);
    void drawText(const QRect& rect, const QString& text, unit uPoints = pix, //
                  int dXpix = 0, int dYpix = 0,                               //
                  const QColor backColor = QColor(255,255,255, 180),          //
                  const QColor textColor = Qt::black);                        //
    void drawPolygon(const QPolygon& polygon, unit uPoints = idMap);

    // Назначить выбранный пиксель в области
    void setCurrentPixPoint(int idXpx, int idYpx); // в пикселях области

    //
    void setRenderHint(bool smoothing = true);

    // Обновить размер виджета согласно размерам карты и приблежению
    void updateSize();

protected:
    void paintEvent(QPaintEvent* pEvent);

    virtual void mousePressEvent(QMouseEvent* mouseEvent)   override;
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent)    override;
    virtual void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    virtual void wheelEvent(QWheelEvent *event)             override;

private:

    //
    qreal angle;

    //
    GISInformer* gis;
    painterMapImage* mapImage;

    // Требуется обновить картинку картографической подложки
    bool updatedImageMap;

    //
    bool drawEnable;

    // Размеры области отображенеия
    int W; // в px
    int H;

    bool isCustomCursor;

    //
    drawAreaTool* Tool;

    // Точка, относительно которой рисуется подложка
    int idXo = 0; // В id дискрет карты
    int idYo = 0;

    //
    QPainter* pPainter;

    // Задачи отрисовки
    QMap <int, taskPainter*> drawTasks;

    // Обновить размеры дискреты
    void updateSizeBlock(int countPix);

    // Изоб. для отрисовки
    QVector <QImage*> images;

    // Что отрисовывать в данный момент
    int curOptRepaint;

    // Отправлять ли данные об координатах
    bool isExportCoord;

    // Коофициент приближения
    double kZoom;

    // Размеры карты для отрисовки
    int wightPixMap;
    int heightPixMap;

    // Изображение которое отрисовывается
    QImage drawImg;
};

#endif // AREADRAWWIDGET_H
