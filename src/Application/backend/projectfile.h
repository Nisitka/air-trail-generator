#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QFile>

// Класс по работе с файлом проекта
class ProjectFile
{
public:
    ProjectFile();
    ~ProjectFile();

    // Коды ошибок
    enum typeError{none, openFile, buildFile}; // и т.д.

    // Узнать последнию ошибку
    int lastError(QString& infoError) const;
    int lastError() const;

    //
    bool open(const QString& path);

    //
    void create(const QString& path);

private:

    // Ошибка
    int codeError;
    QString infoError;

    //
    int countRLS;

    //
    int countMap;

    // Карта, которая была открыта последней
    QString lastOpenMap; // путь карты на ФС

    //
    QFile* proFile;
};

#endif // PROJECTFILE_H
