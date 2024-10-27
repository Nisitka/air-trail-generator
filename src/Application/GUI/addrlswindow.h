#ifndef ADDRLSWINDOW_H
#define ADDRLSWINDOW_H

#include <QDialog>

#include "backend/RLS/labelrls.h"
#include "backend/GIS/gisinformer.h"

#include "backend/RLS/creatorrls.h"

namespace Ui {
class addRLSWindow;
}

class addRLSWindow : public QDialog
{
    Q_OBJECT

signals:

    //
    void loadRLS();

public:
    explicit addRLSWindow(CreatorRLS* creatorRLS,
                          GISInformer* gis,
                          QWidget *parent = 0);
    ~addRLSWindow();

private slots:

    //
    void addRLS();

    //
    void updateHeightRLS();

private:

    //
    void clearFields();

    //
    CreatorRLS* creatorRLS;

    //
    GISInformer* gis;

    //
    void setDesine();
    Ui::addRLSWindow *ui;
};

#endif // ADDRLSWINDOW_H
