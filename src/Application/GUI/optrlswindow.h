#ifndef OPTRLSWINDOW_H
#define OPTRLSWINDOW_H

#include <QWidget>

#include "backend/GIS/gisinformer.h"
#include "backend/RLS/informerrls.h"

//
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

    //
    void updateListRLS();

    // Отображение выполнения процессов
    void startProcessing();
    void updateStatProcessing(int percent); // В процентах
    void finishProcessing();

    // Установить параметры РЛС
    void setOptRLS(int Rmax, int Xpos, int Ypos, int Hzd, bool working);

    // Перерисовать график ДН
    void repaintGraphic(double* x, double* y, int count);

    // Обновить координаты РЛС
    void updateCoordRLS(Coords);

public:
    explicit optRLSwindow(InformerRLS* infoRLS, QWidget *parent = 0);
    ~optRLSwindow();

private slots:

    //
    void setIdCurRLS();

    // изменить точку постановки выбранной РЛС
    void setNewPosRLS();

    void enablingRLS();

    // уcтановить пар-ры ЗО в вертикальной плоскости
    void setOptZDvert();

    void addRLS();

    void removeRLS();

private:

    //
    QStringList columnNames = {"Наименование", "Статус", "Координаты"};

    //
    InformerRLS* infoRLS;
    QList <LabelRLS*> listRLS;

    // Работает ли выбранная РЛС
    bool workingCurRLS;

    //
    int idCurRLS;

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
