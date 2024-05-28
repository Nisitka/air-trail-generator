#include "multiplewindow.h"

#include "designer.h"

#include <QDebug>

MultipleWindow::MultipleWindow()
{
    toolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, toolBar);
    toolBar->setMovable(false);
    toolBar->setStyleSheet(
                "QToolBar {"
                "    border: 1px solid rgb(34,69,157);"
                "    background-color: rgb(255,255,255);"
                "}"
                );
}

void MultipleWindow::addFunWindow(QWidget *window, const QIcon &iconButton, const QString &nameWin,
                                  Qt::DockWidgetAreas typeMoved, Qt::DockWidgetArea initShow)
{
    //
    QToolButton* button = new QToolButton;
    button->setIcon(iconButton);
    button->setToolTip(nameWin);
    setStyleToolButton(button, close);

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

//    connect(dock, SIGNAL(visibilityChanged(bool)),
//            this, SLOT(delTmpDock(bool)));

    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    //this->addDockWidget(typeMoved, dock1);

    //splitDockWidget(dock1, dock, Qt::Horizontal);
    tabifyDockWidget(splitDock, dock);
    //dock1->show();
}

void MultipleWindow::creatSplitDock()
{
    splitDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    splitDock->setAllowedAreas(Qt::RightDockWidgetArea);

    this->addDockWidget(Qt::RightDockWidgetArea, splitDock);

    splitDock->hide();
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
        setStyleToolButton(button, close);
        dock->hide();
    }
    else
    {
        setStyleToolButton(button, open);
        dock->show();
    }
}

void MultipleWindow::setStyleToolButton(QToolButton *button, MultipleWindow::styleButton s)
{
    QString strStyle;
    switch (s) {
    case close:
        strStyle =
                "QToolButton{"
                "   background-color: rgb(255,255,255);"
                "}"
                "QToolButton:hover{"
                "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "}"
                "QToolButton:pressed{"
                "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "};";
        break;
    case open:
        strStyle =
                "QToolButton{"
                "   background-color: rgb(255,251,230);"
                "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "}"
                "QToolButton:hover{"
                "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
                "    border-color: rgb(100,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "}"
                "QToolButton:pressed{"
                "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "    border-style: outset;"
                "    border-radius: 3px;"
                "    border-width: 1px;"
                "};";
        break;
    }

    button->setStyleSheet(strStyle);
}

void MultipleWindow::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}


