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

    //void addGroupFunWindow(const QList <QDockWidget*>);

private slots:

    //
    void showFunWindow();

private:

    QMap <QToolButton*, QDockWidget*> windows;

    QToolBar *toolBar;
};

#endif // MULTIPLEWINDOW_H
