#ifndef MULTIPLEWINDOW_H
#define MULTIPLEWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include <QToolBar>
#include <QToolButton>
#include <QMap>

class MultipleWindow: public QMainWindow
{
    Q_OBJECT
public:
    MultipleWindow();

public slots:

    //
    void addFunWindow(QWidget* window, const QIcon& iconButton, const QString& nameWin = nullptr,
                   Qt::DockWidgetAreas typeMoved = Qt::LeftDockWidgetArea,
                   Qt::DockWidgetArea initShow = Qt::LeftDockWidgetArea);

    //
    void showTmpDock(QWidget* widget, Qt::DockWidgetArea typeMoved = Qt::RightDockWidgetArea);
    void creatSplitDock();

    //void addGroupFunWindow(const QList <QDockWidget*>);

protected:

    // Переопределяем метод, чтоб не вылазило меню при нажатии лев.клавиши мыши
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:

    //
    void showFunWindow();

    //
    void delTmpDock(bool statVis);

private:

    //
    enum styleButton{open, close};
    void setStyleToolButton(QToolButton* button, MultipleWindow::styleButton s);

    QMap <QToolButton*, QDockWidget*> windows;

    QDockWidget* splitDock = new QDockWidget;

    QToolBar *toolBar;
};

#endif // MULTIPLEWINDOW_H
