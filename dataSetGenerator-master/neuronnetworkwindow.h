#ifndef NEURONNETWORKWINDOW_H
#define NEURONNETWORKWINDOW_H

#include <QWidget>

namespace Ui {
class neuronNetworkWindow;
}

class neuronNetworkWindow : public QWidget
{
    Q_OBJECT
signals:
    void predictToRect();

    // запуск обучения сети
    void trainNet(const QString &dirApp,
                  const QString &dirImgs,
                  const QString &dirRewards,
                  int coutEpoch,
                  const QString &dirNameNet);

    void predictTrail(int idXa, int idYa, int idXb, int idYb);

public slots:
    void finishRectPredict(int idX, int idY);

    void setPointsPredictTrail(const QPoint& begin, const QPoint& last);

public:
    explicit neuronNetworkWindow(QWidget *parent = 0);
    ~neuronNetworkWindow();

private slots:
    // запуск прогноза
    void runPredict();

    void runTrainNet();

private:
    // запуск прогноза
    enum typePredict{rect, trail};
    QStringList listTypePredict = {"В области", "Траектории"};
    void runPredictRect();  // в выделенной области
    void runPredictTrail(); // траектории

    QPoint lastPoint;
    QPoint beginPoint;


    Ui::neuronNetworkWindow *ui;
};

#endif // NEURONNETWORKWINDOW_H
