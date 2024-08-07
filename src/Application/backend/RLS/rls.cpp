#include "rls.h"

#include <cmath>

#include <QDebug>

RLS::RLS(TracerLight* RayTracer, RZCreator* RZEditor, HeightMeter* Height,
         QPoint* position, const QString& nameRLS):
    RayTracer(RayTracer), RZEditor(RZEditor), Height(Height),
    name(nameRLS)
{
    setPosition(*position);

    mE = new double [2];

    set_lDV();
    buildZD();

    D = 2000;

    working = false;
}

void RLS::setPosition(int idX, int idY)
{ 
    pos.setX(idX);
    pos.setY(idY);

    // Cразу считаем высоту, для этой позиции
    pos.setZ(Height->absolute(idX, idY, Coords::id));
}

void RLS::setPosition(const QPoint &p)
{
    int idX = p.x();
    int idY = p.y();

    pos.setX(idX);
    pos.setY(idY);

    // Cразу считаем высоту, для этой позиции
    pos.setZ(Height->absolute(idX, idY, Coords::id));
}

int RLS::getCountHorVectors() const
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

void RLS::getOpt(int &Rmax, int &Xpos, int &Ypos, int &Hzd, bool &working_) const
{
    Rmax = D;
    Xpos = pos.x();
    Ypos = pos.y();
    Hzd = 99999; /// !!!!!!!!
    working_ = working;
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
    }
    ZD.clear();
}

void RLS::setOptZDvert(int Rmax,
                       int countVertVectors, int countPointsDV)
{
    //qDebug() << "Set new option RLS!";

    // Сообщаем GUI об начале применнения настроек
    startSetOpt();

    count_PointsDV = countPointsDV;
    COUNT_VECTORS_vert = countVertVectors;
    D = Rmax;

    sizeZD = ZD.size();


    // Построение ЗО в верт. плоскости
    set_lDV();  // диаграмма направленности
    updateDV(); // ЗО

    // Построение всей ЗО (по кругу)
    removeZD();
    buildZD();

    getDataGraphic();

    //
    readyOptZDvert();
}

void RLS::emitSignal()
{
    //qDebug() << "Emit Signal!";

    // Если РЛС не включена, то ничего не делаем
    if (!working) return;

    //
    startEmitSignal();

    // Кол-во вертикальных сегментов
    int countS_ZD = ZD.size();

    // Через какое кол-во сегментов уведомлять об состоянии
    int dV = countS_ZD / 100;
    int iV = 0;

    //
    int xRLS = pos.x();
    int yRLS = pos.y();
    QVector3D posRLS(xRLS, yRLS, Height->absolute(xRLS, yRLS, Coords::id)+1);

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
            ///qDebug() << "111111111111111111";
            RayTracer->emitRay(ZD[i]->at(j), posRLS, blocksZD);
            ///qDebug() << "444444444444444444";

            // Заряжаем дискереты РЛ сигналом
            int c = blocksZD.size();
            for (int i=idLastBlock; i<c; i++)
            {
                RZEditor->toZD(blocksZD[i]);
            }
            ///qDebug() << "555555555555555555";
        }

        // Уведомляем, если изменение > 1%
        if (iV<dV) iV++;
        else
            changeStatProcessing(((double) i/countS_ZD) * 100);
    }

    //qDebug() << "RLS: emit signal finish!";

    finishGenerateZD();
}

const QVector <QVector <QVector3D>>& RLS::getPointsInterZD()
{
    return interPointsZD;
}

void RLS::clearZD()
{
    int count = blocksZD.size();
    if (count > 0)
    {
        startClearZD();

        // Через какое кол-во блоков уведомлять об состоянии
        int dB = count / 100;
        int iB = 0;

        for (int i=0; i<count; i++)
        {
            RZEditor->clearZD(blocksZD[i]);

            // Уведомляем, если изменение > 1%
            if (iB<dB) iB++;
            else
                changeStatProcessing(((double) i/count) * 100);
        }
        blocksZD.clear();

        readyClearZD();
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

void RLS::getRectPosition(int &idX, int &idY, int &W, int &H) const
{
    // Кол-во дискрет в ширину
    int w = D / Height->lenghtBlock();

    idX = pos.x() - w;
    idY = pos.y() - w;

    W = w * 2;
    H = W;
}

RLS::~RLS()
{
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
}
