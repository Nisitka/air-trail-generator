#ifndef AIRWINDOW_H
#define AIRWINDOW_H

#include <QMainWindow>

namespace Ui {
class AirWindow;
}

class AirWindow : public QMainWindow
{
    Q_OBJECT
signals:

    void creat_AirObject(QString,double,double,double,QString);
    void show_AirObject(QString);
public:
    explicit AirWindow(QWidget *parent = nullptr);
    ~AirWindow();

public slots:

    void loading_AirObject(QString, QString);
    void creat_AirObject();
    void clearBoxs();
    void dowPhoto();
    void show_AirObject();

private:
    Ui::AirWindow *ui;
};

#endif // AIRWINDOW_H
