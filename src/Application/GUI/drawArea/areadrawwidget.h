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

class areaDrawWidget: public QMainWindow
{
    Q_OBJECT
signals:
    // перемоделировать сигнал РЛС
    void updateSignals();

    // обновить инфу об координатах курсора
    void updateCoord(double x, double y);

public slots:
    // Добавить РЛС для отрисовки
    void addRLS(QPoint* posRLS, const QString& nameNewRLS);

    // удалить РЛС с отрисовки
    void delRLS(int indexRLS);

    // Выбрать инструмент
    void setTool(int id);

protected:

    // Переопределяем метод, чтоб не вылазило меню при нажатии лев.клавиши мыши
    void contextMenuEvent(QContextMenuEvent* event);

private slots:

    void changeGroupTools(QAction*);
    void changeTool();

public:
    areaDrawWidget(QImage* mapImg, Map* map);

    enum unit{pix, idMap};

    // Добавить инструмент
    void appendTool(drawAreaTool* toolArea);
    // Добавить грппу инструментов
    void appendToolGroup(const QVector <drawAreaTool*>&,
                         const QString& nameGroup);

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

    // инструменты
    enum tools{moveImg, setRLS, zoomImg, predictRect, predictTrail,
               mapVis, editEarth, Ruler, squareTer, def};

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

    //
    void setRenderHint(bool smoothing = true);

    enum StyleButtonTool {on, off};

protected:
    void paintEvent(QPaintEvent* pEvent);

    virtual void mousePressEvent(QMouseEvent* mouseEvent)   override;
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent)    override;
    virtual void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    virtual void wheelEvent(QWheelEvent *event)             override;

private:

    // Карта (для обнаружения высоты)
    Map* map;

    QToolButton* lastToolButton;
    void setButtonStyle(QToolButton*, StyleButtonTool style);

    //
    QPainter* pPainter;

    // Задачи отрисовки
    QMap <int, taskPainter*> drawTasks;

    // Панель для инструментов
    QToolBar* toolBar;

    //
    bool mouseFromArea(QMouseEvent *mouseEvent);

    // Все инструменты
    QMap <int, drawAreaTool*> Tools;

    // Текущий инструмент
    drawAreaTool* Tool;
    int keyCurTool;
    bool isCustomCursor;

    // Обновить размеры дискреты
    void updateSizeBlock(int countPix);

    // Изоб. для отрисовки
    QVector <QImage*> images;

    // пропорции виджета
    int LEN = 800;
    int WID = 800;

    // размеры виджета
    int length = 800;
    int width = 800;

    // Размер дискреты изображения
    int lBlock; // в метрах

    // что отрисовывать в данный момент
    int curOptRepaint;

    // координаты поставленных РЛС
    QList <QPoint*> coordsRLS;
    //
    QStringList namesRLS;
    //
    QColor curRLScolor;

    // отправлять ли данные об координатах
    bool isExportCoord;

    // точка, относительно которой рисуем изображение
    int Xo = 0;
    int Yo = 0;

    //коофициент приближения
    double k;

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

    QLabel* coordLabel;
};

#endif // AREADRAWWIDGET_H
