#include "hellowindow.h"
#include "ui_hellowindow.h"

helloWindow::helloWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helloWindow)
{
    ui->setupUi(this);

    idWindow[ui->switchStartWorkPB] = 0;
    connect(ui->switchStartWorkPB, SIGNAL(clicked(bool)),
            this,                  SLOT(switchWindow()));
    setStyleMainButton(ui->switchStartWorkPB);

    idWindow[ui->switchExamplePB]   = 1;
    connect(ui->switchExamplePB, SIGNAL(clicked(bool)),
            this,                SLOT(switchWindow()));
    setStyleMainButton(ui->switchExamplePB);

    currentButton = ui->switchStartWorkPB;
    ui->switchStartWorkPB->clicked();

    // Открыть проект
    connect(ui->openFilePushButton, SIGNAL(clicked(bool)),
            this,                   SIGNAL(choiceProjectFile()));

    // Создать проект
    connect(ui->createFilePushButton, SIGNAL(clicked(bool)),
            this,                     SIGNAL(showMasterBuildProject()));

    //
    ui->openFilePushButton->setStyleSheet("QPushButton{"
                                          "   background-color: transparent; color: black;"
                                          "   border-style: outset;"
                                          "   border-width: 1px;"
                                          "   border-color: rgb(115,115,120);"
                                          "}"
                                          "QPushButton:hover{"
                                          "   background-color: rgb(230,230,230);"
                                          "   border-color: black;"
                                          "}");

    //
    ui->createFilePushButton->setStyleSheet("QPushButton{"
                                            "   image: url(:/resurs/plusBlackEl);"
                                            "   background-color: transparent; color: black;"
                                            "   border-style: outset;"
                                            "   border-width: 1px;"
                                            "   border-color: rgb(115,115,120);"
                                            "}"
                                            "QPushButton:hover{"
                                            "   image: url(:/resurs/plusBlueEl);"
                                            "   background-color: rgb(230,230,250);"
                                            "   border-color: black;"
                                            "}");
}

void helloWindow::switchWindow()
{
    setStyleMainButton(currentButton);

    currentButton = qobject_cast<QPushButton*>(sender());
    setStyleCurMainButton(currentButton);
    ui->StackedWidget->setCurrentIndex(idWindow[currentButton]);
}

void helloWindow::setStyleMainButton(QPushButton *button)
{
    button->setStyleSheet("QPushButton{"
                          "   background-color: transparent; color: black;"
                          "   border-style: outset;"
                          "   border-width: 1px;"
                          "   border-color: rgb(115,115,120);"
                          "}"
                          "QPushButton:hover{"
                          "   background-color: #d0e3f7;"
                          "   border-color: black;"
                          "}"
                          );
}

void helloWindow::setStyleCurMainButton(QPushButton *button)
{
    button->setStyleSheet("QPushButton{"
                          "   background-color : rgb(75,75,80); color: white;"
                          "   border-color: rgb(0,0,0);"
                          "   border-style: outset;"
                          "   border-width: 1px;"
                          "}"
                          "QPushButton:hover{"
                          "   background-color : rgb(209,226,248); color: rgb(0,0,0);"
                          "   border-color: rgb(0,0,0);"
                          "}"
                          "QPushButton:pressed{"
                          "   background-color : rgb(209,226,248); color: rgb(0,0,0);"
                          "}");
}

helloWindow::~helloWindow()
{
    delete ui;
}
