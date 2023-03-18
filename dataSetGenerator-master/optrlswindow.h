#ifndef OPTRLSWINDOW_H
#define OPTRLSWINDOW_H

#include <QWidget>

#include "map.h"
#include "qcustomplot.h"
#include "paintermapimage.h"

namespace Ui {
class optRLSwindow;
}

class optRLSwindow : public QWidget
{
    Q_OBJECT
signals:
    // запуск моделирования РЛС
    void signalRunRLS(int x, int y, int H); // позиция и срез высот

    // запросить данные для графика ДН антены
    void getDataGraphic();

    // обновить пар-ры ЗО в вертикальной плоскости
    void updateOptZDvert(int Rmax); // в метрах

    //
    void getColorHeight(QColor* color, int height);

public slots:
    // перерисовать график ДН
    void repaintGraphic(double* x, double* y, int count);

    // обновить координаты РЛС
    void updateCoordRLS(int x, int y); // индексы блоков карты

    // начало моделирования работы РЛС
    void startGenerateZD(int countVectors); // кол-во вертикальных сегментов

    // номер готового верт-го сегмента
    void readyVector(int numVector);

    //
    void finishGenerateZD();

    //
    void readyOptZDvert();

    // обновить все, что зависит от пар-ов карты
    void updateInfoMap();

public:
    explicit optRLSwindow(Map* map_, QWidget *parent = 0);
    ~optRLSwindow();

private slots:
    void runRLS();

    void updateHZD(int);

    // уcтановить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert();

private:
    QCursor cursor;

    void updateColorH();

    Map* map;

    QColor* colorH;

    QCustomPlot* cPlot;

    // в индексах блоков карты
    int xRLS;
    int yRLS;
    int hRLS;

    int hZD;

    Ui::optRLSwindow *ui;
};

#endif // OPTRLSWINDOW_H
