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

mapOpenGLWidget::mapOpenGLWidget(Map* map,
                                 QImage* imgTex,
                                 QLabel* wFrameOX, QLabel* wFrameOY, QLabel* wFrameXY,   
                                 QWidget *parent):
    map(map), QOpenGLWidget(parent),
    wFrameOX(wFrameOX), wFrameOY(wFrameOY), wFrameXY(wFrameXY),
    camX(0), camY(0), camZ(0),
    lookX(0), lookY(0), lookZ(0),
    angle(0), lastAngle(1.57),
    angleOZ(0), lastAngleOZ(1.0)
{
    winWidth=300;winHeight=200;

    currentTexture = imgTex;

    Hmap = map->getMaxH() / map->getLenBlock();
    //qDebug() << Hmap;
    //
    wFrameOX->setScaledContents(true);
    wFrameOY->setScaledContents(true);
    wFrameXY->setScaledContents(true);

    //parent->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->setMinimumSize(winWidth,winHeight);
    this->setMaximumSize(9999, 9999);
}

void mapOpenGLWidget::startPredictTrail()
{
    trail.clear();
}

void mapOpenGLWidget::addTrailPoint(int idX, int idY, int idZ)
{
    trail.append(QVector3D(idX, idY, idZ));

    update();
}

void mapOpenGLWidget::finishPredictTrail()
{

}

bool mapOpenGLWidget::isIntersectBorder(const QVector3D &pA, const QVector3D &pB, QVector <QVector3D>& pointsInter)
{
    pointsInter.clear();

    // Если отрезок находится в зоне отрисовки то не считаем
    if (isDrawArea(pA) & isDrawArea(pB)) return false;

    int countInter = 0;
    pointsInter.append(QVector3D());
    pointsInter.append(QVector3D());

    QVector3D pCurInter;
    QVector3D shortInter;

    // Проверяем на пер-я с границами зоны отображения
    for (int idB = 0; idB < 4; idB++)
    {
        if (isInterFlatness(pA, pB,
                            boards[idB][vert::A], boards[idB][vert::B], boards[idB][vert::C],
                            pCurInter))
        {
            countInter++;

            if(countInter == 2)
            {
                if (pCurInter.distanceToPoint(pB) < shortInter.distanceToPoint(pB))
                {
                    pointsInter[interVert::Short] = pCurInter;
                    pointsInter[interVert::Long]  = shortInter;
                }
                else
                {
                    pointsInter[interVert::Short] = shortInter;
                    pointsInter[interVert::Long]  = pCurInter;
                }

                // т.к. макс-м может быть 2 точки то
                return true;
            }
            else
            {
                shortInter = pCurInter;
            }
        }
    }

    // если дошли до сюда значит точка одна
    pointsInter[interVert::Short] = shortInter;
    pointsInter.remove(interVert::Long);

    return true;
}

bool mapOpenGLWidget::isInterFlatness(const QVector3D &A, const QVector3D &B,
                                      const QVector3D &pA, const QVector3D &pB, const QVector3D &pC,
                                      QVector3D &interPoint)
{
    //
    QVector3D N = QVector3D::normal(pA, pB, pC);

    QVector3D V = pA - A;

    // Расстояние до плоскости по нормали
    float d = QVector3D::dotProduct(N, V);
    //qDebug() << d;

    QVector3D W = A - B;
    float e = QVector3D::dotProduct(N, W);

    // Точка пер-я
    QVector3D& O = interPoint;

    // Одна точка пер-я прямой
    if (e != 0.0)
    {
        O = A + (W * ((float) d / e));

        // Пересекает ли отрезок
        if (QVector3D::dotProduct(A - O, B - O) <= 0)
        {
            return true;
        }
    }

    return false;
}

void mapOpenGLWidget::processingPointsZD()
{
    //qDebug() << idXo << countX << idYo << countY << Hmap;

    pZDinBorder.clear();
    pZDinBorder = pointsZD;

    // точка стояния РЛС
    QVector3D pRLS;

    //
    QVector <QVector3D> interPoints;

    //
    bool RLSfromArea = false;

    // по РЛС
    for (int idRLS=0; idRLS<pointsZD.size(); idRLS++)
    {
        pRLS = posRLS->at(idRLS);

        // РЛС в зоне отрисовки?
        RLSfromArea = isDrawArea(pRLS);

        // по гор. сегментам
        for (int idHor = 0; idHor < pointsZD[idRLS].size(); idHor++)
        {
            // по верт. сегментам
            for (int idL = 0; idL < pointsZD[idRLS][idHor].size(); idL++)
            {
                // Если есть пересечения с границами по пути от ЗО до поз. РЛС
                if (isIntersectBorder(pointsZD[idRLS][idHor][idL], pRLS, interPoints))
                {
                    // Если РЛС в зоне отрисовки
                    if (RLSfromArea)
                    {
                        pZDinBorder[idRLS][idHor][idL] = interPoints[interVert::Short];
                    }
                    else
                    {
                        /* ... */
                    }
                }
            }
        }
    }
}

bool mapOpenGLWidget::isDrawArea(const QVector3D &point)
{
    int idX = point.x();
    int idY = point.y();

    if (idX < idXo | idX > idLastX |
        idY < idYo | idY > idLastY)
    {
        return false;
    }
    else
    {
        return true;
    }
}

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

    setFrameOX(0.5);
    setFrameOY(0.5);
    setFrameXY(0.5);
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

    angle = 0;
    angleOZ = 0;
}

void mapOpenGLWidget::updateZD(QVector<QVector<QVector<QVector3D> > > *points)
{
    pointsZD = *points;
    pZDinBorder = pointsZD;

    processingPointsZD();

    update();
}

void mapOpenGLWidget::updatePosRLS(QList<QVector3D> *pRLS)
{
    posRLS = pRLS;

    //qDebug() << *posRLS;
}

void mapOpenGLWidget::updateVertBoards()
{
    boards.clear();
    boards.append(QVector<QVector3D>{
                      QVector3D(idXo,    idYo, 0),
                      QVector3D(idXo,    idYo, Hmap),
                      QVector3D(idLastX, idYo, Hmap) });
    boards.append(QVector<QVector3D>{
                      QVector3D(idXo,    idYo,    0),
                      QVector3D(idXo,    idYo,    Hmap),
                      QVector3D(idXo,    idLastY, Hmap) });
    boards.append(QVector<QVector3D>{
                      QVector3D(idLastX, idLastY, 0),
                      QVector3D(idLastX, idLastY, Hmap),
                      QVector3D(idLastX, idYo,    Hmap) });
    boards.append(QVector<QVector3D>{
                      QVector3D(idLastX, idLastY, 0),
                      QVector3D(idLastX, idLastY, Hmap),
                      QVector3D(idXo,    idLastY, Hmap)});
}

void mapOpenGLWidget::initializeTerrain(int idXo_, int idYo_, int numW, int numL)
{
    //
    idXo = idXo_;
    idYo = idYo_;
    countX = numW;
    countY = numL;
    idLastX = idXo + countX;
    idLastY = idYo + countY;

    //
    Hmap = map->getCountLayers();

    //
    updateVertBoards();

    //
    processingPointsZD();

    //
    float k = (float)countX / countY;
    if (countX > countY)
    {
        wFrameXY->setFixedWidth(maxWLabel);
        wFrameXY->setFixedHeight(maxWLabel/k);
    }
    else
    {
        wFrameXY->setFixedHeight(maxHLabel);
        wFrameXY->setFixedWidth(k*maxHLabel);
    }

    MAP_SCALE = 0.3;

    if (countX > countY) R = countX * MAP_SCALE * kSCALE;
    else                 R = countY * MAP_SCALE * kSCALE;

    heights.clear();
    for (int idX = idXo; idX < idLastX; idX++)
    {
        heights.push_back(QVector<int>());
        for (int idY = idYo; idY < idLastY; idY++)
        {
            heights.last().push_back(map->getHeight(idX, idY));
        }
    }

    lookX = (float) ((float)countX * MAP_SCALE) / 2;
    lookY = (float) ((float)countY * MAP_SCALE) / 2;
    lookZ = 0.0;

    //qDebug() << MAP_SCALE;

    update();
}

void mapOpenGLWidget::colorHeight(int h, float& r, float& g, float& b)
{
    dHeight = Hmap / colors.size();

    int id = h / dHeight;
    // если предельный цвет
    if (id >= colors.size() - 1)
    {
        QColor color = colors[colors.size() - 1];

        r = color.red();
        g = color.green();
        b = color.blue();

        r = (float) r/255;
        g = (float) g/255;
        b = (float) b/255;
    }
    else
    {
        QColor currentColor = colors[id];
        QColor nextColor = colors[id + 1];

        double part = double(h%dHeight) / dHeight;

        r = currentColor.red();
        g = currentColor.green();
        b = currentColor.blue();

        r += (nextColor.red() - currentColor.red()) * part;
        g += (nextColor.green() - currentColor.green()) * part;
        b += (nextColor.blue() - currentColor.blue()) * part;

        r = (float) r/255;
        g = (float) g/255;
        b = (float) b/255;
    }
}

QColor mapOpenGLWidget::colorHeight(int h)
{
    dHeight = Hmap / colors.size();

    int r,g,b;

    int id = h / dHeight;
    // если предельный цвет
    if (id >= colors.size() - 1)
    {
        QColor color = colors[colors.size() - 1];

        r = color.red();
        g = color.green();
        b = color.blue();
    }
    else
    {
        QColor currentColor = colors[id];
        QColor nextColor = colors[id + 1];

        double part = double(h%dHeight) / dHeight;

        r = currentColor.red();
        g = currentColor.green();
        b = currentColor.blue();

        r += (nextColor.red() - currentColor.red()) * part;
        g += (nextColor.green() - currentColor.green()) * part;
        b += (nextColor.blue() - currentColor.blue()) * part;
    }

    return QColor(r,g,b);
}

void mapOpenGLWidget::updateTerrain(int idXo_, int idYo_, int size)
{
    // Сразу выходим если никак не попадаем в область отображения
    if (idXo_ > idLastX | idYo_ > idLastY) return;

    idXo_ -= size/2;
    idYo_ -= size/2;

    int lastIdX = idXo_ + size;
    int lastIdY = idYo_ + size;

    //
    if (lastIdX < idXo | lastIdY < idYo) return;

    // Если частично попадаем в область
    if (idXo_ < idXo) idXo_ = idXo;
    if (idYo_ < idYo) idYo_ = idYo;

    if (lastIdX > idXo+countX) lastIdX = idLastX;
    if (lastIdY > idYo+countY) lastIdY = idLastY;

    for (int idX = idXo_; idX < lastIdX; idX++)
    {
        for (int idY = idYo_; idY < lastIdY; idY++)
        {
            heights[idX-idXo][idY-idYo] = map->getHeight(idX, idY);
        }
    }

    update();
}

void mapOpenGLWidget::updateTerrain()
{
    for (int idX = 0; idX < countX; idX++)
    {
        for (int idY = 0; idY < countY; idY++)
        {
            heights[idX][idY] = map->getHeight(idXo + idX, idYo + idY);
        }
    }

    update();
}

void mapOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen и глубина кэша

    /*/// !!!!!!!!!!!!!!!!!!!!!!!!!!
    //
    GLuint textureID;
    glEnable(GL_TEXTURE_2D);
    QImage texImg;
    glGenTextures(1, &textureID);
    texImg = QGLWidget::convertToGLFormat(*currentTexture);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //glTexSubImage2D();
    //glTexImage2D
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLsizei)texImg.width(),
                 (GLsizei)texImg.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texImg.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    /// !!!!!!!!*/

    lastAngle -= angle;
    lastAngleOZ -= angleOZ;

    camX = lookX + ((float)cos(lastAngle)*R);
    camY = lookY + ((float)sin(lastAngle)*R);
    camZ = lookZ + ((float)(lastAngleOZ)*R);

    glLoadIdentity();
    gluLookAt(camX, camZ, camY,
              lookX, lookZ, lookY,
              0, 1.0, 0);

    H_SCALE = MAP_SCALE * 0.2;

    QRgb color;
    int h;
    for (int idX = 0; idX < countX - 1; idX++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int idY = 0; idY < countY - 1; idY++)
        {
            h = heights[idX][idY];
            color = currentTexture->pixel(idX, idY);
            glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
            addVertex(idXo + idX, idYo + idY, h);

            h = heights[idX][idY+1];
            color = currentTexture->pixel(idX, idY + 1);
            glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
            addVertex(idXo + idX, idYo + idY + 1, h);

            h = heights[idX+1][idY];
            color = currentTexture->pixel(idX+1, idY);
            glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
            addVertex(idXo + idX+1, idYo + idY, h);

            h = heights[idX+1][idY+1];
            color = currentTexture->pixel(idX+1, idY+1);
            glColor3ub(GLint(qRed(color)), GLint(qGreen(color)), GLint(qBlue(color)));
            addVertex(idXo + idX+1, idYo + idY + 1, h);
        }
        glEnd();
    }

    /*/// !!!!!
    // Удаление текстуры
    glBindTexture(GL_TEXTURE_2D, 0); // Отвязка активной текстуры
    glDeleteTextures(1, &textureID);
    glDisable(GL_TEXTURE_2D);
    /// !!!!!!!!!!!!!!!!!!!!!!!!!!*/

    glBegin(GL_LINES);
    glColor3f(0.39, 0.05, 0.67); // цвет линий

    // Отрисовка рамки для оси ОХ
    float lineX = idFrameX * MAP_SCALE;

    glVertex3f(0, 0, lineX);
    glVertex3f(0, H_SCALE*Hmap, lineX);

    glVertex3f(0, H_SCALE*Hmap, lineX);
    glVertex3f(MAP_SCALE*(countX-1), H_SCALE*Hmap, lineX);

    glVertex3f(MAP_SCALE*(countX-1), H_SCALE*Hmap, lineX);
    glVertex3f(MAP_SCALE*(countX-1), 0, lineX);

    glEnd();

    // Отрисовка рамки для оси ОY
    glBegin(GL_LINES);
    glColor3f(0.39, 0.05, 0.67); // цвет линий

    float lineY = idFrameY * MAP_SCALE;

    glVertex3f(lineY, 0, 0);
    glVertex3f(lineY, H_SCALE*Hmap, 0);

    glVertex3f(lineY, H_SCALE*Hmap, 0);
    glVertex3f(lineY, H_SCALE*Hmap, MAP_SCALE*(countY-1));

    glVertex3f(lineY, H_SCALE*Hmap, MAP_SCALE*(countY-1));
    glVertex3f(lineY, 0, MAP_SCALE*(countY-1));

    glEnd();

    // Отрисовка рамки для плоскости XY
    glBegin(GL_LINES);
    glColor3f(0.39, 0.05, 0.67); // цвет линий

    float lineZ = idFrameZ * H_SCALE;

    glVertex3f(0, lineZ, 0);
    glVertex3f(0, lineZ, MAP_SCALE*(countY-1));

    glVertex3f(0, lineZ, MAP_SCALE*(countY-1));
    glVertex3f(MAP_SCALE*(countX-1), lineZ, MAP_SCALE*(countY-1));

    glVertex3f(MAP_SCALE*(countX-1), lineZ, MAP_SCALE*(countY-1));
    glVertex3f(MAP_SCALE*(countX-1), lineZ, 0);

    glVertex3f(MAP_SCALE*(countX-1), lineZ, 0);
    glVertex3f(0, lineZ, 0);

    glEnd();

    // Отрисовка зоны обнаружения
    float a = 0.3;
    glColor4f(0.0, 0.0, 0.8, // цвет
              a);            // прозрачность
    QVector3D p;
    if (pZDinBorder.size() > 0)
    {   // по РЛС
        for (int idRLS=0; idRLS<pZDinBorder.size(); idRLS++)
        {
            // по горизонтальным сегментам
            int countL = pZDinBorder[idRLS][0].size();
            for (int idL=0; idL < countL-1; idL++)
            {
                // по левым нижним точкам в квадратах
                glBegin(GL_TRIANGLE_STRIP);
                for (int idP = 0; idP < pZDinBorder[idRLS].size() - 1; idP++)
                {
                    drawRectZD(idRLS, idL, idP);
                }

                // замыкаем слой
                drawRectZD(idRLS, idL, 0);

                glEnd();
            }

            p = posRLS->at(idRLS); // точка стояния РЛС
            if (p.x() > idXo & p.x() < (idXo + countX) &
                p.y() > idYo & p.y() < (idYo + countY))
            {
                /* Надо будет вычислять в какой точке пересекаются лучи в плоскостями топоражения 3D */

                // замыкаем верх
                int countV = pZDinBorder[idRLS].size();
                glBegin(GL_TRIANGLE_STRIP);
                for (int t = 0; t < countV; t++)
                {
                    p = pZDinBorder[idRLS][t].last();
                    //glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);
                    addVertex(p.x(), p.y(), p.z());

                    p = posRLS->at(idRLS); // точка стояния РЛС
                    //glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);
                    addVertex(p.x(), p.y(), p.z());

                }
                glEnd();

                // замыкаем низ
                glBegin(GL_TRIANGLE_STRIP);
                for (int t = 0; t < countV; t++)
                {
                    p = pZDinBorder[idRLS][t][0];
                    glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);

                    p = posRLS->at(idRLS);
                    glVertex3f((p.x() - idXo) * MAP_SCALE, p.z() * H_SCALE, (p.y() - idYo) * MAP_SCALE);

                }
                glEnd();
            }
        }
    }

    // Отрисовка траектории
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.8); // цвет линий

    int countPoints = trail.size();
    QVector3D point;
    for (int i=0; i<countPoints-1; i++)
    {
        point = trail[i];
        glVertex3f(point.x()*MAP_SCALE,
                   point.z()*H_SCALE,
                   point.y()*MAP_SCALE);

        point = trail[i+1];
        glVertex3f(point.x()*MAP_SCALE,
                   point.z()*H_SCALE,
                   point.y()*MAP_SCALE);
    }

    glEnd();
}

void mapOpenGLWidget::drawRectZD(int idRLS, int idLayer, int idPointLeft)
{
    int x, y, z;
    int& idL = idLayer;
    int& idP = idPointLeft;

    QVector3D pZD = pZDinBorder[idRLS][idP][idL];
    x = pZD.x();
    y = pZD.y();
    z = pZD.z();
    addVertex(x, y, z);

    pZD = pZDinBorder[idRLS][idP+1][idL];
    x = pZD.x();
    y = pZD.y();
    z = pZD.z();
    addVertex(x, y, z);

    pZD = pZDinBorder[idRLS][idP][idL+1];
    x = pZD.x();
    y = pZD.y();
    z = pZD.z();
    addVertex(x, y, z);

    pZD = pZDinBorder[idRLS][idP+1][idL+1];
    x = pZD.x();
    y = pZD.y();
    z = pZD.z();
    addVertex(x, y, z);
}

void mapOpenGLWidget::addVertex(int idX, int idY, int idZ)
{
     glVertex3f((idX - idXo) * MAP_SCALE, idZ * H_SCALE, (idY - idYo) * MAP_SCALE);
}

void mapOpenGLWidget::setFrameOX(float partW)
{
    idFrameY = round((float) (countX-1) * partW);

    int& W = countY;
    int& H = Hmap;

    qDebug() << H;

    QImage img(W, H, QImage::Format_RGB32);

    int maxH = 0;
    for (int y = 0; y < W; y++)
    {
        maxH = heights[idFrameY][y];
        for (int h = 0; h < H; h++)
        { 
            QColor color(0, 0, 0);
            if (h < maxH)
            {
                color = colorHeight(h);
            }
            else
            {
                if (map->getBlock(idFrameY+idXo, y+idYo, h)->isZD())
                {
                    color.setRgb(0,0,255);
                }
            }
            img.setPixelColor(y, H - h - 1, color);
        }
    }

    QPixmap pix = QPixmap::fromImage(img);
    wFrameOX->setPixmap(pix);

    update();
}

void mapOpenGLWidget::setFrameOY(float partW)
{
    idFrameX = round((float) (countY-1) * partW);

    int& W = countX;
    int& H = Hmap;

    QImage img(W, H, QImage::Format_RGB32);

    int maxH = 0;
    for (int x = 0; x < W; x++)
    {
        maxH = heights[x][idFrameX];
        for (int h = 0; h < H; h++)
        {
            QColor color(0, 0, 0);
            if (h < maxH)
            {
                color = colorHeight(h);
            }
            else
            {
                if (map->getBlock(idXo+x, idYo+idFrameX, h)->isZD())
                {
                    color.setRgb(0,0,255);
                }
            }
            img.setPixelColor(x, H - h - 1, color);
        }
    }

    QPixmap pix = QPixmap::fromImage(img);
    wFrameOY->setPixmap(pix);

    update();
}

void mapOpenGLWidget::setFrameXY(float partW)
{
    idFrameZ = round((float) (Hmap-1) * partW);

    int& W = countX;
    int& L = countY;

    QImage img(W, L, QImage::Format_RGB32);

    int h = 0;
    for (int x = 0; x < W; x++)
    {
        for (int y = 0; y < L; y++)
        {
            QColor color(0, 0, 0);

            h = heights[x][y];
            if (h >= idFrameZ)
            {
                color = colorHeight(idFrameZ);
            }
            else
            {
                if (map->getBlock(idXo+x, idYo+y, idFrameZ)->isZD())
                {
                    color.setRgb(0,0,255);
                }
            }
            img.setPixelColor(x, y, color);
        }
    }

    QPixmap pix = QPixmap::fromImage(img);
    wFrameXY->setPixmap(pix);

    update();
}
