#include "buildertraildrones.h"

#include <QApplication>

#include <QDebug>

#include <cmath>
#include "ray.h"

builderTrailDrones::builderTrailDrones(double* angleEDrone)
{ 
    aEDrone = angleEDrone;

    dirInputData = QApplication::applicationDirPath() + "/inputData.jpg";

    dirProgram = "C:\\Users\\20-konkova.a.n\\PycharmProjects\\untitled2\\buildsEXE\\dist\\cApp\\model.exe";
    dirOutData = "C:\\Users\\20-konkova.a.n\\PycharmProjects\\untitled2\\outDataNet.txt";
    dirNet = "C:\\Users\\20-konkova.a.n\\PycharmProjects\\untitled2\\Models\\model3\\model3.meta";

    outFile = new QFile;
    openOutFile();

    processNet = new QProcess(this);
    connect(processNet, SIGNAL(finished(int)),
            this,       SLOT(netFinish()));
    connect(processNet, SIGNAL(error(QProcess::ProcessError)),
            this,       SLOT(failedProcess(QProcess::ProcessError)));

    /*
    qDebug() << matchE(100, 100, 0, 0);
    qDebug() << matchE(100, 100, 18, 123);
    qDebug() << matchE(100, 100, 167, 192);
    qDebug() << matchE(100, 100, 189, 92);
    qDebug() << matchE(100, 100, 110, 100);
    */
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
    {
        points.append(new QPoint(curIdX, curIdY));
        if (matchD(curIdX, curIdY, idXb, idYb) > 50)
        {
            // устанавливаем облать прогноза
            setRect(curIdX, curIdY);

            // устанавливаем азимут конечной точки
            *aEDrone = matchE(curIdX, curIdY, idXb, idYb);
        }
        else
        {
            qDebug() << "finish predict trail!";
            points.append(new QPoint(idXb, idYb));
            setRect(idXb, idYb);
            typeP = rect;

            finishPredictTrail();
        }
    }
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

    //QString strC = "C:\\Users\\20-konkova.a.n\\PycharmProjects\\untitled2\\buildsEXE\\dist\\cApp\\model.exe C:\\Users\\20-konkova.a.n\\Desktop\\trainImages\\netImg_0.jpg C:\\Users\\20-konkova.a.n\\PycharmProjects\\untitled2\\outDataNet.txt C:\\Users\\20-konkova.a.n\\PycharmProjects\\untitled2\\Models\\testModel3\\testModel3.meta";
    QString strC = dirProgram   + " " +
                   dirInputData + " " +
                   dirOutData   + " " +
                   dirNet;

    system(strC.toStdString().data());
    netFinish();
}

void builderTrailDrones::startPredictTrail(int idXa, int idYa, int idXb_, int idYb_)
{
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

    points.append(new QPoint(curIdX, curIdY));
    if (matchD(curIdX, curIdY, idXb, idYb) > 50)
    {
        setRect(curIdX, curIdY);

        // устанавливаем азимут конечной точки
        *aEDrone = matchE(curIdX, curIdY, idXb, idYb);
    }
    else
    {
        qDebug() << "finish predict trail!";
        points.append(new QPoint(idXb, idYb));
        setRect(idXb, idYb);
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

void builderTrailDrones::openOutFile()
{
    delete outFile;
    outFile = new QFile(dirOutData);

    if (!outFile->open(QIODevice::ReadOnly)) qDebug() << "ошибка открытия файла";
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
