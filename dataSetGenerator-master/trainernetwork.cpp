#include "trainernetwork.h"

#include <QDebug>

trainerNetwork::trainerNetwork()
{

}

void trainerNetwork::run(const QString &dirApp,
                         const QString &dirImgs,
                         const QString &dirRewards,
                         int coutEpoch,
                         const QString &dirNameNet)
{
    QString strC = dirApp     + "\\buildTrain.exe " +
                   dirImgs    + " " +
                   dirRewards + " " +
                   dirNameNet + " " +
                   QString::number(coutEpoch);
    qDebug() << strC;
    system(strC.toStdString().data());
}
