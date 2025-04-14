#include "createprojectwindow.h"
#include "ui_createprojectwindow.h"

#include "GUI/designer.h"

#include <QApplication>
#include <QFileDialog>

#include <QDebug>

#include "../backend/projectfile.h"

createProjectWindow::createProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createProjectWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Создать проект");

    // Значения по умолчанию
    ui->dirProjectLineEdit->setText(
                QApplication::applicationDirPath());
    ui->nameProjectLineEdit->setText("Безымянный_1");

    //
    ui->progressBar->hide();

    //
    connect(ui->createProjectButton, SIGNAL(clicked(bool)),
            this,                    SLOT(buildProject()));

    // Вызвать окно выбора директории
    connect(ui->setDirProjectPushButton, SIGNAL(clicked(bool)),
            this,                        SLOT(showSelectFolderWin()));

    //
    Designer::setGroupBox(ui->groupBox_2);
    Designer::setGroupBox(ui->groupBox_3);

    //
    Designer::setButton(ui->createProjectButton);
    Designer::setButton(ui->setDirProjectPushButton);

    //
    Designer::setProgressBar(ui->progressBar);
}

void createProjectWindow::showSelectFolderWin()
{
    QString dir = QFileDialog::getExistingDirectory();
    ui->dirProjectLineEdit->setText(dir);
}

void createProjectWindow::buildProject()
{
    //
    ui->progressBar->show();
    ui->progressBar->setMaximum(0);

    // Полный путь проекта
    QString dirNameProject;
    QString format; ProjectFile::format(format);
    dirNameProject  = ui->dirProjectLineEdit->text() + "/";
    dirNameProject += ui->nameProjectLineEdit->text() + format;

    //
    sendDataNewProject(dirNameProject);
}

createProjectWindow::~createProjectWindow()
{
    delete ui;
}
