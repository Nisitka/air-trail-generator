#ifndef MANAGERRLS_H
#define MANAGERRLS_H

#include <QObject>
#include <QRect>

#include "../GIS/heightmeter.h"
#include "../GIS/rzcreator.h"

#include "../tracerlight.h"
#include "rls.h"

#include <memory>

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

    //
    void startEmitSignal();
    void finishGenerateZD();
    void exportGraphicData(double* X, double* Y, int countPoint);
    void readyOptZDvert();
    void clearZD();
    void startSetOpt();
    void startClearZD();

    //
    void changeStatProcessing(int percent); // В процентах

public slots:
    // перемоделировать сигналы всех РЛС
    void updateSignals();

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
    void runRLS(); // срез высоты
    // установить поз. РЛС и смод-ть сигнал
    void runRLS(int, int); // индексы дискрет гор. координат

    void getDataGraphic();
    void setOptZDvert(int,int,int);

public:
    managerRLS(TracerLight* RayTracer, RZCreator* RZEditor, HeightMeter* Height);

private:

    //
    void emitSignalAllRLS();

    // Для испускания сигнала
    TracerLight* RayTracer;
    RZCreator* RZEditor;
    HeightMeter* Height;

    // сколько вертикальных сегментов готово
    int curVecReady;

    // все РЛС
    QList <RLS*> listRLS;
    int idCurRLS; // индекс выбранной РЛС

    //
    QVector<QVector<QVector<QVector3D>>>* pointsInterZD;
    //
    QList <QVector3D>* posRLS;
};

#endif // MANAGERRLS_H
