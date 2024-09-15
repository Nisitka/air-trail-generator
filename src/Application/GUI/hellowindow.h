#ifndef HELLOWINDOW_H
#define HELLOWINDOW_H

#include <QWidget>

#include <QPushButton>
#include <QMap>

namespace Ui {
class helloWindow;
}

class helloWindow : public QWidget
{
    Q_OBJECT

signals:

    //
    void choiceProjectFile();

public:
    explicit helloWindow(QWidget *parent = 0);
    ~helloWindow();

private slots:

    void switchWindow();

private:

    //
    void setStyleMainButton(QPushButton* button);
    void setStyleCurMainButton(QPushButton* button);

    //
    QMap <QPushButton*, int> idWindow;
    QPushButton* currentButton;

    Ui::helloWindow *ui;
};

#endif // HELLOWINDOW_H
