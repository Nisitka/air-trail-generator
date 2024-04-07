#ifndef DATAACCESSOBJECTWINDOW_H
#define DATAACCESSOBJECTWINDOW_H

#include <QWidget>
#include "backend/dao.h"

namespace Ui {
class DataAccessObjectWindow;
}

class DataAccessObjectWindow : public QWidget
{
    Q_OBJECT
public slots:

    void connect_dao();

    void status_connect(bool);
signals:

    void connection(QString);

public:
    explicit DataAccessObjectWindow(QWidget *parent = nullptr);
    ~DataAccessObjectWindow();

private:

    Ui::DataAccessObjectWindow *ui;
};

#endif // DATAACCESSOBJECTWINDOW_H
