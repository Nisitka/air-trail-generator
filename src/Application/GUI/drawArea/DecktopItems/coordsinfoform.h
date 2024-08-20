#ifndef COORDSINFOFORM_H
#define COORDSINFOFORM_H

#include <QLabel>

#include "backend/GIS/coords.h"

namespace Ui {
class CoordsInfoForm;
}

class CoordsInfoForm : public QLabel
{
    Q_OBJECT

public:
    explicit CoordsInfoForm(QWidget *parent = 0);
    ~CoordsInfoForm();

    void setData(const Coords& coords);

    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::CoordsInfoForm *ui;
};

#endif // COORDSINFOFORM_H
