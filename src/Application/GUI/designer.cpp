#include "designer.h"

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


void Designer::setButton(QPushButton* button, int style)
{
    QString strStyle;
    switch (style) {
    case blue:
        strStyle = "QPushButton{"
                   "   background-color: rgb(84,123,177); color: rgb(255,255,255);"

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
        "QTabWidget::pane {"
        "   border: 2px solid rgb(84,123,177);"
        "   background: rgb(255,255,255);"
        "}"
        ""
        "QTabWidget::tab-bar {"
        "   left: 5px;"
        "}"
        ""
        "QTabBar::tab {"
        "   background: rgb(84,123,177);"
        "   color: rgb(255,255,255);"
        "   border: 2px solid rgb(84,123,177);"
        "   border-bottom-color: rgb(84,123,177);"
        "   border-top-left-radius: 4px;"
        "   border-top-right-radius: 4px;"
        "   min-width: 8ex;"
        "   padding: 2px;"
        "}"
        ""
        "QTabBar::tab:hover {"
        "   background: rgb(193,254,255);"
        "   color: rgb(0,0,0);"
        "}"
        ""
        "QTabBar::tab:selected {"
        "   background: rgb(155,232,238);"
        "   border-color: rgb(84,123,177);"
        "   color: rgb(0,0,0);"
        "   border-bottom-color: rgb(155,232,238);"
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
            "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
            "   border: 2px solid gray;"
            "   padding: 2px 0px;"
            "   border-radius: 2px;"
            "   margin-top: 17px;" // отступ вверх
            "}"

            "QGroupBox::title {"
            "    subcontrol-origin: margin;"
            "    subcontrol-position: top left;"
            "    padding: 1px 2px;"
            "    margin-top: 2px;"
            "    background-color: white;"
            "    border: 2px solid gray;"
            "    border-radius: 3px;"
            "    left: 10px;"
            "}";
        break;
    case lightBlue:
        strStyle =
            "QGroupBox {"
            "   background-color: rgb(224,232,243);"
            "   border: 2px solid rgb(84,123,177);"
            "   padding: 2px 0px;"
            "   border-radius: 2px;"
            "}";
        break;
    }
    gb->setStyleSheet(strStyle);
}
