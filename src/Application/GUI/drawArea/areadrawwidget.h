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

class areaDrawWidget: public QMainWindow
{
    Q_OBJECT
signals:
    // перемоделировать сигнал РЛС
    void updateSignals();

    // поднять землю в указанной области
    void upEarth(int idX, int idY, int R);

    // опустить землю в указанной области
    void downEarth(int idX, int idY, int R);

    // обновить данные об области 3D визуализации
    void updateRect3D(int idXo, int idYo, int numW, int numL);

    // обновить инфу об координатах курсора
    void updateCoord(double x, double y);

    // установить РЛС
    void setCoordRLS(int x, int y);

    // предсказать полет БпЛА в квадрате
    void predictMoveDroneRect(int idX, int idY, int typeP = -1);

    //
    void setPointsTrail(int idXa, int idYa, int idXb, int idYb);

public slots:
    // Добавить РЛС для отрисовки
    void addRLS(QPoint* posRLS, const QString& nameNewRLS);

    //
    void startPredictTrail();
    void finishPredictTrail();

    // Добавить точку траектории
    void addPointTrail(int idXpt, int idYpt, int idZpt);

    // удалить РЛС с отрисовки
    void delRLS(int indexRLS);

    // Выбрать инструмент
    void setTool(int id);

protected:

    // Переопределяем метод, чтоб не вылазило меню при нажатии лев.клавиши мыши
    void contextMenuEvent(QContextMenuEvent* event);

public:
    areaDrawWidget(QImage* mapImg);

    //
    void setRectVis(int idXa, int idYa, int idXb, int idYb);

    // узнать левый верхний угол карты относительно виджета
    void getCoordDrawArea(int& Xo, int& Yo);

    // установить левый верхний угол карты относительно виджета
    void setCoordDrawArea(int Xo, int Yo);

    // узнать размеры карты
    void getSizePixMap(int& W, int& H); // в пикселях

    //
    double getValZoom();

    // изменить точку постановки РЛС
    void setMarkCoordRLS(int x, int y);

    // установить выбранную РЛС
    void setCurRLS(int idRLS);

    //
    int curTool();

    // начальная и конечная точки маршрута БПЛА
    void setBeginPointTrail(int idX, int idY);
    void setLastPointTrail(int idX, int idY);
    void sendPointsTrail();

    void drawResultPredictRect(int idX, int idY);
    bool paintPredictRect;

    // установка квадрата прогноза
    void setPredictRect(int idXo, int idYo);

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
    enum tools{moveImg, setRLS, zoomImg, predictRect, predictTrail, mapVis, editEarth, def};

    //
    QToolBar* getToolBar();

    // задачи отрисовки (В порядке отрисовки)
    enum drawTasksID{background, terImg,
                     iconRLS, toolVis, toolPredRect, toolPredTrail, toolRLS};
    // методы для задач отрисовки
    void drawBackground(QPainter& painter);
    void drawMap(QPainter& painter);
    void drawEleToolRLS(QPainter& painter);
    void drawEleToolVis(QPainter& painter);
    void drawEleToolPredRect(QPainter& painter);
    void drawEleToolPredTrail(QPainter& painter);
    void drawRLS(QPainter& painter);

    // база задач отрисовки
    QMap <drawTasksID, void (areaDrawWidget::*)(QPainter&)> drawTasks;

    void (areaDrawWidget::*p)(QPainter&);
    // текущие задачи
    QMap <drawTasksID, void (areaDrawWidget::*)(QPainter&)> curDrawTasks;

    // добавить задачу для отрисовки
    void appendDrawTask(drawTasksID);

    // снять задачу с отрисовки
    void delDrawTask(drawTasksID);

    // установить размер кисти
    void setRangeToolEditEarth(int R); // длина квадрата в пикселях

protected:
    void paintEvent(QPaintEvent* pEvent);

    virtual void mousePressEvent(QMouseEvent* mouseEvent)   override;
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent)    override;
    virtual void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    virtual void wheelEvent(QWheelEvent *event)             override;

private:
    // Панель для инструментов
    QToolBar* toolBar;

    //
    bool mouseFromArea(QMouseEvent *mouseEvent);

    // Все инструменты
    QMap <int, drawAreaTool*> Tools;

    // Текущий инструмент
    drawAreaTool* Tool;

    // размер кисти редактора рельефа
    int toolEarthR;

    // точки области детального отображения рельефа
    QPoint a3D;
    QPoint b3D;

    // текущий инструмент
    int tool;

    // форматы изображений
    QVector <const char*> strFormatImg;

    // обновить размеры дискреты
    void updateSizeBlock(int countPix);

    // изоб. для отрисовки
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

    // позиция РЛС на окне в базовых пикселях
    int xPosRLS;
    int yPosRLS;

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

    // приближение (отдаление) на дискрету
    //void zoom();
    double k; //коофициент приближения

    // размеры карты для отрисовки
    int wightPixMap;
    int heightPixMap;

    // изображение которое отрисовывается
    QImage* drawImg;

    //
    int idXoPredict;
    int idYoPredict;

    // индексы дискрет центра квадрата прогноза
    int idXRect;
    int idYRect;

    // результаты прогноза в квадрате
    int idPRectX;
    int idPRectY;

    // точки для задания траектории
    QPoint lastPoint;  // в индексах карты
    QPoint beginPoint; // в индексах карты

    // иконки оконечных точек
    QPixmap* pixBeginDrone;  // начала
    QPixmap* pixFinishDrone; // конца

    // иконки РЛС
    QPixmap* pixRLS;
    QPixmap* pixCurRLS;
    // выбранная РЛС
    int idCurRLS; // индекс выбранной РЛС

    //
    QVector <QPoint*> trail;
    void clearTrail();

    //
    QPixmap getScreen();
};

#endif // AREADRAWWIDGET_H
