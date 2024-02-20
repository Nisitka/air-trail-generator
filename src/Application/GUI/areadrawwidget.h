#ifndef AREADRAWWIDGET_H
#define AREADRAWWIDGET_H

#include <QWidget>

#include <QImage>

#include <QEvent>
#include <QPaintEvent>
#include <QPainter>

#include <QVector>

class areaDrawWidget : public QWidget
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
    void setPointsTrail(const QPoint& begin, const QPoint& last);

public slots:
    // земля отредактирована
    void readyEditEarth();

    // добавить РЛС для отрисовки
    void addRLS(QPoint* posRLS, const QString& nameNewRLS);

    // удалить РЛС с отрисовки
    void delRLS(int indexRLS);

public:
    areaDrawWidget(QImage* mapImg,
                   QImage* netDataImg,
                   QImage* QFunImg);

    // установить выбранную РЛС
    void setCurRLS(int idRLS);

    int curTool();

    void startPredictTrail();
    void finishPredictTrail();

    void drawResultPredictRect(int idX, int idY);
    bool paintPredictRect;

    // установка квадрата прогноза
    void setPredictRect(int idXo, int idYo);

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
    void setTool(tools);

    // добавить точку траектории
    void addPointTrail(int idXpt, int idYpt);

    // установить размер кисти
    void setRangeToolEditEarth(int R); // длина квадрата в пикселях

protected:
    void paintEvent(QPaintEvent* pEvent);

    virtual void mousePressEvent(QMouseEvent* mouseEvent);
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent);

    virtual void mouseReleaseEvent(QMouseEvent* mouseEvent);

private:
    // размер кисти редактора рельефа
    int toolEarthR;

    // точки области детального отображения рельефа
    QPoint a3D;
    QPoint b3D;

    int angX3D, angY3D;
    int numW, numL;

    // рисовать ли область детального отображения
    bool isDrawRect3D;


    enum keyMouse{left, right, mid};
    enum statusMouse{press, release};
    int lastKeyMouse;
    int statMouse;

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

    // курсор
    int xPressMouse; // последние координаты нажатия
    int yPressMouse;
    int xMouse;      // последние координаты
    int yMouse;

    // позиция РЛС на окне в базовых пикселях
    int xPosRLS;
    int yPosRLS;

    // координаты поставленных РЛС
    QList <QPoint*> coordsRLS;
    //
    QStringList namesRLS;
    //
    QColor curRLScolor;

    // координаты мыши в дискретах карты
    int idX, idY;

    // отправлять ли данные об координатах
    bool isExportCoord;

    // отрисовывать ли точку для постановки РЛС
    bool isDrawPositionRLS;

    // точка, относительно которой рисуем изображение
    int Xo = 0;
    int Yo = 0;

    // точка захвата картинки
    int pXo, pYo;

    // приближение (отдаление) на дискрету
    void zoom();
    double k; //коофициент приближения
    const double dk = 0.2; // дискрета приближения
    QPixmap iconZoom;
    QCursor zoomCursor;

    QCursor editEarthCursor;

    QCursor moveCloseCursor = Qt::ClosedHandCursor;
    QCursor moveOpenCursor = Qt::OpenHandCursor;
    QCursor rlsCursor = Qt::CrossCursor;
    QCursor predictNetCursor = Qt::CrossCursor;
    QCursor rect3DCursor = Qt::PointingHandCursor;

    // передвижение изображения двигая мышку
    void matchTranslateMove();
    int dXmove, dYmove;

    // размеры карты для отрисовки
    int wightPixMap;
    int heightPixMap;

    // изображение которое отрисовывается
    QImage* drawImg;

    // отрисовывать ли выбранный квадрат инструмента
    bool drawRectInit;

    // отрисовывать ли выбранный квадрат прогноза
    bool drawRectPredict;
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

    // рисовать ли оконечные точки маршрута
    bool drawSFPointsTrail;

    // начался ли прогноз траектории
    bool isPredictTrail;

    QVector <QPoint*> trail;
    void clearTrail();

    //
    QPixmap getScreen();
};

#endif // AREADRAWWIDGET_H
