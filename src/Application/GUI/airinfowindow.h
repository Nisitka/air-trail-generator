#ifndef AIRINFOWINDOW_H
#define AIRINFOWINDOW_H

#include <QMainWindow>
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

private:
    Ui::AirInfoWindow *ui;
};

#endif // AIRINFOWINDOW_H
