#ifndef OPTDRONEWINDOW_H
#define OPTDRONEWINDOW_H

#include <QWidget>

namespace Ui {
class optDroneWindow;
}

class optDroneWindow : public QWidget
{
    Q_OBJECT

signals:
    void setAngleE(double E);

public:
    explicit optDroneWindow(QWidget *parent = 0);
    ~optDroneWindow();

private slots:


private:
    Ui::optDroneWindow *ui;

    //
    void setDesine();
};

#endif // OPTDRONEWINDOW_H
