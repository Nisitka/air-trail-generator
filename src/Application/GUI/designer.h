#ifndef DESIGNER_H
#define DESIGNER_H

#include <QPushButton>
#include <QProgressBar>
#include <QGroupBox>
#include <QTabWidget>
#include <QComboBox>
#include <QToolBar>
#include <QMainWindow>
#include <QDockWidget>
#include <QMenu>
#include <QScrollArea>

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

    //
    static void setToolBar(QToolBar* toolBar, int style = tool);
    enum styleToolBox{tool, whiteToolBox};

    //
    static void setMainWindow(QMainWindow* mainWin, int style = def);
    enum styleMainWin{def};

    static void setDockWidget(QDockWidget* dockWidget);

    static void setMenu(QMenu* menu);

    static void setScrollArea(QScrollArea* area);
};

#endif // DESIGNER_H
