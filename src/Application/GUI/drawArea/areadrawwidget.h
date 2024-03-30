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

#include "tooldefault.h"
#include "tooleditmap.h"
#include "toolmovemap.h"
#include "toolpredrect.h"
#include "toolpredtrail.h"
#include "toolsetrls.h"
#include "toolvismap.h"
#include "toolzoommap.h"
#include "toolruler.h"

#include "drawtask.h"

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
    areaDrawWidget(QImage* mapImg);

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

    // установить выбранную РЛС
    void setCurRLS(int idRLS);

    //
    int curTool();

    // изменить коофициент приближения на dK
    void zoom(double dK);

    // форматы изображений для сохр.
    enum formatImg{jpg, png, bmp};

    // сохранить текущее изображени
    enum typeSaveImg{full, screen, rect};
    void saveImage(const QString& dirName, formatImg, typeSaveImg = full);

    void drawGeoMap();
    void drawDataNet();
    void drawQFunction();

    // изображения для отображения
    enum showImages{geoMap, netData, QFunction};

    // инструменты
    enum tools{moveImg, setRLS, zoomImg, predictRect, predictTrail, mapVis, editEarth, Ruler, def};

    // задачи отрисовки (В порядке отрисовки)
    enum drawTasksID{background, terImg,
                     iconRLS, toolVis, toolPredRect, toolPredTrail, toolRLS, toolRuler};

    // методы для задач отрисовки
    void drawBackground();
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

    enum StyleButtonTool {on, off};

protected:
    void paintEvent(QPaintEvent* pEvent);

    virtual void mousePressEvent(QMouseEvent* mouseEvent)   override;
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent)    override;
    virtual void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    virtual void wheelEvent(QWheelEvent *event)             override;

private:

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

    // Текущий инструмент
    int keyCurTool;

    // Форматы изображений
    QVector <const char*> strFormatImg;

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

    // размер дискреты изображения
    int lBlock; // в пикселях

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

    //
    QPixmap getScreen();
};

#endif // AREADRAWWIDGET_H
