#ifndef MAINSWITCHERWINDOW_H
#define MAINSWITCHERWINDOW_H

#include <QMainWindow>

#include <QToolBar>
#include <QToolButton>
#include <QDockWidget>

namespace Ui {
class mainSwitcherWindow;
}

class mainSwitcherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainSwitcherWindow(QWidget *parent = 0);
    ~mainSwitcherWindow();

    //
    void addWindow(QWidget *window,
                   const QIcon& iconButton,
                   const QString& nameButton);
    //
    void setCurrentWindow(QWidget* window) const;

private slots:

    //
    void showWindow();

private:

    //
    void createMenus();

    // Панель переключения окон
    QToolBar* toolBar;

    //
    QMap <QToolButton*, QWidget*> windows;

    Ui::mainSwitcherWindow *ui;
};

#endif // MAINSWITCHERWINDOW_H