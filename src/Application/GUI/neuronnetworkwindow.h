#ifndef NEURONNETWORKWINDOW_H
#define NEURONNETWORKWINDOW_H

#include <QWidget>

#include <QDir>

namespace Ui {
class neuronNetworkWindow;
}

class neuronNetworkWindow : public QWidget
{
    Q_OBJECT
signals:
    void predictToRect(const QString &nameNet);

    // запуск обучения сети
    void trainNet(const QString &dirImgs,
                  const QString &dirRewards,
                  int coutEpoch,
                  const QString &nameNet);

    void predictTrail(const QString& nameModel,
                      int idXa, int idYa, int idXb, int idYb);

public slots:
    void finishRectPredict(int idX, int idY);

    void setPointsPredictTrail(const QPoint& begin, const QPoint& last);

public:
    static int countFilePatch(const QString& dir);

    explicit neuronNetworkWindow(QWidget *parent = 0);
    ~neuronNetworkWindow();

private slots:
    // запуск прогноза
    void runPredict();

    void runTrainNet();

    // обновить список моделей
    void updateModelsList();

    void setDirImages();

    void setDirRewards();

private:
    // настройка дизайна
    void setDesine();

    // запуск прогноза
    enum typePredict{rect, trail};
    QStringList listTypePredict = {"в области", "траекторию"};
    void runPredictRect();  // в выделенной области
    void runPredictTrail(); // траектории

    QPoint lastPoint;
    QPoint beginPoint;

    int countTrainImg;
    int countTrainReward;

    Ui::neuronNetworkWindow *ui;
};

#endif // NEURONNETWORKWINDOW_H
