#ifndef MAINSWITCHERWINDOW_H
#define MAINSWITCHERWINDOW_H

#include <QMainWindow>
#include <QStatusBar>

#include <QToolBar>
#include <QToolButton>
#include <QDockWidget>

namespace Ui {
class mainSwitcherWindow;
}

class mainSwitcherWindow : public QMainWindow
{
    Q_OBJECT

signals:

    // Запросить окно выбора файла-проекта
    void choiceProjectFile();

    // Запросить окно создания проекта
    void showMasterBuildProject();

public slots:

    //
    void showMainWindow();

public:
    explicit mainSwitcherWindow(QWidget *parent = 0);
    ~mainSwitcherWindow();

    //
    void addWindow(QWidget *window,
                   const QIcon& iconButton,
                   const QString& nameButton,
                   bool isMain = false);
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

    //
    QWidget* mainWindow;

    Ui::mainSwitcherWindow *ui;
};

#endif // MAINSWITCHERWINDOW_H
