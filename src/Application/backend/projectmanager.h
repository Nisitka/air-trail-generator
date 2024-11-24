#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QFile>
#include <QObject>

// Класс управляющий проектом
class ProjectManager: public QObject
{
    Q_OBJECT

public slots:

    /// Работа с проектом
    // Создать новый проект
    void createProject(const QString& dirNameNewProject);

    // Открыть сущесвующий проект
    void openProject(const QString& dirNameProject);


    /// Карты
    // Добавить карту в проект
    void addMap(const QString& dirNameMap);

    // Удалить карту из проекта
    void removeMap(const QString& nameMap);


    /// РЛС
    // Добавть РЛС в проект
    void addRLS(const QString& dirNameRLS);

    // Удалить РЛС из проекта
    void removeRLS(const QString& nameRLS);

public:
    ProjectManager();

private:

    // Закрыть текущий проект
    void closeProject();

    // pro файл проекта
    QFile* proFile;
};

#endif // PROJECTMANAGER_H
