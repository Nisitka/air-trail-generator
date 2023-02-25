#include "rls.h"

#include "geoblock.h"

#include <QDebug>

#include <cmath>

RLS::RLS(Map* map_, QObject *parent) : QObject(parent), map(map_)
{
    set_lDV();
    buildZD();
}

void RLS::setPosition(double X, double Y)
{
    position.setX(X);
    position.setY(Y);

    // сразу считаем высоту, на которую ставим РЛС в этой позиции
    Hpos = (double) map->getHeight(position.x(), position.y()) * Ray::mH + hSender;
}

void RLS::setOptZDvert(int Rmax)
{
    D = Rmax;
    updateDV();
    getDataGraphic();

    for (int i=0; i<ZD.size(); i++)
    {
        QVector <Ray*>* rays = ZD[i];
        for (int j=0; j<rays->size(); j++)
        {
            delete rays->at(j);
        }
    }

    ZD.clear();
    buildZD();
}

void RLS::run(int xPos, int yPos, int srez_H)
{
    setPosition(xPos, yPos);

    int Wmap = map->getWidth();
    int Lmap = map->getLength();
    int Hmap = map->getCountLayers();

    // кол-во вертикальных сегментов
    int countS_ZD = ZD.size();

    startGenerateZD(countS_ZD);

    // очистка всех блоков от сигнала
    for (int x=0; x<Wmap; x++)
    {
        for (int y=0; y<Lmap; y++)
        {
            for (int h=0; h<Hmap; h++)
            {
                map->getBlock(x, y, h)->removeZD();
            }
        }
    }

    int num_Hmin = Hpos / Ray::mH; // индекс слоя мин-ой высоты

    // полет лучей сигнала

    // по вертикальным сегментам
    for (int i=0; i<countS_ZD; i++)
    {   // по лучам в сегменте
        for (int j=0; j<ZD.at(i)->size(); j++)
        {
            QVector <int*>* way = ZD[i]->at(j)->getWay();
            int idX;
            int idY;
            int idH;

            // полет луча
            for (int k=1; k<way->size(); k++)
            {   // в пути луча содержатся относительные индексы
                idX = position.x() + way->at(k)[Ray::X];
                idY = position.y() + way->at(k)[Ray::Y];
                idH = 1 + num_Hmin + way->at(k)[Ray::Z];

                // если луч вышел за карту
                if (idY >= Lmap) break;
                if (idY < 0) break;

                if (idX >= Wmap) break;
                if (idX < 0) break;

                if (idH >= Hmap) break;
                if (idH < 0) break;

                //
                if (idH > srez_H) break;

                // если блок на пути, является землей, то
                if (map->getBlock(idX, idY, idH)->isEarth())
                {
                    //qDebug() << "луч столкнулся с рельефом";
                    break;
                }
                else
                {
                    map->getBlock(idX, idY, idH)->toZD();
                }
            }
        }
        readyVector(i);
    }

    finishGenerateZD();
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
    }

    readyOptZDvert();
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
