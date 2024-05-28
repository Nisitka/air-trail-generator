#include "designer.h"

#include <QScrollBar>

Designer::Designer()
{

}

void Designer::setProgressBar(QProgressBar* pb)
{
    //pb->setAlignment(Qt::AlignCenter);
    pb->setStyleSheet(
            "QProgressBar{"
            "   border: 5px solid rgb(0,0,0);"
            "   border-radius: 3px;"
            "   background-color: rgb(255,255,255);"
            "   text-align: center;"
            "   color: rgb(0,150,0);"
            "   border-width: 1px;"
            "}"
            "QProgressBar::chunk{"
            "   border-radius: 3px;"
            "   background-color: rgb(155,238,100);"
            "}"
            );
}

void Designer::setColorToolButton(QToolButton *toolButton, const QColor& color)
{
    QString strStyle;

    QString strColor = "rgb(" + QString::number(color.red())   + "," +
                                QString::number(color.green()) + "," +
                                QString::number(color.blue())  + ")";

    strStyle =
            "QToolButton{"
            "   background-color: " + strColor + ";"
            "}"
            "QToolButton:hover{"
            "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
            "    border-color: rgb(0,0,0);"
            "    border-style: outset;"
            "    border-radius: 3px;"
            "    border-width: 1px;"
            "    border-color: rgb(0,0,0);"
            "}"
            "QToolButton:pressed{"
            "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
            "    border-color: rgb(0,0,0);"
            "    border-style: outset;"
            "    border-radius: 3px;"
            "    border-width: 1px;"
            "    border-color: rgb(0,0,0);"
            "};";

    toolButton->setStyleSheet(strStyle);
}

void Designer::setButton(QPushButton* button, int style)
{
    QString strStyle;
    switch (style) {
    case blue:
        strStyle = "QPushButton{"
                   "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                   "                                     stop: 0 rgb(255,252,254), "
                   "                                     stop: 0.3 rgb(209,226,248), "
                   "                                     stop: 1 rgb(251,252,254));"
                   "   border: 1px solid rgb(150,183,227);"
                   "   border-radius: 3px;"
                   "   border-width: 1px;"
                   "   color: rgb(34,69,157);"
                   "}"
                   "QPushButton:hover{"
                   "   border: 1px solid rgb(255,165,0);"
                   "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                   "                                     stop: 0 rgb(255,252,254), "
                   "                                     stop: 0.4 rgb(255,204,60), "
                   "                                     stop: 1 rgb(255,251,230));"
                   "   color: rgb(102,51,0);"
                   "}"
                   "QPushButton:pressed{"
                   "    background-color : rgb(125,202,208); color: rgb(0,0,0);;"
                   "}";
        break;
    case white:
        strStyle =
                "QPushButton{"
                "   background-color: rgb(255,255,255); color: rgb(0,0,0);"
                "   border-style: outset;"
                "   border-radius: 3px;"
                "   border-width: 1px;"
                "   border-color: rgb(0,0,0);"
                "}"
                "QPushButton:hover{"
                "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
                "    border-color: rgb(0,0,0);"
                "}"
                "QPushButton:pressed{"
                "    background-color : rgb(143,204,205); color: rgb(0,0,0);;"
                "}";
        break;
    case red:
        strStyle = "QPushButton{"
                   "   background-color: rgb(136,0,21); color: rgb(255,255,255);"

                   "   border-style: outset;"
                   "   border-radius: 3px;"
                   "   border-width: 1px;"
                   "   border-color: rgb(0,0,0);"
                   "}"
                   "QPushButton:hover{"
                   "    background-color : rgb(255,19,0); color: rgb(0,0,0);"
                   "    border-color: rgb(0,0,0);"
                   "}"
                   "QPushButton:pressed{"
                   "    background-color : rgb(136,0,21); color: rgb(255,255,255);;"
                   "}";
        break;
    case green:
        strStyle = "QPushButton{"
                   "   background-color: rgb(0,184,0); color: rgb(255,255,255);"

                   "   border-style: outset;"
                   "   border-radius: 3px;"
                   "   border-width: 1px;"
                   "   border-color: rgb(0,0,0);"
                   "}"
                   "QPushButton:hover{"
                   "    background-color : rgb(75,255,0); color: rgb(0,0,0);"
                   "    border-color: rgb(0,0,0);"
                   "}"
                   "QPushButton:pressed{"
                   "    background-color : rgb(0,164,0); color: rgb(255,255,255);;"
                   "}";
        break;
    case toolOFF:
        strStyle = "QPushButton{"
                   "   background-color: rgb(255,255,255);"

                   "   border-style: outset;"
                   "   border-radius: 5px;"
                   "   border-width: 2px;"
                   "   border-color: rgb(0,0,0);"
                   "}"
                   "QPushButton:hover{"
                   "    background-color : rgb(193,254,255);"
                   "    border-color: rgb(0,162,223);"
                   "}";
        break;
    case toolON:
        strStyle = "QPushButton{"
                   "   background-color: rgb(193,254,255);"

                   "   border-style: outset;"
                   "   border-radius: 5px;"
                   "   border-width: 2px;"
                   "   border-color: rgb(0,0,0);"
                   "}"
                   "QPushButton:hover{"
                   "    background-color : rgb(193,254,255);"
                   "    border-color: rgb(0,162,223);"
                   "}";
        break;
    }

    button->setStyleSheet(strStyle);
}

void Designer::setComboBox(QComboBox *cb)
{
    QString strStyle =
        "QComboBox {"
        "   background-color: rgb(255,255,255); color: rgb(0,0,0);"
        "   border-style: outset;"
        "   border-radius: 3px;"
        "   border-width: 1px;"
        "   border-color: rgb(0,0,0);"
        "}"
        "QComboBox:hover{"
        "    background-color : rgb(193,254,255); color: rgb(0,0,0);"
        "    border-color: rgb(0,0,0);"
        "}"
        "QComboBox:pressed{"
        "    background-color : rgb(143,204,205); color: rgb(0,0,0);"
        "}"
        "QAbstractItemView{"
        "   background-color: rgb(255,255,255); color: rgb(0,0,0);"
        "   border-style: outset;"
        "   border-radius: 3px;"
        "   border-width: 1px;"
        "   border-color: rgb(0,0,0);"
        "}"
        "QAbstractItemView::item:selected{"
        "    background-color: rgb(193,254,255);"
        "    color: rgb(0,0,0);"
        "}";
    cb->setStyleSheet(strStyle);
}

void Designer::setTabWidget(QTabWidget *tw)
{
    QString strStyle =
            "QTabWidget::pane {"                        /// Сама область
            "   border: 1px solid rgb(150,183,227);"
            "   background: rgb(244,248,253);"
            "   border-radius: 2px;"
            "}"
            ""
            "QTabWidget::tab-bar {"
            "   left: 5px;"
            "}"
            ""
            "QTabBar::tab {"
            "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
            "                                     stop: 0 rgb(255,252,254), "
            "                                     stop: 0.3 rgb(209,226,248), "
            "                                     stop: 1 rgb(251,252,254));"
            "   border: 1px solid rgb(150,183,227);"
            "   color: rgb(84,113,177);"
            "   border-bottom-color: rgb(209,226,248);"
            "   border-top-left-radius: 4px;"
            "   border-top-right-radius: 4px;"
            "   min-width: 8ex;"
            "   padding: 2px;"
            "}"
            ""
            "QTabBar::tab:hover {"
            "   border: 1px solid rgb(255,165,0);"
            "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
            "                                     stop: 0 rgb(255,252,254), "
            "                                     stop: 0.4 rgb(255,204,60), "
            "                                     stop: 1 rgb(255,251,230));"
            "   color: rgb(102,51,0);"
            "}"
            ""
            "QTabBar::tab:selected {"
            "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
            "                                     stop: 0 rgb(255,255,255), "
            "                                     stop: 0.3 rgb(209,226,248), "
            "                                     stop: 1   rgb(244,248,253));"
            "   border-color: rgb(150,183,227);"
            "   color: rgb(34,69,157);"
            "   border-bottom-color: rgb(244,248,253);"
            "}"
            "QTabBar::tab:!selected {"
            "   margin-top: 3px;"
            "}";

    tw->setStyleSheet(strStyle);
}

void Designer::setGroupBox(QGroupBox *gb, int style)
{
    QString strStyle;
    switch (style) {
    case gray:
        strStyle =
            "QGroupBox {"
            "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
            "                                     stop: 0    #E0E0E0,"
            "                                     stop: 0.35 rgb(251,252,254), "
            "                                     stop: 1    rgb(231,232,234));"
            "   border: 1px solid gray;"
            "   padding: 2px 0px;"
            "   border-radius: 2px;"
            "   margin-top: 17px;" // отступ вверх
            "}"

            "QGroupBox::title {"
            "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
            "                                     stop: 0    white, "
            "                                     stop: 0.25 rgb(220, 220, 220), "
            "                                     stop: 1    rgb(251,252,254));"
            "    subcontrol-origin: margin;"
            "    subcontrol-position: top left;"
            "    padding: 1px 2px;"
            "    margin-top: 2px;"
            "    border: 1px solid gray;"
            "    border-radius: 3px;"
            "    left: 10px;"
            "}";
        break;
    case lightBlue:
        strStyle =
            "QGroupBox {"
            "   background-color: rgb(224,232,243);"
            "   border: 1px solid rgb(84,123,177);"
            "   padding: 1px 0px;"
            "   border-radius: 2px;"
            "}";
        break;
    }
    gb->setStyleSheet(strStyle);
}

void Designer::setMenu(QMenu *menu)
{
    QString strStyle =
        "QMenu {"
        "   background-color: gray;"
        "   margin: 2px;"
        "   border-radius: 5px;"
        "}"
        "QMenu::item{"
        "   background-color: #E0E0E0;"
        "   color: rgb(25, 25, 25);"
        "}"
        "QMenu::item:selected{"
        "   background-color: rgb(193,254,255);"
        "   color: black;"
        "}";
    menu->setStyleSheet(strStyle);
}

void Designer::setMainWindow(QMainWindow *mainWin, int style)
{
    QString strStyle;

    switch (style) {
    case def:
        strStyle =
        "QMainWindow{"
        "    background-color: rgb(209,226,248);"
        "    border: 1px solid rgb(150,183,227);"
        "    color: rgb(34,69,157);}";
        break;
    }

    mainWin->setStyleSheet(strStyle);
}

void Designer::setDockWidget(QDockWidget *dockWidget)
{
    QString strStyle =
        "QDockWidget{"
        "    background-color: #7795bf;"
        "    border: 1px solid rgb(34,69,157);"
        "}";
    dockWidget->setStyleSheet(strStyle);
}

void Designer::setToolBar(QToolBar *toolBar, int style)
{
    QString strStyle;
    switch (style) {
    case tool:
        strStyle = "";

        break;
    case whiteToolBox:
        strStyle =
        "QToolBar {"
        "    border: 1px solid rgb(34,69,157);"
        "    background-color: rgb(255,255,255);"
        "}"
        "QToolButton{"
        "   background-color: rgb(255,255,255);"
        "}"
        "QToolButton:hover{"
        "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
        "    border-color: rgb(0,0,0);"
        "    border-style: outset;"
        "    border-radius: 3px;"
        "    border-width: 1px;"
        "    border-color: rgb(0,0,0);"
        "}"
        "QToolButton:pressed{"
        "    background-color : rgb(255,251,230); color: rgb(0,0,0);"
        "    border-color: rgb(0,0,0);"
        "    border-style: outset;"
        "    border-radius: 3px;"
        "    border-width: 1px;"
        "    border-color: rgb(0,0,0);"
        "};";
        break;
    }

    toolBar->setStyleSheet(strStyle);
}

void Designer::setScrollArea(QScrollArea *area)
{
    QString strStyle =
        "QScrollBar:horizontal {"
        "   border: 2px solid grey;"
        "   background: #32CC99;"
        "   height: 15px;"
        "   margin: 0px 20px 0 20px;"
        "}"
        "QScrollBar:vertical {"
        "   border: 2px solid grey;"
        "   background: #32CC99;"
        "   height: 15px;"
        "   margin: 0px 20px 0 20px;"
        "}";

    //area->setStyleSheet(strStyle);
}
