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

#include "tooldefault.h"
#include "tooleditmap.h"
#include "toolmovemap.h"
#include "toolpredrect.h"
#include "toolpredtrail.h"
#include "toolsetrls.h"
#include "toolvismap.h"
#include "toolzoommap.h"
#include "toolruler.h"
#include "toolsquareter.h"

#include "drawtask.h"

#include "backend/gis/map.h"

class areaDrawWidget: public QWidget
{
    Q_OBJECT
signals:
    // перемоделировать сигнал РЛС
    void updateSignals();

    // Обновить информацию об координатах курсора
    void updateCoord(const QString& textdataCoords);

    // Изменился размер
    void resized();

public:
    areaDrawWidget(QImage* mapImg, Map* map);

    enum unit{pix, idMap};

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

    // Длина одного блока
    void setBlockSize(int size); // в метрах
    int getBlockSize() const;

    //
    int curTool();

    // изменить коофициент приближения на dK
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

    // Обновить информацию об координатах
    void updateInfoCoordMap(int idXpx, int idYpx); // в пикселях области

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

    // Размеры области отображенеия
    int W; // в px
    int H;

    bool isCustomCursor;

    //
    drawAreaTool* Tool;

    // Карта (для обнаружения высоты)
    Map* map;

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

    // Размер дискреты изображения
    int lBlock; // в метрах

    // Что отрисовывать в данный момент
    int curOptRepaint;

    // Отправлять ли данные об координатах
    bool isExportCoord;

    // Коофициент приближения
    double kZoom;

    // размеры карты для отрисовки
    int wightPixMap;
    int heightPixMap;

    // изображение которое отрисовывается
    QImage* drawImg;
};

#endif // AREADRAWWIDGET_H
