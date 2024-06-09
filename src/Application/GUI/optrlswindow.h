#ifndef OPTRLSWINDOW_H
#define OPTRLSWINDOW_H

#include <QWidget>

#include "backend/GIS/gisinformer.h"
#include "plotwidget.h"

#include "processtmpwidget.h"

namespace Ui {
class optRLSwindow;
}

class optRLSwindow : public QWidget
{
    Q_OBJECT
signals:
    // Запустить поиск оптимальной позиции РЛС
    void sendDataForSearchBestPos(int idXo, int idYo, int W, int L, int idMaxH);

    // Создать новую РЛС
    void createRLS(QPoint* posRLS, const QString& nameNewRLS);

    // Удалить РЛС
    void delRLS(int id);

    // Выбрать РЛС
    void setRLS(int id);

    // Установить новую позицию РЛС
    void setPositionRLS(int idX, int idY);

    // Запуск моделирования работы РЛС
    void signalRunRLS();

    // Выключить РЛС(т.е. очистить от РЛ поля)
    void signalOffRLS();

    // запросить данные для графика ДН антены
    void getDataGraphic();

    // обновить пар-ры ЗО в вертикальной плоскости
    void updateOptZDvert(int Rmax, // в метрах
                         int countVertVectors, int countPointsDV); // кол-водискрет

public slots:

    // Отображение выполнения процессов
    void startProcessing();
    void updateStatProcessing(int percent); // В процентах
    void finishProcessing();

    // Инициализация новой РЛС завершина
    void buildNewRLSready();

    // Установить параметры РЛС
    void setOptRLS(int Rmax, int Xpos, int Ypos, int Hzd, bool working);

    // Начало изменения настроек прогресса
    void startSetOptRLS(int sizeP);

    // Обновить полоску прогресса установки настроек РЛС
    void updateProgressSetOptRLS(int id); // номер текущей дискреты

    // Перерисовать график ДН
    void repaintGraphic(double* x, double* y, int count);

    // Обновить координаты РЛС
    void updateCoordRLS(Coords);

    // Начало моделирования работы РЛС
    void startGenerateZD(int countVectors); // кол-во вертикальных сегментов

    // Номер готового верт-го сегмента
    void readyVector(int numVector);

    //
    void finishGenerateZD();

    //
    void readyOptZDvert();

public:
    explicit optRLSwindow(QWidget *parent = 0);
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

    // Работает ли выбранная РЛС
    bool workingCurRLS;

    // Названия всех РЛС
    QStringList namesRLS;

    // Для графика ДН
    plotWidget* graphicWidget;

    // Координаты РЛС
    Coords RLScoords;

    //
    processTmpWidget* loadingWidget;

    void setDesine();
    Ui::optRLSwindow *ui;
};

#endif // OPTRLSWINDOW_H
