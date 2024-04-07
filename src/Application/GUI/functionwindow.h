#ifndef FUNCTIONWINDOW_H
#define FUNCTIONWINDOW_H

#include <QObject>
#include <QDockWidget>

class functionWindow: public QObject
{
    Q_OBJECT
public slots:
    //
    void editShowStatus();

public:
    functionWindow(QDockWidget* dockWin);

private:
    //
    QDockWidget* dockWin;

    //
    bool isOpen;
};

#endif // FUNCTIONWINDOW_H
