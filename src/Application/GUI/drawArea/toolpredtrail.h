#ifndef TOOLPREDTRAIL_H
#define TOOLPREDTRAIL_H

#include "GUI/drawArea/drawareatool.h"

class ToolPredTrail: public drawAreaTool
{
    Q_OBJECT
signals:
    //
    void sendPointsTrail(int idXa, int idYa, int idXb, int idYb);

public slots:

    //
    void startPredictTrail();
    void finishPredictTrail();

    // Добавить точку траектории
    void addPointTrail(int idXpt, int idYpt, int idZpt);

public:
    ToolPredTrail(areaDrawWidget*, int id, QObject *parent = 0);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

private:
    //
    drawTask <ToolPredTrail>* dTask;

    //
    QVector <QPoint*> trail;
    void clearTrail();

    // точки для задания траектории
    QPoint lastPoint;  // в индексах карты
    QPoint beginPoint; // в индексах карты

    // иконки оконечных точек
    QPixmap* pixBeginDrone;  // начала
    QPixmap* pixFinishDrone; // конца

    // Радиус прогноза в итерации
    int R = 50;
};

#endif // TOOLPREDTRAIL_H
