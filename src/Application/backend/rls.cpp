#include "rls.h"

#include "geoblock.h"

#include <QDebug>

#include <cmath>

RLS::RLS(Map* map_, QPoint* position_, const QString& nameRLS, QObject *parent) : QObject(parent), map(map_)
{
    name = nameRLS;

    position = position_;
    Hpos = (double) map->getHeight(position->x(), position->y(), Map::m) + hSender;

    mE = new double [2];

    set_lDV();
    buildZD();

    maxHzd = 20;

    D = 2000;

    working = false;
}

void RLS::getPosition(QVector3D &point)
{
    // в индексах
    point.setX(position->x());
    point.setY(position->y());
    point.setZ(minHzd);
}

int RLS::getCountMaxBlocksZD()
{
    int maxCountBlocks = 0;

    // кол-во вертикальных сегментов
    int countS_ZD = ZD.size();

    // по вертикальным сегментам
    for (int i=0; i<countS_ZD; i++)
    {
        // по лучам в сегменте
        int countLZD = ZD.at(i)->size(); // кол-во лучей
        for (int j=0; j<countLZD; j++)
        {
            QVector <int*> way = ZD[i]->at(j)->getWay();

            // полет луча
            int idX, idY, idH;
            int countDelta = way.size(); // кол-во дискрет одного луча
            for (int k=1; k<countDelta; k++)
            {   // в пути луча содержатся относительные индексы
                int* l = way[k];

                // если индексы пренадлежат отличному от предыдущего блока
                if (idX!=l[Ray::X] || idY!=l[Ray::Y] || idH!=l[Ray::Z])
                {
                    idX = l[Ray::X];
                    idY = l[Ray::Y];
                    idH = l[Ray::Z];

                    maxCountBlocks++;
                }
            }
        }
    }

    return maxCountBlocks;
}

int RLS::getCurrentBlocksZD(int idX, int idY, int idMaxH)
{
    int countBlocksZD = 0;

    // кол-во вертикальных сегментов
    int countS_ZD = ZD.size();

    int Wmap = map->getWidth();
    int Lmap = map->getLength();
    int Hmap = map->getCountLayers();

    int xRLS = idX;
    int yRLS = idY;

    int num_Hmin = map->getHeight(xRLS, yRLS); // индекс слоя мин-ой высоты
    minHzd = num_Hmin;
    qDebug() << minHzd;

    // по вертикальным сегментам
    for (int i=0; i<countS_ZD; i++)
    {   // по лучам в сегменте
        int countLZD = ZD.at(i)->size();
        for (int j=0; j<countLZD; j++)
        {
            QVector <int*> way = ZD[i]->at(j)->getWay();
            int idX;
            int idY;
            int idH;

            // полет луча
            int countDelta = way.size(); // кол-во дискрет одного луча
            for (int k=1; k<countDelta; k++)
            {   // в пути луча содержатся относительные индексы
                int* l = way[k];

                idX = xRLS + l[Ray::X];
                idY = yRLS + l[Ray::Y];
                idH = 1 + num_Hmin + l[Ray::Z];

                // если выше среза ЗО
                if (idH > idMaxH) break;

                // если луч вышел за карту
                if (idY >= Lmap) break;
                if (idY < 0) break;

                if (idX >= Wmap) break;
                if (idX < 0) break;

                if (idH >= Hmap) break;
                if (idH < 0) break;

                geoBlock* block = map->getBlock(idX, idY, idH);
                // если блок на пути, является землей, то
                if (block->isEarth())
                {
                    // луч столкнулся с рельефом
                    break;
                }
                else
                {
                    if (!block->isZD())
                    {
                        countBlocksZD++;
                    }
                }
            }
        }
    }

    return countBlocksZD;
}

bool RLS::isWorking()
{
    return working;
}

int RLS::getCountHorVectors()
{
    return COUNT_VECTORS_vert;
}

void RLS::on()
{
    working = true;
}

void RLS::off()
{
    working = false;

    clearZD();
}

void RLS::getOpt(int &Rmax, int &Xpos, int &Ypos, int &Hzd, bool &working_)
{
    Rmax = D;
    Xpos = position->x();
    Ypos = position->y();
    Hzd = maxHzd * map->getLenBlock();
    working_ = working;
}

void RLS::setPosition(int X, int Y)
{
    position->setX(X);
    position->setY(Y);

    // сразу считаем высоту, на которую ставим РЛС в этой позиции
    //Hpos = (double) map->getHeight(position->x(), position->y()) * Ray::mH + hSender;
    Hpos = (double) map->getHeight(X, Y, Map::m) + hSender;
    minHzd = map->getHeight(X, Y, Map::id);
}

void RLS::removeZD()
{
    for (int i=0; i<sizeZD; i++)
    {
        QVector <Ray*>* rays = ZD[i];
        for (int j=0; j<rays->size(); j++)
        {
            delete rays->at(j);
        }
        delete rays;
        readySetRay(i);
    }
    ZD.clear();
}

void RLS::setOptZDvert(int Rmax,
                       int countVertVectors, int countPointsDV)
{
    count_PointsDV = countPointsDV;
    COUNT_VECTORS_vert = countVertVectors;
    D = Rmax;

    sizeZD = ZD.size();
    // сообщаем GUI об начале применнения настроек
    startSetOpt(sizeZD + COUNT_VECTORS_vert);

    // построение ЗО в верт. плоскости
    set_lDV();  // диаграмма направленности
    updateDV(); // ЗО

    // построение всей ЗО (по кругу)
    removeZD();
    buildZD();

    readyOptZDvert();
    getDataGraphic();
}

void RLS::emitSignal()
{
    // если РЛС не включена, то ничего не делаем
    if (!working) return;

    // кол-во вертикальных сегментов
    int countS_ZD = ZD.size();

    int Wmap = map->getWidth();
    int Lmap = map->getLength();
    int Hmap = map->getCountLayers();

    int xRLS = position->x();
    int yRLS = position->y();

    int num_Hmin = Hpos / map->getLenBlock(); // индекс слоя мин-ой высоты
    minHzd = num_Hmin;
    qDebug() << minHzd;

    interPointsZD.clear();
    // по вертикальным сегментам
    for (int i=0; i<countS_ZD; i++)
    {   // по лучам в сегменте
        interPointsZD.append(QVector <QVector3D>()); // добавляем список точек пер-я в сегменте
        int countLZD = ZD.at(i)->size();
        for (int j=0; j<countLZD; j++)
        {
            QVector <int*> way = ZD[i]->at(j)->getWay();
            int idX;
            int idY;
            int idH;

            // полет луча
            int countDelta = way.size(); // кол-во дискрет одного луча
            for (int k=1; k<countDelta; k++)
            {   // в пути луча содержатся относительные индексы
                int* l = way[k];

                idX = xRLS + l[Ray::X];
                idY = yRLS + l[Ray::Y];
                idH = 1 + num_Hmin + l[Ray::Z];

                //bool isBreak = false;

                // если выше среза ЗО
                if (idH > maxHzd) {
                    // то последней точкой будет предыдущая
                    idX = xRLS + way[k-1][Ray::X];
                    idY = yRLS + way[k-1][Ray::Y];
                    interPointsZD.last().push_back(QVector3D(idX, idY, maxHzd));
                    break;
                }

                // если луч вышел за карту
                if (idY >= Lmap) {
                    interPointsZD.last().push_back(QVector3D(idX, Lmap-1, idH));
                    break;
                }
                if (idY < 0) {
                    interPointsZD.last().push_back(QVector3D(idX, 0, idH));
                    break;
                }

                if (idX >= Wmap) {
                    interPointsZD.last().push_back(QVector3D(Wmap-1, idY, idH));
                    break;
                }
                if (idX < 0) {
                    interPointsZD.last().push_back(QVector3D(0, idY, idH));
                    break;
                }

                if (idH >= Hmap) {
                    interPointsZD.last().push_back(QVector3D(idX, idY, Hmap-1));
                    break;
                }
                if (idH < 0) {
                    interPointsZD.last().push_back(QVector3D(idX, idY, 0));
                    break; /*isBreak = true;*/
                }

                //if (isBreak) break;

                // блок, в котором пролетает луч
                geoBlock* block = map->getBlock(idX, idY, idH);

                // если блок на пути, является землей, то
                if (block->isEarth())
                {
                    // луч столкнулся с рельефом
                    interPointsZD.last().push_back(QVector3D(idX, idY, idH));
                    break;
                }
                else
                {   // если блок не в ЗО
                    if (!block->isZD())
                    {
                        block->toZD();
                        blocksZD.append(block); // в список блоков ЗО
                    }

                    if (k == countDelta - 1)
                        interPointsZD.last().push_back(QVector3D(idX, idY, idH));
                }
            }
        }
        readyVector(i);
    }

    //qDebug() << interPointsZD;

    finishGenerateZD();
}

const QVector <QVector <QVector3D>>& RLS::getPointsInterZD()
{
    return interPointsZD;
}

void RLS::emitSignal(int srez_H)
{
    this->on();

    // установка среза высоты
    maxHzd = srez_H;

    // очистка карты от сигнала данной РЛС
    clearZD();

    emitSignal();
}

void RLS::clearZD()
{
    if (blocksZD.size() > 0)
    {
        for (int i=0; i<blocksZD.size(); i++)
            blocksZD[i]->removeZD();
        blocksZD.clear();
    }
}

void RLS::buildZD()
{
    int count_PointsDV = DV.size();
    double dE = (double) (2 * Pi) / COUNT_VECTORS_vert;

    for (int i=0; i<COUNT_VECTORS_vert; i++)
    {
        ZD.append(new QVector <Ray*>);
        double angleE = (double) i * dE; // азимут (радианы)

        for (int j=0; j<count_PointsDV; j++)
        {
            double angleB = mE[j];
            double d = functionDV(angleB) * D; // дальность луча

            ZD.last()->append(new Ray(d, angleB, angleE));
        }
        readySetRay(sizeZD + i);
    }   
}

double RLS::functionDV(double e)
{
    if (e > 0 && e <= Emin) return 1 - (double) (Emin - e) / Emin;
    if (e > Emin && e < Eo) return 1.0;
    if (e >= Eo && e <= Emax) return sin(Eo) / sin(e);
    if (e > Emax && e < (double)Pi/2) return 0;

}

void RLS::set_lDV()
{
    // Очищаем память от предыдущей lDV
    for (int i=0; i<l_DV.size(); i++)
    {
        delete [] l_DV[i];
    }
    l_DV.clear();
    // очищаем память от дискретных значений угла
    delete [] mE;

    // Создание массива дискретных значений угла
    mE = new double[count_PointsDV]; // дискретные значения угла места
    double dE = (double)Pi * 0.49 / count_PointsDV;
    for (int i=1; i<=count_PointsDV; i++)
    {
        l_DV.append(new double[2]);
        mE[i-1] = i*dE; // инициализируем дискреты углов
    }

    for (int i=0; i<count_PointsDV; i++)
    {
        l_DV.at(i)[H] = functionDV(mE[i]) * sin(mE[i]); //
        l_DV.at(i)[L] = functionDV(mE[i]) * cos(mE[i]); //
    }

    // сразу же считаем проекции будущих лучей
    buildDV();
}

void RLS::buildDV()
{
    // очищаем память от предыдущей ДН
    for (int i=0; i<DV.size(); i++)
    {
        delete [] DV[i];
    }
    DV.clear();

    int count_PointsDV = l_DV.size();

    // расчет проекций лучей в ДН
    for (int i=0; i<count_PointsDV; i++)
    {
        DV.append(new double[2]);
        DV.last()[L] = l_DV.at(i)[L] * D;
        DV.last()[H] = l_DV.at(i)[H] * D;
    }
}

void RLS::updateDV()
{
    int count_PointsDV = l_DV.size();

    // расчет проекций лучей в верт. ЗО
    for (int i=0; i<count_PointsDV; i++)
    {
        DV.at(i)[L] = l_DV.at(i)[L] * D;
        DV.at(i)[H] = l_DV.at(i)[H] * D;
    }
}

void RLS::getDataGraphic()
{
    int countPoint = DV.size();
    double* x = new double[countPoint];
    double* y = new double[countPoint];
    for (int i=0; i<countPoint; i++)
    {
        x[i] = DV.at(i)[L];
        y[i] = DV.at(i)[H];
    }

    exportGraphicData(x, y, countPoint);
}

void RLS::getRectPosition(int &idX, int &idY, int &W, int &H)
{
    int w = D / map->getLenBlock();

    idX = position->x() - w;
    idY = position->y() - w;

    W = w * 2;
    H = W;
}

RLS::~RLS()
{
    // очистка блоков от сигнала данной РЛС
    for (int i=0; i<blocksZD.size(); i++)
    {
        blocksZD[i]->removeZD();
    }

    sizeZD = ZD.size();
    for (int i=0; i<sizeZD; i++)
    {
        QVector <Ray*>* rays = ZD[i];
        for (int j=0; j<rays->size(); j++)
        {
            delete rays->at(j);
        }
        delete rays;
    }

    // Очищаем память от предыдущей lDV
    for (int i=0; i<l_DV.size(); i++)
    {
        delete [] l_DV[i];
    }
    // очищаем память от дискретных значений угла
    delete [] mE;

    //
    delete position;
}
