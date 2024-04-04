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
    //
    void runPredictTrail(int idXa, int idYa,
                         int idXb, int idYb);
public slots:
    //
    void setPredictPoints(int idXa, int idYa,
                          int idXb, int idYb);

    //
    void startSetOptPredict();
    void finishSetOptPredict();
    void updateProgSetOptPred(int percent);

public:
    explicit optDroneWindow(QWidget *parent = 0);
    ~optDroneWindow();

private slots:
    //
    void startPredictTrail();

private:
    Ui::optDroneWindow *ui;

    //
    void setDesine();
};

#endif // OPTDRONEWINDOW_H
