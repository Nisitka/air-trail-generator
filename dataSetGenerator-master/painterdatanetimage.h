#ifndef PAINTERDATANETIMAGE_H
#define PAINTERDATANETIMAGE_H

#include "painterimage.h"

class painterDataNetImage : public painterImage
{
    Q_OBJECT
signals:
    // начало генерации образа
    void startGenerateImg(int sizeP);

    // информируем об текущей строке в генерации
    void readyStringDataNet(int numString);

    void readyInputData();

    // информируем о том, что квадрат установлен
    void readyRect(int idXo, int idYo); // левый верхний угол

public slots:
    void run();

    // сохранить изображение
    void saveImage(const QString& dirName);

    // изменить пар-ры генерации цветов
    void updateKrgb(double kG1, double kG2,
                    double kpD1, double kpD2,
                    double kB1);

    //
    void setRect(int idXo, int idYo);

    //
    void generateInputData(const QString& dirSaveImg);

public:
    painterDataNetImage(Map*, double* E);

private:
    const double Pi = 3.1415926;

    double* E; // азимут конечной точки

    int zX;
    int zY;

    // подсчет зеленого цвета
    int matchGreen(int idX, int idY);

    // пар-ры зеленого цвета
    double kG1 = 0.6;
    double kG2 = 0.05;
    double kpD1 = 0.4;
    double kpD2 = 0.8;

    // пар-ры синиго цвета
    double kB1 = 0.02;

    //
    int idXo, idYo;

    QImage createSubImage(const QRect& rect);
};

#endif // PAINTERDATANETIMAGE_H
