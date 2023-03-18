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

    void openMap_signal(const QString& dirFile);

public slots:
    // обновить полоску загрузки
    void updateProgressBar(int value);

    // конец генерации рельефа
    void finishGenerateMap();

    // генериовать карту по установленным пар-м
    void startGenerateMap();

public:
    explicit optMapGeneratorWindow(QWidget *parent = 0);
    ~optMapGeneratorWindow();

private slots:
    void setProgressBar(int countLayers);

    void openMap();

private:
    Ui::optMapGeneratorWindow *ui;
};

#endif // OPTMAPGENERATORWINDOW_H
