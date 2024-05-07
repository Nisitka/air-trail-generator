#ifndef AIROBJECTFUNWINDOW_H
#define AIROBJECTFUNWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "multiplewindow.h"
#include "backend/airobject.h"
#include "airwindow.h"
#include "airinfowindow.h"


class AirObjectFunWindow : public MultipleWindow
{
    Q_OBJECT
signals:

    void creat_AirObject(QString,double,double,double,QString);
    void show_AirObject(QString);
    void loading_AirInfo(QString, QString);
    void cleareBoxs();

public:
    AirObjectFunWindow();
public slots:

    void loading_AirObject(QString, QString);
    void clearBoxs();
    void show_AirObject(AirInfoWindow*);


private:

//    QLabel *photoLabel, *nameLabel, *longLabel, *wigthLabel, *speedLabel;
//    QLineEdit *photoEdit, *nameEdit, *longEdit, *wigthEdit, *speedEdit;
//    QWidget *wid;
//    AirWindow *AirWin = new AirWindow;
//    AirObject *airObj;

    AirWindow *AirWin;
};

#endif // AIROBJECTFUNWINDOW_H
