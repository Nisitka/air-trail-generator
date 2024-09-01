#ifndef HELLOWINDOW_H
#define HELLOWINDOW_H

#include <QWidget>

namespace Ui {
class helloWindow;
}

class helloWindow : public QWidget
{
    Q_OBJECT

public:
    explicit helloWindow(QWidget *parent = 0);
    ~helloWindow();

private:
    Ui::helloWindow *ui;
};

#endif // HELLOWINDOW_H
