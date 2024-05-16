#include "rls.h"

#include "gis/geoblock.h"

#include <QDebug>

#include <cmath>

RLS::RLS(TracerLight* RayTracer, RZCreator* RZEditor, HeightMeter* Height,
         QPoint* position_, const QString& nameRLS):
    RayTracer(RayTracer), RZEditor(RZEditor), Height(Height),
    name(nameRLS), position(position_)
{
    //Hpos = (double) map->getHeight(position->x(), position->y(), Map::m) + hSender;

    mE = new double [2];

    set_lDV();
    buildZD();

    D = 2000;

    working = false;
}

void RLS::getPosition(QVector3D &point)
{
    // в индексах
    point.setX(position->x());
    point.setY(position->y());
    point.setZ(1234);
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
    Hzd = 99999; //map->getLenBlock();
    working_ = working;
}

void RLS::setPosition(int X, int Y)
{
    position->setX(X);
    position->setY(Y);

    // сразу считаем высоту, на которую ставим РЛС в этой позиции
    //Hpos = (double) map->getHeight(position->x(), position->y()) * Ray::mH + hSender;
    //Hpos = (double) map->getHeight(X, Y, Map::m) + hSender;
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
    // Сообщаем GUI об начале применнения настроек
    startSetOpt(sizeZD + COUNT_VECTORS_vert);

    // Построение ЗО в верт. плоскости
    set_lDV();  // диаграмма направленности
    updateDV(); // ЗО

    // Построение всей ЗО (по кругу)
    removeZD();
    buildZD();

    readyOptZDvert();
    getDataGraphic();
}

void RLS::emitSignal()
{
    // Если РЛС не включена, то ничего не делаем
    if (!working) return;

    // Кол-во вертикальных сегментов
    int countS_ZD = ZD.size();

    //
    int xRLS = position->x();
    int yRLS = position->y();
    QVector3D posRLS(xRLS, yRLS, Height->absolute(xRLS, yRLS, Map::id)+1);

    //qDebug() << posRLS;

    // Дискрета РЛС по умолчанию в ЗО
    blocksZD.clear();
    blocksZD.append(posRLS);
    RZEditor->toZD(posRLS);

    int idLastBlock;
    // По вертикальным сегментам
    for (int i=0; i<countS_ZD; i++)
    {
        // По лучам в сегменте
        int countLZD = ZD.at(i)->size();
        for (int j=0; j<countLZD; j++)
        {
            //
            idLastBlock = blocksZD.size() - 1;

            // Полет луча
            RayTracer->emitRay(ZD[i]->at(j), posRLS, blocksZD);

            // Заряжаем дискереты РЛ сигналом
            int c = blocksZD.size();
            for (int i=idLastBlock; i<c; i++)
            {
                RZEditor->toZD(blocksZD[i]);
            }
        }
        readyVector(i);
    }

    qDebug() << "RLS: emit signal finish!";

    finishGenerateZD();
}

const QVector <QVector <QVector3D>>& RLS::getPointsInterZD()
{
    return interPointsZD;
}

void RLS::clearZD()
{
    if (blocksZD.size() > 0)
    {
        int count = blocksZD.size();
        for (int i=0; i<count; i++)
            RZEditor->clearZD(blocksZD[i]);
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
    if (e > Emax && e < (double)Pi/2) return 0.0;

    return 0.0;
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
    int w = D / 20.0; //map->getLenBlock();

    idX = position->x() - w;
    idY = position->y() - w;

    W = w * 2;
    H = W;
}

RLS::~RLS()
{
    // Очистка блоков от сигнала данной РЛС
    clearZD();

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
    // Очищаем память от дискретных значений угла
    delete [] mE;

    //
    delete position;
}
