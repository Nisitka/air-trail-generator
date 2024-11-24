#ifndef INFORLSWINDOW_H
#define INFORLSWINDOW_H

#include "backend/GIS/gisinformer.h"
#include "backend/RLS/labelrls.h"
#include "backend/GIS/coords.h"

#include <QWidget>

#include <QVector>
#include <QVector3D>

//
#include "plotwidget.h"

namespace Ui {
class InfoRLSWindow;
}

class InfoRLSWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InfoRLSWindow(GISInformer* gis,
                           QWidget *parent = 0);
    ~InfoRLSWindow();

    //
    void showRLS(const LabelRLS *infoRLS);

    //
    void setGraphicData(const QVector <double>& X,
                        const QVector <double>& Y);

    //
    void clearData();

private slots:

    // Обновить значение высоты РЛС
    void updateHeightRLS();

private:

    //
    GISInformer* gis;

    // Для графика ДН
    plotWidget* graphicWidget;

    //
    void setDesine();
    Ui::InfoRLSWindow *ui;


};

#endif // INFORLSWINDOW_H
