#ifndef TRAINERNETWORK_H
#define TRAINERNETWORK_H

#include <QObject>

class trainerNetwork: public QObject
{
    Q_OBJECT

signals:
    // обновить список моделей
    void updateListModels();

public slots:
    void run(const QString& dirImgs,
             const QString& dirRewards,
             int coutEpoch,
             const QString& nameNet);

public:
    trainerNetwork();
};

#endif // TRAINERNETWORK_H
