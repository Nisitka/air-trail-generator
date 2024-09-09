#ifndef COORDSINFOFORM_H
#define COORDSINFOFORM_H

#include <QWidget>

#include "backend/GIS/coords.h"

namespace Ui {
class CoordsInfoForm;
}

class CoordsInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit CoordsInfoForm(QWidget *parent = 0);
    ~CoordsInfoForm();

    void setData(const Coords& coords);

private:
    Ui::CoordsInfoForm *ui;
};

#endif // COORDSINFOFORM_H
