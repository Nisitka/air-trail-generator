#ifndef TOOLPREDTRAIL_H
#define TOOLPREDTRAIL_H

#include "GUI/drawArea/Tools/drawareatool.h"
#include "toolpredict.h"

class ToolPredTrail: public drawAreaTool, public ToolPredict
{
    Q_OBJECT
signals:
    //
    void sendPointsTrail(int idXa, int idYa, int idXb, int idYb);

    // Изменить радиус прогноза
    void setRpred(int countDiscretes);

public slots:

    //
    void startPredictTrail();
    void finishPredictTrail();

    // Добавить точку траектории
    void addPointTrail(int idXpt, int idYpt, int idZpt);

public:
    ToolPredTrail(int id, QObject *parent = 0);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void wheelEvent(QWheelEvent* event) override;

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
};

#endif // TOOLPREDTRAIL_H
