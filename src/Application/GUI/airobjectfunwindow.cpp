#include "airobjectfunwindow.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QDebug>

AirObjectFunWindow::AirObjectFunWindow()
{
    //AirWin = new AirWindow;
    this->setCentralWidget(AirWin);

    QObject::connect(AirWin, SIGNAL(creat_AirObject(QString, double,double,double, QString)),
                     this, SIGNAL(creat_AirObject(QString, double,double,double, QString))
                     );
    QObject::connect(this, SIGNAL(loading_AirInfo(QString, QString)),
                     AirWin, SLOT(loading_AirObject(QString, QString))
                     );
    QObject::connect(this, SIGNAL(cleareBoxs()),
                     AirWin, SLOT(clearBoxs())
                     );
    QObject::connect(AirWin, SIGNAL(show_AirObject(QString)),
                     this, SIGNAL(show_AirObject(QString))
                     );

    creatSplitDock();
}

void AirObjectFunWindow::show_AirObject(AirInfoWindow* AirInfo)
{
    showTmpDock(AirInfo);
}

void AirObjectFunWindow::loading_AirObject(QString ID, QString name)
{
    loading_AirInfo(ID, name);
}

void AirObjectFunWindow::clearBoxs()
{
    cleareBoxs();
}

