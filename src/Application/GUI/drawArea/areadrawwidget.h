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

#include "backend/map.h"

class areaDrawWidget: public QWidget
{
    Q_OBJECT
signals:
    // перемоделировать сигнал РЛС
    void updateSignals();

    // Обновить информацию об координатах курсора
    void updateCoord(const QString& textdataCoords);

public slots:
    // Добавить РЛС для отрисовки
    void addRLS(QPoint* posRLS, const QString& nameNewRLS);

    // удалить РЛС с отрисовки
    void delRLS(int indexRLS);

public:
    areaDrawWidget(QImage* mapImg, Map* map);

    enum unit{pix, idMap};

    //
    void setTool(drawAreaTool* tool);

    // Добавить задачу для отрисовки
    void appendDrawTask(int priorityKey, taskPainter*);

    // Снять задачу с отрисовки
    void delDrawTask(int priorityKey);

    // узнать левый верхний угол карты относительно виджета
    void getCoordDrawArea(int& Xo, int& Yo);

    // установить левый верхний угол карты относительно виджета
    void setCoordDrawArea(int Xo, int Yo);

    // узнать размеры карты
    void getSizePixMap(int& W, int& H); // в пикселях

    //
    double getValZoom();

    // Длина одного блока
    void setBlockSize(int size); // в метрах
    int getBlockSize() const;

    // установить выбранную РЛС
    void setCurRLS(int idRLS);

    //
    int curTool();

    // изменить коофициент приближения на dK
    void zoom(double dK);


    void drawGeoMap();
    void drawDataNet();
    void drawQFunction();

    //
    void toIdMapCoords(int& Xpix, int& Ypix);

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
    void drawRLS();

    //
    void setPen(const QPen&);
    void setBrush(const QBrush&);

    //
    void drawLine(int x1, int y1, int x2, int y2, unit uPoints = idMap);
    void drawCircle(int x, int y, int R, unit uR = idMap, unit uCoords = idMap);
    void drawPixmap(int x, int y, int dX, int dY, const QPixmap& pix);
    void drawRect(int x1, int y1, int x2, int y2);
    void drawText(const QRect& rect, const QString& text, unit uPoints = pix);
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

    // Координаты поставленных РЛС
    QList <QPoint*> coordsRLS;
    //
    QStringList namesRLS;
    //
    QColor curRLScolor;

    // Отправлять ли данные об координатах
    bool isExportCoord;

    // Точка, относительно которой рисуем изображение
    int Xo = 0;
    int Yo = 0;

    // Коофициент приближения
    double kZoom;

    // размеры карты для отрисовки
    int wightPixMap;
    int heightPixMap;

    // изображение которое отрисовывается
    QImage* drawImg;

    // иконки РЛС
    QPixmap* pixRLS;
    QPixmap* pixCurRLS;
    // выбранная РЛС
    int idCurRLS; // индекс выбранной РЛС
};

#endif // AREADRAWWIDGET_H
