#ifndef OPTDATANETWINDOW_H
#define OPTDATANETWINDOW_H

#include <QWidget>

namespace Ui {
class optDataNetWindow;
}

class optDataNetWindow : public QWidget
{
    Q_OBJECT
signals:
    void generateImage();

public:
    explicit optDataNetWindow(QWidget *parent = 0);
    ~optDataNetWindow();

private:
    Ui::optDataNetWindow *ui;
};

#endif // OPTDATANETWINDOW_H
