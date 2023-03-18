#ifndef BUILDERTRAILDRONES_H
#define BUILDERTRAILDRONES_H

#include <QObject>
#include <QFile>
#include <QIODevice>

#include <QProcess>

#include <QPoint>
#include <QVector>

// генерирует скртный маршрут
class builderTrailDrones : public QObject
{
    Q_OBJECT
signals:
    void buildInputData(const QString& dirSaveImg);

    // установить угол конечной точки
    void setAngleE(double E);

    // выдача результатов прогноза в квадрате
    void resultPredictRect(int idX, int idY); // индексы дискреты

    // установить квадрат обзора
    void setRect(int idX, int idY);

    // завершение прогноза траектории
    void finishPredictTrail();

public slots:
    // начать прогноз траектории от точки до точки
    void startPredictTrail(int idXa, int idYa,
                           int idXb, int idYb);

    // область прогноза установлена
    void readySetRect(int idXo, int idYo);

    // начать прогноз в прямоугольнике
    void predictToRect();

    // запустить сеть
    void usedNet();

public:
    builderTrailDrones(double* angleEDrone);

private slots:
    void netFinish();

    void failedProcess(QProcess::ProcessError error);

private:
    // азимут БПЛА
    double* aEDrone;

    // тип прогноза
    enum typePredict{rect, trail}; // в квадрате, от А до B
    int typeP;

    // совокупность точек - траектория
    QVector <QPoint*> points;

    // текущие координаты БПЛА
    int curIdX;
    int curIdY;

    int idXb, idYb;

    // азимут конечной точки (град.)
    double matchE(int idXa, int idYa,  // нач. точка
                  int idXb, int idYb); // кон. точка

    // посчитать расстояние между точками
    double matchD(int idXa, int idYa,  // нач. точка
                  int idXb, int idYb); // кон. точка)

    void openOutFile();
    void readOutData(int& x, int& y);
    enum coordsId{X, Y};

    // путь к exe использования сети
    QString dirProgram;
    // путь к файлу модели
    QString dirNet;

    // путь к файлу образа (входной инф.)g
    QString dirInputData;

    // путь к файлу координат (выходной инф.)
    QString dirOutData;

    // файл с данными от нейронной сети
    QFile* outFile;

    QProcess* processNet;

    // левый верхний угол обл. прогнозирования
    int idXo, idYo;
};

#endif // BUILDERTRAILDRONES_H
