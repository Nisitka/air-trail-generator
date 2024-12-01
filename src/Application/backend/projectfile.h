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

    //
    void findingPoint();

    void unloading();

    void addDate(const QString& path);

    void deleteDate(const QString& path);

    bool frontWith(const QString& s, const QString& suffix);

    bool findString(const QString& s, const QString& suffix);

private:

    // Ошибка
    int codeError;
    QString infoError;

    //
    int countRLS;

    //
    int countMap;

    //
    int first, last, dfirst, dlast;

    // Карта, которая была открыта последней
    QString lastOpenMap; // путь карты на ФС

    //
    QFile* proFile;
};

#endif // PROJECTFILE_H
