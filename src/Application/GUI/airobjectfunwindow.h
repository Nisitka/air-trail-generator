#ifndef AIROBJECTFUNWINDOW_H
#define AIROBJECTFUNWINDOW_H

#include <QWidget>

#include "multiplewindow.h"

namespace Ui {
class AirObjectFunWindow;
}

class AirObjectFunWindow : public MultipleWindow
{
    Q_OBJECT

public:
    explicit AirObjectFunWindow();
    ~AirObjectFunWindow();
public slots:

    void setParameters(QString, double,double,double, QString);

private:
    Ui::AirObjectFunWindow *ui;
};

#endif // AIROBJECTFUNWINDOW_H
