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
    // обновить инфу об координатах курсора
    void updateCoord(double x, double y);
    // установить РЛС
    void setCoordRLS(int x, int y);

public slots:

public:
    areaDrawWidget(QImage* mapImg,
                   QImage* netDataImg,
                   QImage* QFunImg);

    // форматы изображений для сохр.
    enum formatImg{jpg, png, bmp};

    // сохранить текущее изображени
    void saveImage(const QString& dirName, formatImg);

    void drawGeoMap();
    void drawDataNet();
    void drawQFunction();

    //
    void updateSizeWidget(int countPix);

    // изображения для отображения
    enum showImages{geoMap, netData, QFunction};

protected:
    void paintEvent(QPaintEvent* pEvent);

    virtual void mousePressEvent(QMouseEvent* mouseEvent);
    virtual void mouseMoveEvent(QMouseEvent* mouseEvent);

private:
    QVector <const char*> strFormatImg;

    // обновить размеры дискреты
    void updateSizeBlock(int countPix);

    // изоб. для отрисовки
    QVector <QImage*> images;

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

    // отрисовывать ли точку для постановки РЛС
    bool isDrawPositionRLS;

};

#endif // AREADRAWWIDGET_H
