#ifndef OPTBUILDDATASETWINDOW_H
#define OPTBUILDDATASETWINDOW_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class optBuildDataSetWindow;
}

class optBuildDataSetWindow : public QWidget
{
    Q_OBJECT
signals:
    void startGenerateDataSet(int countData,
                              const QString& dirNetImages,
                              const QString& dirQFunData,
                              int countRect);

public:
    explicit optBuildDataSetWindow(QWidget *parent = 0);
    ~optBuildDataSetWindow();

public slots:
    // готовность одной пары X-Y
    void readyPart();

private slots:
    // установка директорий для сохранения
    void setDirNetImages();
    void setDirQFunData();

    void generateDataSet();

    void updateSizeDS();

private:
    void setDesine();

    int sizeDataSet;
    int currentData;

    // директории для сохранения
    QString dirNetImages;
    QString dirQFunData;

    Ui::optBuildDataSetWindow *ui;
};

#endif // OPTBUILDDATASETWINDOW_H
