#include "multiplewindow.h"

#include <QDebug>

MultipleWindow::MultipleWindow()
{
    toolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, toolBar);
    toolBar->setMovable(false);
}

void MultipleWindow::addFunWindow(QWidget *window, const QIcon &iconButton, const QString &nameWin,
                                  Qt::DockWidgetAreas typeMoved, Qt::DockWidgetArea initShow)
{
    //
    QToolButton* button = new QToolButton;
    button->setIcon(iconButton);
    button->setToolTip(nameWin);
    //setButtonStyle(button, on);

    toolBar->addWidget(button);

    //
    QDockWidget* dock = new QDockWidget(nameWin);
    this->addDockWidget(initShow, dock);
    dock->setWidget(window);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(typeMoved);
    dock->hide();

    //
    connect(button, SIGNAL(clicked(bool)),
            this,   SLOT(showFunWindow()));

    windows[button] = dock;
}

void MultipleWindow::showTmpDock(QWidget *widget, Qt::DockWidgetArea typeMoved)
{
    QDockWidget* dock = new QDockWidget;
    dock->setWidget(widget);

    connect(dock, SIGNAL(visibilityChanged(bool)),
            this, SLOT(delTmpDock(bool)));

    this->addDockWidget(typeMoved, dock);
}

void MultipleWindow::delTmpDock(bool statVis)
{
    if (statVis == false)
    {
        QDockWidget* dock = qobject_cast<QDockWidget*>(sender());

        disconnect(dock, SIGNAL(visibilityChanged(bool)),
                   this, SLOT(delTmpDock(bool)));

        delete dock;
    }
}

void MultipleWindow::showFunWindow()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());

    QDockWidget* dock = windows[button];
    if (dock->isVisible())
    {
        dock->hide();
    }
    else
    {
        dock->show();
    }
}

void MultipleWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}


