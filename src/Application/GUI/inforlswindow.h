#ifndef INFORLSWINDOW_H
#define INFORLSWINDOW_H

#include <QWidget>

#include <QVector>

//
#include "plotwidget.h"

namespace Ui {
class InfoRLSWindow;
}

class InfoRLSWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InfoRLSWindow(QWidget *parent = 0);
    ~InfoRLSWindow();

    //
    void setGraphicData(const QVector <double>& X,
                        const QVector <double>& Y);

    //
    void clearData();

private:

    // Для графика ДН
    plotWidget* graphicWidget;

    //
    void setDesine();
    Ui::InfoRLSWindow *ui;


};

#endif // INFORLSWINDOW_H
