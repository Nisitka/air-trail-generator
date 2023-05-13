#ifndef MANAGERRLS_H
#define MANAGERRLS_H

#include <QObject>
#include <QRect>

#include "map.h"
#include "rls.h"

// класс для управления всеми РЛС
class managerRLS : public QObject
{
    Q_OBJECT
signals:
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

    // сообщаем об начале поиска лучшей позиции РЛС
    void startSearchBestPos(int numW, int numL, int sizeProgress);

    // обновляем полоску прогресса поиска лучшей позиции
    //void

    // отправляем результаты поиска наилучшей позиции
    void readySearchBestPos(int idX, int idY, double* K);

public slots:
    // поиск лучшей позиции для выбранной РЛС
    void searchBestPosRLS(int idXo, int idYo, int W, int L, int idMaxH);

    // создать новую РЛС
    void addRLS(QPoint* posRLS);

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
    void updateVisInfoRLS();

    //
    void readyVecRLS();

private:
    // сколько вертикальных сегментов готово
    int curVecReady;

    void emitSignalAllRLS();

    // все РЛС
    QList <RLS*> listRLS;
    int idCurRLS; // индекс выбранной РЛС

    Map* map;
};

#endif // MANAGERRLS_H
