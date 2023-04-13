#include "buildertraildrones.h"

#include <QApplication>

#include <QDebug>

#include <cmath>
#include "ray.h"

builderTrailDrones::builderTrailDrones(double* angleEDrone)
{ 
    aEDrone = angleEDrone;

    QString dirApp = QApplication::applicationDirPath();

    dirInputData = dirApp + "\\inputData.jpg";

    dirProgram = dirApp + "\\model.exe";
    dirOutData = dirApp + "\\outDataNet.txt";
    dirNets = dirApp + "\\Models\\";

    // создание/открытие файла выходной информации
    outFile = NULL;
    setOutFile();

    processNet = new QProcess(this);
    connect(processNet, SIGNAL(finished(int)),
            this,       SLOT(netFinish()));
    connect(processNet, SIGNAL(error(QProcess::ProcessError)),
            this,       SLOT(failedProcess(QProcess::ProcessError)));
}

void builderTrailDrones::predictToRect(const QString &nameNet)
{
    setNameModel(nameNet);
    buildInputData(dirInputData);
}
void builderTrailDrones::predictToRect()
{
    buildInputData(dirInputData);
}

void builderTrailDrones::netFinish()
{
    int x, y;
    // заменяем текущую точку БПЛА
    readOutData(x, y);
    curIdX = idXo + x;
    curIdY = idYo + y;

    // если интересует прогноз только в квадрате то отдаем результат
    if (typeP == rect)
    {
        resultPredictRect(curIdX, curIdY); // уже в обсолютных id
    }
    else
    {// иначе записывем точку и прогназируем следующую
        points.append(new QPoint(curIdX, curIdY));
        predictNextPoint();
    }
}

void builderTrailDrones::setNameModel(const QString &nameModel_)
{
    nameModel = nameModel_;
}

void builderTrailDrones::readySetRect(int idXo_, int idYo_)
{
    idXo = idXo_;
    idYo = idYo_;

    // если в данный момент прогнозируем траекторию,
    // то осуществляем прогноз области
    if (typeP == trail)
    {
        predictToRect();
    }
}

void builderTrailDrones::usedNet()
{
    /*
    QStringList argv;
    argv << dirInputData << dirOutData << dirNet;
    processNet->start(dirProgram, argv, QProcess::ReadOnly);
    */

    QString strC = dirProgram   + " " +
                   dirInputData + " " +
                   dirOutData   + " " +
                   dirNets + "\\" + nameModel + "\\" + nameModel + ".meta";

    system(strC.toStdString().data());
    netFinish();
}

void builderTrailDrones::startPredictTrail(const QString& nameModel,
                                           int idXa, int idYa, int idXb_, int idYb_)
{
    setNameModel(nameModel);

    curIdX = idXa;
    curIdY = idYa;

    idXb = idXb_;
    idYb = idYb_;

    // тип прогноза - траектория
    typeP = trail;

    // очищаем память от старых точек
    for (int i=0; i<points.size(); i++)
    {
        delete points[i];
    }
    // очищаем вектор от старых точек
    points.clear();
    numCurPoint = 0;

    points.append(new QPoint(curIdX, curIdY));
    predictNextPoint();
}

void builderTrailDrones::predictNextPoint()
{
    if (matchD(curIdX, curIdY, idXb, idYb) > minD)
    {   // устанавливаем область прогноза и прогназируем
        if (numCurPoint%sizeFilter == 0)
        {
            setRect(curIdX, curIdY, mainP);
        }
        else
        {
            setRect(curIdX, curIdY, midP);
        }
        numCurPoint++;

        // устанавливаем азимут конечной точки
        *aEDrone = matchE(curIdX, curIdY, idXb, idYb);
    }
    else
    {
        qDebug() << "finish predict trail!";
        points.append(new QPoint(idXb, idYb));
        setRect(idXb, idYb, mainP);
        typeP = rect;

        finishPredictTrail();
    }
}

double builderTrailDrones::matchD(int idXa, int idYa, int idXb, int idYb)
{
    return sqrt(pow(idXa - idXb, 2) + pow(idYa - idYb, 2));
}

double builderTrailDrones::matchE(int idXa, int idYa, int idXb, int idYb)
{
    double dX = idXb - idXa;
    double dY = idYb - idYa;

    // определение четверти точки
    int numS;
    if (dX <  0 && dY <= 0) numS = 1;
    if (dX >= 0 && dY <  0) numS = 2;
    if (dX <= 0 && dY >  0) numS = 3;
    if (dX >  0 && dY >= 0) numS = 4;
    dX = abs(dX);
    dY = abs(dY);

    double e;
    switch (numS) {
    case 1:
        e = 360 - Ray::toGrad(atan(dX / dY));
        break;
    case 2:
        e = Ray::toGrad(atan(dX / dY));
        break;
    case 3:
        e = 270 - Ray::toGrad(atan(dY / dX));
        break;
    case 4:
        e = 90 + Ray::toGrad(atan(dY / dX));
        break;
    }

    return e;
}

void builderTrailDrones::failedProcess(QProcess::ProcessError error)
{
    qDebug() << "failedProcess"; //.arguments();
}

void builderTrailDrones::setOutFile()
{
    delete outFile;
    outFile = new QFile(dirOutData);

    // если файла нет, то создаем его
    if (!outFile->open(QIODevice::ReadOnly))
    {
        //
        outFile->open(QIODevice::ReadWrite);
    }
    outFile->close();
}

void builderTrailDrones::readOutData(int &x, int &y)
{
    outFile->open(QIODevice::ReadOnly);

    QByteArray data;
    data = outFile->readAll();

    QStringList coords = QString(data).split(" ", QString::SkipEmptyParts);
    x = coords[X].toInt();
    y = coords[Y].toInt();

    outFile->close();
}
