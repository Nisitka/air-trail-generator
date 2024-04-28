#ifndef OPTRLSWINDOW_H
#define OPTRLSWINDOW_H

#include <QWidget>

#include "backend/gis/map.h"
#include "backend/gis/paintermapimage.h"
#include "plotwidget.h"

#include "processtmpwidget.h"

namespace Ui {
class optRLSwindow;
}

class optRLSwindow : public QWidget
{
    Q_OBJECT
signals:
    // запустить поиск оптимальной позиции РЛС
    void sendDataForSearchBestPos(int idXo, int idYo, int W, int L, int idMaxH);

    // создать новую РЛС
    void createRLS(QPoint* posRLS, const QString& nameNewRLS);

    // удалить РЛС
    void delRLS(int id);

    // выбрать РЛС
    void setRLS(int id);

    // установить новую позицию РЛС
    void setPositionRLS(int idX, int idY);

    // запуск моделирования РЛС
    void signalRunRLS(int H); // срез высот

    // выключить РЛС(т.е. очистить от РЛ поля)
    void signalOffRLS();

    // запросить данные для графика ДН антены
    void getDataGraphic();

    // обновить пар-ры ЗО в вертикальной плоскости
    void updateOptZDvert(int Rmax, // в метрах
                         int countVertVectors, int countPointsDV); // кол-водискрет

public slots:
    // инициализация новой РЛС завершина
    void buildNewRLSready();

    // установить параметры РЛС
    void setOptRLS(int Rmax, int Xpos, int Ypos, int Hzd, bool working);

    // начало изменения настроек прогресса
    void startSetOptRLS(int sizeP); // кол-во дискрет прогресса

    // обновить полоску прогресса установки настроек РЛС
    void updateProgressSetOptRLS(int id); // номер текущей дискреты

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

public:
    explicit optRLSwindow(Map* map_, QWidget *parent = 0);
    ~optRLSwindow();

private slots:
    //
    void runSearchBestPos();

    // изменить точку постановки выбранной РЛС
    void setNewPosRLS();

    void enablingRLS();

    // уcтановить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert();

    void addRLS();

    void removeRLS();

private:

    // работает ли выбранная РЛС
    bool workingCurRLS;

    void setDesine();

    QStringList namesRLS;

    Map* map;

    plotWidget* graphicWidget;

    // координаты РЛС
    int xRLS; // в индексах блоков карты
    int yRLS;
    int hRLS;

    // срез высоты ЗО
    int hZD;

    //
    processTmpWidget* loadingWidget;

    Ui::optRLSwindow *ui;
};

#endif // OPTRLSWINDOW_H
