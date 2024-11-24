#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QFile>
#include <QVector>

// Управляет приложением (его настройками)
class ApplicationManager: public QObject
{
    Q_OBJECT
signals:

    // Уведомление об ошибке
    void error(int codeError, const QString& message);

public:

    // Ошибки, об которых будем уведомлять Core
    enum errors {createSettings, readSettings};

    ApplicationManager();

private:

    // Максимальное кол-во последних проектов
    int maxCountLastProject;

    // Рамеры зоны активных действий
    int heightActionArea;
    int widthActionArea;

    //
    void initSettings(const QString& pathSettings);

    //
    void createDefultSettings(const QString& pathSettings);

    // Файл настроек
    QFile* settingFile;
};

#endif // APPLICATIONMANAGER_H
