#ifndef MAPOPENGLWIDGET_H
#define MAPOPENGLWIDGET_H

#include <QWidget>
#include <QLabel>

#include <QOpenGLWidget>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QVector3D>
#include <QMap>

#include "backend/GIS/gisinformer.h"

class mapOpenGLWidget: public QOpenGLWidget
{
    Q_OBJECT

//public slots:

//    // Отображение прогноза маршрута
//    void startPredictTrail();
//    void addTrailPoint(int idX, int idY, int idZ);
//    void finishPredictTrail();

public:
    explicit mapOpenGLWidget(GISInformer* mapInformer,
                             QWidget *parent = 0);

//    void updatePosRLS(QList <QVector3D>* pRLS);
//    void updateZD(QVector<QVector<QVector<QVector3D> > >* points);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mouseMoveEvent(QMouseEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent* event);

    // Какую часть карты отображать в 3D
    void initializeTerrain(int idXo, int idYo,  // id левой верхней дискреты
                           int numW, int numL); // ширина, высота

    // Актуализировать значения матрицы высот
    void updateTerrain(int idXo, int idYo, int W, int L); // в области
    void updateTerrain();                                 // везде

private:

    // Подготовлены ли данные
    bool readyRender;

    GISInformer* mapInformer;

//    // Точки траектории
//    QVector <QVector3D> trail;

//    //
//    enum interVert{Short, Long}; // ближняя, дальняя

//    // Пересекает ли отрезок границы области отображения
//    bool isIntersectBorder(const QVector3D& A, const QVector3D& B, // отрезок
//                           QVector <QVector3D>& pointsInter);      // точки пер-я

//    // Пересекает ли отрезок плоскость
//    bool isInterFlatness(const QVector3D& A,  const QVector3D& B, // отрезок
//                         const QVector3D& fA, const QVector3D& fB, const QVector3D& fC, // плоскость
//                         QVector3D& interPoint); // точка пер-я

//    // Внутри ли зоны отрисовки точка
//    bool isDrawArea(const QVector3D& point);

//    int c = 0;

//    // Обработка точек ЗО
//    void processingPointsZD();

//    void drawWallFrame();

//    void drawRectZD(int idRLS, int idLayer, int idPointLeft);

    // Добавить точку подобно glVetex3f
    void addVertex(int idX, int idY, int idZ);

//    // Прозрачность ЗО
//    float aZD;

//    // РЛС, гор. сегмент, верт. сегмент
//    QVector<QVector<QVector<QVector3D> > > pointsZD;
//    QVector<QVector<QVector<QVector3D> > > pZDinBorder;
//    QList <QVector3D>* posRLS;

    //
    int mouseLastX;
    int mouseLastY;

    //
    int mousePressX;
    int mousePressY;

    float lastAngle;
    float angle;

    float lastAngleOZ;
    float angleOZ;

    // Где стоит камера
    float camX;
    float camY;
    float camZ;

    // Куда смотрит камера
    float lookX;
    float lookY;
    float lookZ;

    // Радиус вращения камеры
    float R;
    float kSCALE = 1.2;

    //
    int idXo;
    int idYo;
    int countX = 15;
    int countY = 15;
    int idLastX;
    int idLastY;

////    // Границы зоны визуализации
////    enum vert{A, B, C};
////    QVector <QVector <QVector3D>> boards;
////    void updateVertBoards();

    // Матрица высот
    QVector <QVector <int>> heights;
    float MAP_SCALE = 0.3;
    float H_SCALE = 0.3;
};

#endif // MAPOPENGLWIDGET_H
