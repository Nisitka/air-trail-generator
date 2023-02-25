#ifndef OPTMAPGENERATORWINDOW_H
#define OPTMAPGENERATORWINDOW_H

#include <QWidget>

namespace Ui {
class optMapGeneratorWindow;
}

class optMapGeneratorWindow : public QWidget
{
    Q_OBJECT
signals:
    void runGenerateMap(double setBlockP, int countEpochs,
                        int W, int L, int H,
                        double lenBlock);

public slots:
    // обновить полоску загрузки
    void updateProgressBar(int value);

    // конец генерации рельефа
    void finishGenerateMap();

public:
    explicit optMapGeneratorWindow(QWidget *parent = 0);
    ~optMapGeneratorWindow();

private slots:
    void startGenerateMap();
    void setProgressBar(int countLayers);

private:
    Ui::optMapGeneratorWindow *ui;
};

#endif // OPTMAPGENERATORWINDOW_H
