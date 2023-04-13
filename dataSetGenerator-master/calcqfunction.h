#ifndef CALCQFUNCTION_H
#define CALCQFUNCTION_H

#include "painterimage.h"

#include <QFile>
#include <QTextStream>

class calcQFunction : public painterImage
{
    Q_OBJECT
signals:
    // информирование GUI
    void calcStart(int countSigment); // кол-во сигментов
    void readySigment(int idSigment);

public slots:
    void run();

    void calculate(); // только изменяем изображение
    void calculate(const QString& dir, int numFile);// и сохраняем значения в txt файл

    // установка области расчета ЦФ
    void setRect(int idXo, int idYo); // левый верхний угол области

public:
    calcQFunction(Map*, double* E);

    double static m(double v);

private:
    // точка стояния БПЛА
    int Xo;
    int Yo;

    // цвета максимума и минимума
    QColor* colorMin;
    QColor* colorMax;

    // значение функции сдвинувшись в данную позицию
    int Q(int idX, int idY, double angleE);

    // в зависимости от отчков получаем цвет
    QColor scoreToColor(int score);

    // амплетуды составляющих ЦФ
    int maxD = 600;
    int maxZD = 580;
    int maxH = 200;
    int maxScore;

    int zX;
    int zY;

    double* angleE;

    QFile* file;
    QTextStream* outData;

    // левый верхний угол области расчета
    int idXo, idYo;

    //
    double F_D(int D, double dE);
    double kG1 = 0.99;
    double kG2 = 0.2;
    double kpD1 = 0.45;
    double kpD2 = 0.8;

    //
    double F_ZD(double mZD);

    //
    double F_H(int mH); // сред. высота (в дискретах)
};


#endif // CALCQFUNCTION_H
