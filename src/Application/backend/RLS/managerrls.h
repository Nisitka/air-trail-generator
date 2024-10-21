#ifndef MANAGERRLS_H
#define MANAGERRLS_H

#include <QObject>
#include <QRect>

#include "../GIS/heightmeter.h"

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

    //
    void exportGraphicData(double* X, double* Y, int countPoint);

public slots:

    // создать новую РЛС
    void addRLS(const QPoint& posRLS, const QString& nameRLS);

    // удалить РЛС
    void delRLS(int id); // индекс в листе, которую удаляем

    // выбрать РЛС
    void setCurrentRLS(int id); // индекс в листе

    /* Слоты только для РЛС */
    void setPositionRLS(int idX, int idY);

    // выключить РЛС
    void offRLS(); // выключется выбранная РЛС

    // смоделировать сигнал по уже уст. позиции
    void runRLS();

public:
    managerRLS(HeightMeter* heightInfo);   //

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
    HeightMeter* heightInfo;

    // все РЛС
    QList <RLS*> listRLS;
    int idCurRLS; // индекс выбранной РЛС
};

#endif // MANAGERRLS_H
