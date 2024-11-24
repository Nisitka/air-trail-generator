#ifndef MANRLSWINDOW_H
#define MANRLSWINDOW_H

#include "./multiplewindow.h"

#include "backend/GIS/gisinformer.h"
#include "backend/RLS/informerrls.h"

#include "GUI/inforlswindow.h"

//
#include "processtmpwidget.h"

namespace Ui {
class manRLSWindow;
}

class manRLSWindow: public MultipleWindow
{
    Q_OBJECT
signals:

    // Добавить РЛС
    void addRLS();

    // Выбрать РЛС
    void setCurrentRLS(int id);

    // Установить новую позицию РЛС
    void setPositionRLS(int idX, int idY);

    //
    void delRLS(int idRLS);

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

public:
    explicit manRLSWindow(GISInformer* gis,
                          InformerRLS* infoRLS);
    ~manRLSWindow();

private slots:

    // Выбрать РЛС
    void setIdCurRLS();

    // Удалить РЛС из проекта
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
    InfoRLSWindow* guiRLS;
    InformerRLS* infoRLS;
    QList <LabelRLS*> listRLS;

    //
    int idCurRLS;

    // Координаты РЛС
    Coords RLScoords;

    //
    processTmpWidget* loadingWidget;

    void setDesine();
    Ui::manRLSWindow *ui;
};

#endif // MANRLSWINDOW_H
