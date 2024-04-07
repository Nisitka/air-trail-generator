#include "functionwindow.h"

functionWindow::functionWindow(QDockWidget* dockWin): dockWin(dockWin)
{
    isOpen = false;
}

void functionWindow::editShowStatus()
{
    if (isOpen)
    {
        dockWin->hide();
        isOpen = false;
    }
    else
    {
        dockWin->show();
        isOpen = true;
    }
}
