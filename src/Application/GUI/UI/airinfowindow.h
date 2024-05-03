#ifndef AIRINFOWINDOW_H
#define AIRINFOWINDOW_H

#include <QMainWindow>
#include "backend/airobject.h"
namespace Ui {
class AirInfoWindow;
}

class AirInfoWindow : public QMainWindow
{
    Q_OBJECT
signals:

    void addDocks(AirInfoWindow*);

public:
    explicit AirInfoWindow(QWidget *parent = nullptr);
    ~AirInfoWindow();
public slots:

    void showInfo(AirObject*);

private:
    Ui::AirInfoWindow *ui;
};

#endif // AIRINFOWINDOW_H
