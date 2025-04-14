#ifndef CREATEMAPWINDOW_H
#define CREATEMAPWINDOW_H

#include <QDialog>

#include "../backend/GIS/mapdata.h"

namespace Ui {
class createMapWindow;
}

class createMapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit createMapWindow(QWidget *parent = 0);
    ~createMapWindow();

private slots:

    //
    void createMap();

private:
    Ui::createMapWindow *ui;
};

#endif // CREATEMAPWINDOW_H
