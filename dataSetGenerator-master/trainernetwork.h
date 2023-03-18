#ifndef TRAINERNETWORK_H
#define TRAINERNETWORK_H

#include <QObject>

class trainerNetwork: public QObject
{
    Q_OBJECT

public slots:
    void run(const QString& dirApp,
             const QString& dirImgs,
             const QString& dirRewards,
             int coutEpoch,
             const QString& dirNameNet);

public:
    trainerNetwork();
};

#endif // TRAINERNETWORK_H
