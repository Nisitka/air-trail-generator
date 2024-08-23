#ifndef MANAGERRLS_H
#define MANAGERRLS_H

#include <QObject>
#include <QRect>

#include "../GIS/heightmeter.h"
#include "../GIS/rzcreator.h"

#include "../tracerlight.h"
#include "rls.h"

#include <memory>

#include "informerrls.h"

// класс для управления всеми РЛС
class managerRLS : public QObject, public InformerRLS
{
    Q_OBJECT
signals:

    // Завершена инициализация РЛС
    void createReadyRLS();

    // Завершено удаление РЛС
    void deleteReadyRLS();

    // Выбрана другая РЛС
    void changeCurrentRLS();

    /// Заменить на changeSignal() !!!!
    void updateVisInfoMap(int idX, int idY, int w, int h);
    void updateVisInfoMap(QRect*, int count);

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
    void setCurrentRLS(int id); // индекс в листе

    /* Слоты только для РЛС */
    void setPositionRLS(int idX, int idY);

    // выключить РЛС
    void offRLS(); // выключется выбранная РЛС

    // смоделировать сигнал по уже уст. позиции
    void runRLS(); // срез высоты
    // установить поз. РЛС и смод-ть сигнал
    void runRLS(int, int); // индексы дискрет гор. координат

    //
    void setOptZDvert(int,int,int);

public:
    managerRLS(TracerLight* RayTracer, //
               RZCreator* RZEditor,    //
               HeightMeter* Height);   //

    // Узнать индекс выбранной РЛС
    int idCurrentRLS() const;

    // Получить интерфейс выбранной РЛС
    const LabelRLS* currentRLS() const;

    // Узнать общее кол-во РЛС
    int countRLS() const;

    // Получить интерфейс РЛС по id
    const LabelRLS* getInfoRLS(int idRLS) const;

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
