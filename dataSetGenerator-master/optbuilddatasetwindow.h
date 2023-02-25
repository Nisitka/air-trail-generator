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
    void startGenerateDataSet();

public:
    explicit optBuildDataSetWindow(QWidget *parent = 0);
    ~optBuildDataSetWindow();

private slots:
    // установка директорий для сохранения
    void setDirNetImages();
    void setDirQFunData();

    void generateDataSet();

private:
    int sizeDataSet;

    // директории для сохранения
    QString dirNetImages;
    QString dirQFunData;

    Ui::optBuildDataSetWindow *ui;
};

#endif // OPTBUILDDATASETWINDOW_H
