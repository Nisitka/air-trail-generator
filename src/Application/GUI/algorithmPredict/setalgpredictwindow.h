#ifndef SETALGPREDICTWINDOW_H
#define SETALGPREDICTWINDOW_H

#include <QMainWindow>

#include "glyph.h"

#include "compospredfunctionarea.h"

namespace Ui {
class setAlgPredictWindow;
}

class setAlgPredictWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit setAlgPredictWindow(QWidget *parent = 0);
    ~setAlgPredictWindow();

private:

    //
    composPredFunctionArea* comArea;

    Ui::setAlgPredictWindow *ui;
};

#endif // SETALGPREDICTWINDOW_H
