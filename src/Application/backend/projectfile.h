#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QFile>
#include <QMap>

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

    // Открыть файл проекта
    bool open(const QString& path);

    // Создать файл проекта
    void create(const QString& path);

    //
    enum typeObjects {RLS, plane};

private:

    // Теги-заголовки для сущностей, необходимых для проекта
    QMap<int,QString> headObj;

    // Узнать промежуток содержащий информацию об сущности
    void findingPoint(int& first, int& last, // номера строк промежутка
                      const QString& obj);   // тег сущност

    // Выгрузить строковые данные из файла проекта
    void unloading(QVector<QString>& stringsData, // куда выгружаем
                   typeObjects obj);              // что (по тегу)

    void addData(const QString& path);

    void deleteData(const QString& path);

    //
    bool frontWith(const QString& s, const QString& suffix);
    bool findString(const QString& s, const QString& suffix);

    // Ошибка
    int codeError;
    QString infoError;

    //
    int countRLS;

    //
    int countMap;

    //
    int /*first*//*, last,*/ dfirst, dlast;

    // Карта, которая была открыта последней
    QString lastOpenMap; // путь карты на ФС

    //
    QFile* proFile;
};

#endif // PROJECTFILE_H
