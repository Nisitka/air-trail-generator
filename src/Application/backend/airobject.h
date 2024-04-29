#ifndef AIROBJECT_H
#define AIROBJECT_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDockWidget>
#include <QtWidgets>
#include "GUI/airobjectfunwindow.h"
#include "GUI/multiplewindow.h"

namespace Ui {
class AirObject;
}

class AirObject : public QMainWindow
{
    Q_OBJECT
signals:

    void show_AirObject(QString);
    void creat_AirObject(QString, double,double,double, QString);

public:
    explicit AirObject(QWidget *parent = nullptr);
    ~AirObject();

private slots:

    void loading_AirObject(QString, QString);

    void show_AirObject();
    void show_AirObject(QString, double,double,double, QString);
    void creat_AirObject();
    void clearBoxs();

    void dowPhoto();
private:


    
    Ui::AirObject *ui;
};

#endif // AIROBJECT_H
