#include "mapopenglwidget.h"

#include <iostream>

#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

#include <QDebug>

#include <QPicture>
#include <QPainter>
#include <QRgb>

#include <QGLWidget>

#include <QDebug>

mapOpenGLWidget::mapOpenGLWidget(GISInformer* mapInformer,
                                 QWidget *parent):
    QOpenGLWidget(parent),
    mapInformer(mapInformer),
    camX(0), camY(0), camZ(0),
    lookX(0), lookY(0), lookZ(0),
    angle(0), lastAngle(1.57),
    angleOZ(0), lastAngleOZ(1.0)
{
    //
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->setMinimumSize(300, 200);
    this->setMaximumSize(9999, 9999);

    readyRender = false;
}

//void mapOpenGLWidget::startPredictTrail()
//{
//    trail.clear();
//}

//void mapOpenGLWidget::addTrailPoint(int idX, int idY, int idZ)
//{
//    trail.append(QVector3D(idX, idY, idZ));

//    update();
//}

//void mapOpenGLWidget::finishPredictTrail()
//{

//}

//bool mapOpenGLWidget::isIntersectBorder(const QVector3D &pA, const QVector3D &pB, QVector <QVector3D>& pointsInter)
//{
//    pointsInter.clear();

//    // Если отрезок находится в зоне отрисовки то не считаем
//    if (isDrawArea(pA) & isDrawArea(pB)) return false;

//    int countInter = 0;
//    pointsInter.append(QVector3D());
//    pointsInter.append(QVector3D());

//    QVector3D pCurInter;
//    QVector3D shortInter;

//    // Проверяем на пер-я с границами зоны отображения
//    for (int idB = 0; idB < 4; idB++)
//    {
//        if (isInterFlatness(pA, pB,
//                            boards[idB][vert::A], boards[idB][vert::B], boards[idB][vert::C],
//                            pCurInter))
//        {
//            countInter++;

//            if(countInter == 2)
//            {
//                if (pCurInter.distanceToPoint(pB) < shortInter.distanceToPoint(pB))
//                {
//                    pointsInter[interVert::Short] = pCurInter;
//                    pointsInter[interVert::Long]  = shortInter;
//                }
//                else
//                {
//                    pointsInter[interVert::Short] = shortInter;
//                    pointsInter[interVert::Long]  = pCurInter;
//                }

//                // т.к. макс-м может быть 2 точки то
//                return true;
//            }
//            else
//            {
//                shortInter = pCurInter;
//            }
//        }
//    }

//    // Если дошли до сюда значит точка одна
//    pointsInter[interVert::Short] = shortInter;
//    pointsInter.remove(interVert::Long);

//    return true;
//}

//bool mapOpenGLWidget::isInterFlatness(const QVector3D &A, const QVector3D &B,
//                                      const QVector3D &pA, const QVector3D &pB, const QVector3D &pC,
//                                      QVector3D &interPoint)
//{
//    //
//    QVector3D N = QVector3D::normal(pA, pB, pC);

//    QVector3D V = pA - A;

//    // Расстояние до плоскости по нормали
//    float d = QVector3D::dotProduct(N, V);

//    QVector3D W = A - B;
//    float e = QVector3D::dotProduct(N, W);

//    // Точка пер-я
//    QVector3D& O = interPoint;

//    // Одна точка пер-я прямой
//    if (e != 0.0)
//    {
//        O = A + (W * ((float) d / e));

//        // Пересекает ли отрезок
//        if (QVector3D::dotProduct(A - O, B - O) <= 0)
//        {
//            return true;
//        }
//    }

//    return false;
//}

//void mapOpenGLWidget::processingPointsZD()
//{
//    pZDinBorder.clear();
//    pZDinBorder = pointsZD;

//    // точка стояния РЛС
//    QVector3D pRLS;

//    //
//    QVector <QVector3D> interPoints;

//    //
//    bool RLSfromArea = false;

//    // по РЛС
//    for (int idRLS=0; idRLS<pointsZD.size(); idRLS++)
//    {
//        pRLS = posRLS->at(idRLS);

//        // РЛС в зоне отрисовки?
//        RLSfromArea = isDrawArea(pRLS);

//        // по гор. сегментам
//        for (int idHor = 0; idHor < pointsZD[idRLS].size(); idHor++)
//        {
//            // по верт. сегментам
//            for (int idL = 0; idL < pointsZD[idRLS][idHor].size(); idL++)
//            {
//                // Если есть пересечения с границами по пути от ЗО до поз. РЛС
//                if (isIntersectBorder(pointsZD[idRLS][idHor][idL], pRLS, interPoints))
//                {
//                    // Если РЛС в зоне отрисовки
//                    if (RLSfromArea)
//                    {
//                        pZDinBorder[idRLS][idHor][idL] = interPoints[interVert::Short];
//                    }
//                    else
//                    {
//                        /* ... */
//                    }
//                }
//            }
//        }
//    }
//}

//bool mapOpenGLWidget::isDrawArea(const QVector3D &point)
//{
//    int idX = point.x();
//    int idY = point.y();

//    if (idX < idXo | idX > idLastX |
//        idY < idYo | idY > idLastY)
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//}

void mapOpenGLWidget::initializeGL()
{ 
    glClearColor(0.0, 0.0, 0.0, 0.0); // фон
    glShadeModel(GL_SMOOTH);    // Включить тень сглаживать

    glClearDepth(1.0);          // Установка кэша глубины
    glEnable(GL_DEPTH_TEST);    // Включить тест глубины
    glDepthFunc(GL_LEQUAL);     // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLfloat position[] = {0.0,0.0,-3.0,1.0};//
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //qDebug() << "InitGL";
}

void mapOpenGLWidget::resizeGL(int W, int H) // Сбрасывает размер окна OpenGL
{
    glViewport(0, 0, (GLint) W, (GLint) H); // Сброс текущего окна просмотра
    glMatrixMode(GL_PROJECTION); // Выбор матрицы проецирования
    glLoadIdentity(); // Сброс матрицы проецирования

    // Установить размер окна просмотра
    gluPerspective((GLdouble)45.0, (GLdouble)W/H, (GLdouble)0.1, (GLdouble)800.0);

    glMatrixMode(GL_MODELVIEW); // Выбор матрицы наблюдений модели
    glLoadIdentity(); // Сброс модели наблюдения Матрица
}

void mapOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    MAP_SCALE += (float) event->angleDelta().y() / 4000;

    if (MAP_SCALE < 0.016) MAP_SCALE = 0.016;

    lookX = (float) ((float)countX * MAP_SCALE) / 2;
    lookY = (float) ((float)countY * MAP_SCALE) / 2;
    lookZ = 0.0;

    update();
}

void mapOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int dX = mouseLastX - x;
    int dY = mouseLastY - y;

    mouseLastX = x;
    mouseLastY = y;

    angle = (float)dX / 500;
    angleOZ = (float)dY / 500;

    update();
}

void mapOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ClosedHandCursor);

    mousePressX = event->x();
    mousePressY = event->y();

    mouseLastX = mousePressX;
    mouseLastY = mousePressY;
}

void mapOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);

//    angle = 0;
//    angleOZ = 0;
}

//void mapOpenGLWidget::updateZD(QVector<QVector<QVector<QVector3D> > > *points)
//{
//    pointsZD = *points;
//    pZDinBorder = pointsZD;

//    //processingPointsZD();

//    update();
//}

//void mapOpenGLWidget::updatePosRLS(QList<QVector3D> *pRLS)
//{
//    posRLS = pRLS;
//}

//void mapOpenGLWidget::updateVertBoards()
//{

//    boards.clear();
//    boards.append(QVector<QVector3D>{
//                      QVector3D(idXo,    idYo, 0),
//                      QVector3D(idXo,    idYo, Hmap),
//                      QVector3D(idLastX, idYo, Hmap) });
//    boards.append(QVector<QVector3D>{
//                      QVector3D(idXo,    idYo,    0),
//                      QVector3D(idXo,    idYo,    Hmap),
//                      QVector3D(idXo,    idLastY, Hmap) });
//    boards.append(QVector<QVector3D>{
//                      QVector3D(idLastX, idLastY, 0),
//                      QVector3D(idLastX, idLastY, Hmap),
//                      QVector3D(idLastX, idYo,    Hmap) });
//    boards.append(QVector<QVector3D>{
//                      QVector3D(idLastX, idLastY, 0),
//                      QVector3D(idLastX, idLastY, Hmap),
//                      QVector3D(idXo,    idLastY, Hmap)});
//}

void mapOpenGLWidget::initializeTerrain(int idXo_, int idYo_, int numW, int numL)
{
    qDebug() << "Init terrain OpenGL";

    // Запрещаем отрисовку
    readyRender = false;

    // Дискреты углов
    idXo = idXo_;            // Левый верхний
    idYo = idYo_;
    idLastX = idXo + numW; // Правый нижний
    idLastY = idYo + numL;

    // Размер области
    countX = numW; // Ширина
    countY = numL; // Высота

    MAP_SCALE = 0.3;

    // Расчет радиуса вращения камеры
    if (countX > countY) R = countX * MAP_SCALE * kSCALE;
    else                 R = countY * MAP_SCALE * kSCALE;

    // Перерасчет матрицы высот
    heights.clear();
    for (int idX = idXo; idX < idLastX; idX++)
    {
        heights.append(QVector <int>(countY));
        for (int idY = idYo; idY < idLastY; idY++)
        {
            heights.last()[idY] = mapInformer->getH(idX, idY, Coords::id);
        }
    }

    // Обновляем взор камеры
    lookX = (float) ((float)countX * MAP_SCALE) / 2;
    lookY = (float) ((float)countY * MAP_SCALE) / 2;
    lookZ = 0.0;

    // Разрешаем отрисовку
    readyRender = true;

    qDebug() << "Ready terrain OpenGL";

    // Рисуем обновленную картинку
    update();
}

//void mapOpenGLWidget::updateTerrain(int idXo_, int idYo_, int W, int L)
//{
//    // Сразу выходим если никак не попадаем в область отображения
//    if (idXo_ > idLastX | idYo_ > idLastY) return;

//    // Правая нижняя точка зоны изменения
//    int lastIdX = idXo_ + W;
//    int lastIdY = idYo_ + L;

//    // Если частично попадаем в область
//    if (idXo_ < idXo) idXo_ = idXo;
//    if (idYo_ < idYo) idYo_ = idYo;

//    //
//    if (lastIdX > idLastX) lastIdX = idLastX;
//    if (lastIdY > idLastY) lastIdY = idLastY;

//    //
//    if (lastIdX < idXo | lastIdY < idYo) return;

//    //
//    for (int idX = idXo_; idX < lastIdX; idX++)
//    {
//        for (int idY = idYo_; idY < lastIdY; idY++)
//        {
//            heights[idX-idXo][idY-idYo] = map->getHeight(idX, idY);
//        }
//    }

//    // Показываем обновленное
//    update();
//}

//void mapOpenGLWidget::updateTerrain()
//{
//    for (int idX = 0; idX < countX; idX++)
//    {
//        for (int idY = 0; idY < countY; idY++)
//        {
//            heights[idX][idY] = map->getHeight(idXo + idX, idYo + idY);
//        }
//    }

//    update();
//}

void mapOpenGLWidget::paintGL()
{
    if (readyRender)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen и глубина кэша

        lastAngle -= angle;
        lastAngleOZ -= angleOZ;

        camX = lookX + ((float)cos(lastAngle)*R);
        camY = lookY + ((float)sin(lastAngle)*R);
        camZ = lookZ + ((float)(lastAngleOZ)*R);

        glLoadIdentity();
        gluLookAt(camX, camZ, camY,
                  lookX, lookZ, lookY,
                  0, 1.0, 0);

        H_SCALE = MAP_SCALE * 0.7;

        const QImage& currentTexture = mapInformer->getGeoImage();

        QRgb color;
        int h;
        for (int idX = 0; idX < countX - 1; idX++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (int idY = 0; idY < countY - 1; idY++)
            {
                h = heights[idX][idY];
                color = currentTexture.pixel(idXo + idX, idYo + idY);
                glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
                addVertex(idXo + idX, idYo + idY, h);

                h = heights[idX][idY+1];
                color = currentTexture.pixel(idXo + idX, idYo + idY + 1);
                glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
                addVertex(idXo + idX, idYo + idY + 1, h);

                h = heights[idX+1][idY];
                color = currentTexture.pixel(idXo + idX+1, idYo + idY);
                glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
                addVertex(idXo + idX+1, idYo + idY, h);

                h = heights[idX+1][idY+1];
                color = currentTexture.pixel(idXo + idX+1, idYo + idY+1);
                glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
                addVertex(idXo + idX+1, idYo + idY + 1, h);
            }
            glEnd();
        }

//        glBegin(GL_LINES);
//        glColor3f(0.39, 0.05, 0.67); // цвет линий

//        // Отрисовка зоны обнаружения
//        float a = 0.3;
//        glColor4f(0.0, 0.0, 0.8, // цвет
//                  a);            // прозрачность
//        QVector3D p;
//        if (pZDinBorder.size() > 0)
//        {   // по РЛС
//            for (int idRLS=0; idRLS<pZDinBorder.size(); idRLS++)
//            {
//                // по горизонтальным сегментам
//                int countL = pZDinBorder[idRLS][0].size();
//                for (int idL=0; idL < countL-1; idL++)
//                {
//                    // по левым нижним точкам в квадратах
//                    glBegin(GL_TRIANGLE_STRIP);
//                    for (int idP = 0; idP < pZDinBorder[idRLS].size() - 1; idP++)
//                    {
//                        drawRectZD(idRLS, idL, idP);
//                    }

//                    // замыкаем слой
//                    drawRectZD(idRLS, idL, 0);

//                    glEnd();
//                }

//                p = posRLS->at(idRLS); // точка стояния РЛС
//                if (p.x() > idXo & p.x() < (idXo + countX) &
//                    p.y() > idYo & p.y() < (idYo + countY))
//                {
//                    /* Надо будет вычислять в какой точке пересекаются лучи в плоскостями топоражения 3D */

//                    // замыкаем верх
//                    int countV = pZDinBorder[idRLS].size();
//                    glBegin(GL_TRIANGLE_STRIP);
//                    for (int t = 0; t < countV; t++)
//                    {
//                        p = pZDinBorder[idRLS][t].last();
//                        //glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);
//                        addVertex(p.x(), p.y(), p.z());

//                        p = posRLS->at(idRLS); // точка стояния РЛС
//                        //glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);
//                        addVertex(p.x(), p.y(), p.z());

//                    }
//                    glEnd();

//                    // замыкаем низ
//                    glBegin(GL_TRIANGLE_STRIP);
//                    for (int t = 0; t < countV; t++)
//                    {
//                        p = pZDinBorder[idRLS][t][0];
//                        glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);

//                        p = posRLS->at(idRLS);
//                        glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);

//                    }
//                    glEnd();
//                }
//            }
//        }

//        // Отрисовка траектории
//        glBegin(GL_LINES);
//        glColor3f(1.0, 0.0, 0.8); // цвет линий

//        int countPoints = trail.size();
//        QVector3D point;
//        for (int i=0; i<countPoints-1; i++)
//        {
//            point = trail[i];
//            glVertex3f(point.x()*MAP_SCALE,
//                       point.z()*H_SCALE,
//                       point.y()*MAP_SCALE);

//            point = trail[i+1];
//            glVertex3f(point.x()*MAP_SCALE,
//                       point.z()*H_SCALE,
//                       point.y()*MAP_SCALE);
//        }

//        glEnd();
    }
}

//void mapOpenGLWidget::drawRectZD(int idRLS, int idLayer, int idPointLeft)
//{
//    int x, y, z;
//    int& idL = idLayer;
//    int& idP = idPointLeft;

//    QVector3D pZD = pZDinBorder[idRLS][idP][idL];
//    x = pZD.x();
//    y = pZD.y();
//    z = pZD.z();
//    addVertex(x, y, z);

//    pZD = pZDinBorder[idRLS][idP+1][idL];
//    x = pZD.x();
//    y = pZD.y();
//    z = pZD.z();
//    addVertex(x, y, z);

//    pZD = pZDinBorder[idRLS][idP][idL+1];
//    x = pZD.x();
//    y = pZD.y();
//    z = pZD.z();
//    addVertex(x, y, z);

//    pZD = pZDinBorder[idRLS][idP+1][idL+1];
//    x = pZD.x();
//    y = pZD.y();
//    z = pZD.z();
//    addVertex(x, y, z);
//}

void mapOpenGLWidget::addVertex(int idX, int idY, int idZ)
{
     glVertex3f((idX - idXo) * MAP_SCALE, (GLfloat)idZ * H_SCALE, (idY - idYo) * MAP_SCALE);
}
