#ifndef AIROBJECT_H
#define AIROBJECT_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDockWidget>
#include <QtWidgets>

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

    QDockWidget *dockWidget;
    QLabel *nameLabel;
    QLabel *longsLabel;
    QLabel *weightLabel;
    QLabel *speedLabel;

    QLineEdit* nameEdit;
    QLineEdit* longsEdit;
    QLineEdit* nweightEdit;
    QLineEdit* speedEdit;

    QGridLayout *leftLayout;
    QWidget *widget;

    
    Ui::AirObject *ui;
};

#endif // AIROBJECT_H
