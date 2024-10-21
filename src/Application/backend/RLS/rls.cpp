#include "rls.h"

#include <cmath>

#include <QDebug>

RLS::RLS(const QVector3D& position,
         const QString& nameRLS)
{
    setPosition(position);

    //
    name = nameRLS;

    mE = new double [2];

    set_lDV();

    D = 2000;

    working = false;
}

double RLS::Rmax() const
{
    return D;
}

void RLS::getGraphicData(QVector<double> &X, QVector<double> &Y) const
{
    // Защита от дурака
    X.clear();
    Y.clear();

    //
    int countPoint = DV.size();
    X.resize(countPoint);
    Y.resize(countPoint);

    for (int i=0; i<countPoint; i++)
    {
        X[i] = DV.at(i)[L];
        Y[i] = DV.at(i)[H];
    }
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

void RLS::setOptZDvert(int Rmax)
{
    //qDebug() << "Set new option RLS!";

    // Сообщаем GUI об начале применнения настроек
    startSetOpt();

    D = Rmax;

    // Построение ЗО в верт. плоскости
    set_lDV();  // диаграмма направленности
    updateDV(); // ЗО

    //
    readyOptZDvert();
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
    // Очищаем память от дискретных значений угла
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

    // Сразу же считаем проекции будущих лучей
    buildDV();
}

void RLS::buildDV()
{
    // Очищаем память от предыдущей ДН
    for (int i=0; i<DV.size(); i++)
    {
        delete [] DV[i];
    }
    DV.clear();

    int count_PointsDV = l_DV.size();

    // Расчет проекций лучей в ДН
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

    // Расчет проекций лучей в верт. ЗО
    for (int i=0; i<count_PointsDV; i++)
    {
        DV.at(i)[L] = l_DV.at(i)[L] * D;
        DV.at(i)[H] = l_DV.at(i)[H] * D;
    }
}

RLS::~RLS()
{
    // Очищаем память от предыдущей lDV
    for (int i=0; i<l_DV.size(); i++)
    {
        delete [] l_DV[i];
    }
    // Очищаем память от дискретных значений угла
    delete [] mE;
}
