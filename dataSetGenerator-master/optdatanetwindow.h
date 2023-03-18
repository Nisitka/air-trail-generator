#ifndef OPTDATANETWINDOW_H
#define OPTDATANETWINDOW_H

#include <QWidget>

namespace Ui {
class optDataNetWindow;
}

class optDataNetWindow : public QWidget
{
    Q_OBJECT
signals:
    void generateImage();

    void updateKrgb(double kG1, double kG2,
                    double kpD1, double kpD2,
                    double kB1);

public slots:
    // установить коофициенты по умолчанию
    void setDefaultK();

public:
    explicit optDataNetWindow(QWidget *parent = 0);

    ~optDataNetWindow();

private slots:
    // считываем значения с ui и устанавливаем
    void setKrgb();

private:
    const int MAX_VAL_SLI = 1000;

    // зеленый
    const double maxK1 = 1.0;
    const double maxK2 = 0.2;
    const double maxK3 = 1.0;
    const double maxK4 = 2.0;

    Ui::optDataNetWindow *ui;
};

#endif // OPTDATANETWINDOW_H
