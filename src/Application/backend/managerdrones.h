#ifndef MANAGERDRONES_H
#define MANAGERDRONES_H

#include <QObject>
#include <QList>

#include "drone.h"

class managerDrones: public QObject
{
    Q_OBJECT

public slots:
    //
    void createDrone();

    //
    void removeDrone(int idDrone);

public:
    managerDrones();

private:
    //
    QList <Drone*> drones;
};

#endif // MANAGERDRONES_H
