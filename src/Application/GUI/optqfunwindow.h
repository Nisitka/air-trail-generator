#ifndef OPTQFUNWINDOW_H
#define OPTQFUNWINDOW_H

#include <QWidget>

namespace Ui {
class optQFunWindow;
}

class optQFunWindow : public QWidget
{
    Q_OBJECT

signals:
    void runCalcQFun(); // начать обсчет Q функции

public slots:
    // начало генерации изображения
    void startGenImage(int countSigment);

    //
    void updateProgressGenImage(int currentSigment);

    //
    void finishGenImage();

public:
    explicit optQFunWindow(QWidget *parent = 0);
    ~optQFunWindow();

private slots:
    // отправить сигнал для запуска калькулятора Q функции
    void emitSignalRunGenImage();

private:
    Ui::optQFunWindow *ui;
};

#endif // OPTQFUNWINDOW_H
