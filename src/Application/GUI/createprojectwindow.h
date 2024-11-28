#ifndef CREATEPROJECTWINDOW_H
#define CREATEPROJECTWINDOW_H

#include <QDialog>

#include "backend/GIS/mapdata.h"

namespace Ui {
class createProjectWindow;
}

// Окно создания проекта
class createProjectWindow : public QDialog
{
    Q_OBJECT

signals:

    //
    void sendDataNewProject(const MapData DataMap,
                            const QString& dirName);

public:
    explicit createProjectWindow(QWidget *parent = 0);
    ~createProjectWindow();

public slots:

    //
    ///void setStatCreateProject(int percent);

private slots:

    //
    void showSelectFolderWin();

    //
    void buildProject();

private:
    Ui::createProjectWindow *ui;
};

#endif // CREATEPROJECTWINDOW_H
