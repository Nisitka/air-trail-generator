#ifndef DESIGNER_H
#define DESIGNER_H

#include <QPushButton>
#include <QProgressBar>
#include <QGroupBox>
#include <QTabWidget>
#include <QComboBox>

class Designer
{
public:
    Designer();

    // настроить визуал полоски прогресса
    static void setProgressBar(QProgressBar*);

    // настроить визуал кнопки
    static void setButton(QPushButton*, int style = Designer::blue);
    enum styleButton{blue, white, red, green, toolOFF, toolON}; // стили кнопки

    // настроить визуал группбокса
    static void setGroupBox(QGroupBox*, int style = Designer::gray);
    enum styleGroupBox{gray, lightBlue};

    // настроить визуал таба виджетов
    static void setTabWidget(QTabWidget*);

    // настроить визуал выпадающего списка
    static void setComboBox(QComboBox*);
};

#endif // DESIGNER_H
