#ifndef TOOLSETRLS_H
#define TOOLSETRLS_H

#include "GUI/drawArea/Tools/drawareatool.h"
#include "backend/GIS/gisinformer.h"
#include "backend/RLS/informerrls.h"

class ToolSetRLS: public drawAreaTool
{
    Q_OBJECT
signals:

    // Установить РЛС
    void setCoordRLS(Coords coord);

public slots:

    //
    void updateInfoRLS();

public:
    ToolSetRLS(int id,
               GISInformer* gis,
               InformerRLS* infoRLS);

    void mousePress(QMouseEvent* mouse) override;
    void mouseRelease(QMouseEvent* mouse) override;
    void mouseMove(QMouseEvent* mouse) override;

    void procDrawTask() override;

    void init() override;
    void end() override;

    // изменить точку постановки РЛС
    void setMarkCoordRLS();

private:

    // Отрисовка иконки одной станции (РЛС)
    void drawRLS(const LabelRLS* station,
                 const QPixmap&  icon,
                 const QColor& textColor) const;

    // Интерфейс для получения инфы об РЛС
    InformerRLS* infoRLS;

    //
    GISInformer* gis;

    // Иконки РЛС
    QPixmap pixRLS;
    QPixmap pixCurRLS;

    //
    QColor curRLScolor;
    QColor RLScolor;

    //
    drawTask<ToolSetRLS>* dTask;

    // позиция РЛС на окне
    int xPosRLS;
    int yPosRLS;
};

#endif // TOOLSETRLS_H
