#ifndef MANAGERMAPSWINDOW_H
#define MANAGERMAPSWINDOW_H

#include <QMainWindow>

namespace Ui {
class ManagerMapsWindow;
}

class ManagerMapsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerMapsWindow(QWidget *parent = 0);
    ~ManagerMapsWindow();

private:
    Ui::ManagerMapsWindow *ui;
};

#endif // MANAGERMAPSWINDOW_H
