#ifndef MANAGERRLS_H
#define MANAGERRLS_H

#include <QObject>
#include <QRect>

#include "gis/map.h"
#include "rls.h"

#include <memory>

// класс для управления всеми РЛС
class managerRLS : public QObject
{
    Q_OBJECT
signals:
    // отправка данных для отрисовки ЗО в 3D
    void sendPointsInterZD(QVector<QVector<QVector<QVector3D>>>*, QList <QVector3D>*);

    // сообщаем GUI об завершении инициализации РЛС
    void createReadyRLS();

    void updateVisInfoMap(int idX, int idY, int w, int h);
    void updateVisInfoMap(QRect*, int count);

    // обновить данные об РЛС в интерфейсе
    void updateOptGui(int Rmax, int Xpos, int Ypos, int Hzd, bool working);

    /* Сигналы только для РЛС */
    void startGenerateZD(int);
    void readyVector(int);
    void finishGenerateZD();
    void exportGraphicData(double*, double*, int);
    void readyOptZDvert();
    void startSetOpt(int);
    void readySetRay(int);

    //
    //void

    // сообщаем об начале поиска лучшей позиции РЛС
    void startSearchBestPos(int numW, int numL, int sizeProgress);

    // обновляем полоску прогресса поиска лучшей позиции
    //void

    // отправляем результаты поиска наилучшей позиции
    void readySearchBestPos(int idX, int idY, double* K);

public slots:
    // перемоделировать сигналы всех РЛС
    void updateSignals();

    //


    // поиск лучшей позиции для выбранной РЛС
    void searchBestPosRLS(int idXo, int idYo, int W, int L, int idMaxH);

    // создать новую РЛС
    void addRLS(QPoint* posRLS, const QString& nameRLS);

    // удалить РЛС
    void delRLS(int id); // индекс в листе, которую удаляем

    // выбрать РЛС
    void setRLS(int id); // индекс в листе

    /* Слоты только для РЛС */
    void setPositionRLS(int idX, int idY);

    // выключить РЛС
    void offRLS(); // выключется выбранная РЛС

    // смоделировать сигнал по уже уст. позиции
    void runRLS(int); // срез высоты
    // установить поз. РЛС и смод-ть сигнал
    void runRLS(int, int, int); // индексы дискрет гор. координат, срез высоты

    void getDataGraphic();
    void setOptZDvert(int,int,int);

public:
    managerRLS(Map* map_);

private slots:
    //
    void readyVecRLS();

private:
    //
    void updateVisInfoRLS();
    void emitSignalAllRLS();

    // сколько вертикальных сегментов готово
    int curVecReady;

    // все РЛС
    QList <RLS*> listRLS;
    int idCurRLS; // индекс выбранной РЛС

    //
    QVector<QVector<QVector<QVector3D>>>* pointsInterZD;
    //
    QList <QVector3D>* posRLS;

    Map* map;
};

#endif // MANAGERRLS_H
