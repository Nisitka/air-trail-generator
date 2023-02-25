#ifndef CALCQFUNCTION_H
#define CALCQFUNCTION_H

#include "painterimage.h"

class calcQFunction : public painterImage
{
    Q_OBJECT
signals:
    // информирование GUI
    void calcStart(int countSigment); // кол-во сигментов
    void readySigment(int idSigment);

public slots:
    void run();

    void calculate(double angleE);

public:
    calcQFunction(Map*);

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

    //
    double kD = 0.3;
    double kZD = 1.3;
    double kH = 0.13;

    int zX;
    int zY;

    double angleE;
};


#endif // CALCQFUNCTION_H
