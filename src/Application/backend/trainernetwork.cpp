#include "trainernetwork.h"

#include <QDebug>

#include <QApplication>

trainerNetwork::trainerNetwork()
{

}

void trainerNetwork::run(const QString &dirImgs,
                         const QString &dirRewards,
                         int coutEpoch,
                         const QString &nameNet)
{
    QString dirRun = QApplication::applicationDirPath().replace("/", "\\");

    QString dirApp = dirRun;
    QString dirNets = dirRun + "\\Models\\";

    QString strC = dirApp     + "\\buildTrain.exe " +
                   dirImgs    + " " +
                   dirRewards + " " +
                   dirNets    + nameNet + " " +
                   QString::number(coutEpoch);
    //qDebug() << strC;
    system(strC.toStdString().data());

    updateListModels();
}
