#include "rls.h"

#include <cmath>

#include <QDebug>

RLS::RLS(LabelRLS infoRLS): LabelRLS(infoRLS)
{
    mE = new double [2];

    setDV();
}

void RLS::setPosition(int idX, int idY, int idH)
{ 
    pos.setX(idX);
    pos.setY(idY);
    pos.setZ(idH);
}

void RLS::setPosition(const QVector3D& pos_)
{
    pos = pos_;
}

void RLS::on()
{
    working = true;
}

void RLS::off()
{
    working = false;
}

double RLS::functionDV(double e)
{
    if (e > 0 && e <= Emin) return 1 - (double) (Emin - e) / Emin;
    if (e > Emin && e < Eo) return 1.0;
    if (e >= Eo && e <= Emax) return sin(Eo) / sin(e);
    if (e > Emax && e < (double)Pi/2) return 0.0;

    return 0.0;
}

void RLS::setDV()
{
    // Очищаем память от предыдущей lDV
    DV.clear();
    DV.resize(count_PointsDV);

    // Очищаем память от дискретных значений угла
    delete [] mE;

    // Создание массива дискретных значений угла
    mE = new double[count_PointsDV]; // дискретные значения угла места
    double dE = (double)Pi * 0.49 / count_PointsDV;
    for (int i=1; i<=count_PointsDV; i++)
        mE[i-1] = i*dE; // инициализируем дискреты углов

    for (int i=0; i<count_PointsDV; i++)
    {
        DV[i].setY(functionDV(mE[i]) * sin(mE[i])); //
        DV[i].setX(functionDV(mE[i]) * cos(mE[i])); //
    }
}

RLS::~RLS()
{
    // Очищаем память от предыдущей DV
    DV.clear();

    // Очищаем память от дискретных значений угла
    delete [] mE;
}
