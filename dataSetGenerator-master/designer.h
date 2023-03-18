#ifndef DESIGNER_H
#define DESIGNER_H

#include <QPushButton>
#include <QProgressBar>
#include <QGroupBox>

class Designer
{
public:
    Designer();

    // настроить визуал полоски прогресса
    static void setProgressBar(QProgressBar*);

    // настроить визуал кнопки
    static void setButton(QPushButton*, int style = Designer::blue);
    enum styleButton{blue, white, red, toolOFF, toolON}; // стили кнопки

    // настроить визуал группбокса
    static void setGroupBox(QGroupBox*);
};

#endif // DESIGNER_H
