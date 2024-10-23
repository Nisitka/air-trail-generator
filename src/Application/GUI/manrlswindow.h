#ifndef MANRLSWINDOW_H
#define MANRLSWINDOW_H

#include "./multiplewindow.h"

#include "backend/GIS/gisinformer.h"
#include "backend/RLS/informerrls.h"

//
#include "plotwidget.h"
//
#include "processtmpwidget.h"

namespace Ui {
class manRLSWindow;
}

class manRLSWindow: public MultipleWindow
{
    Q_OBJECT
signals:

    // Создать новую РЛС
    void createRLS(QPoint posRLS, const QString& nameNewRLS);

    // Удалить РЛС
    void delRLS(int id);

    // Выбрать РЛС
    void setCurrentRLS(int id);

    // Установить новую позицию РЛС
    void setPositionRLS(int idX, int idY);

    // Включить/Выключить РЛС
    void runRLS();
    void offRLS();

public slots:

    // Отобразить информацию об выбранной РЛС
    void showInfoCurRLS();

    //
    void updateListRLS();

    // Обновить данные по конкретной РЛС в списке
    void updateDataRLS(int idRLS);

    // Отображение выполнения процессов
    void startProcessing();
    void updateStatProcessing(int percent); // В процентах
    void finishProcessing();

    // Обновить координаты РЛС
    void updateCoordRLS(Coords);

public:
    explicit manRLSWindow(InformerRLS* infoRLS);
    ~manRLSWindow();

private slots:

    //
    void setIdCurRLS();

    // изменить точку постановки выбранной РЛС
    void setNewPosRLS();

    void enablingRLS();

    void addRLS();

    void removeRLS();

private:

    //
    QStringList columnNames = {"Наименование", "Статус", "Координаты"};

    // Перерисовать график ДН
    void repaintGraphic();

    //
    void RLStoTable(int numStr,
                    const LabelRLS* rls);

    //
    InformerRLS* infoRLS;
    QList <LabelRLS*> listRLS;

    //
    int idCurRLS;

    // Для графика ДН
    plotWidget* graphicWidget;

    // Координаты РЛС
    Coords RLScoords;

    //
    processTmpWidget* loadingWidget;

    void setDesine();
    Ui::manRLSWindow *ui;
};

#endif // MANRLSWINDOW_H
